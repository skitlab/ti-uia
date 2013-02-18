/* 
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */

/*
 *  ======== LoggerProbePoint.xdc ========
 */
import xdc.runtime.ITimestampClient;
import xdc.runtime.IHeap;
import xdc.runtime.Types;
import xdc.runtime.Log;
import xdc.runtime.ILogger;
import xdc.runtime.Error;
import xdc.runtime.Diags;
import xdc.rov.ViewInfo;

/*!
 *  ======== LoggerProbePoint ========
 *  A logger which stores `Log` events in a non-blocking, streamable 
 *  circular buffer.
 */

@ModuleStartup      /* Initialize static instances */
@InstanceFinalize   /* this mod has cleanup fxn when instances are deleted */
@InstanceInitError  /* instance create can fail */
module LoggerProbePoint inherits ILoggerSnapshot
{
    /*!
     *  @_nodoc
     *  ======== ModuleView ========
     */
    metaonly struct ModuleView {                
        Bool       isTimestampEnabled;
        Bool       enableFlush;
        String     statusLogger;
        String     moduleIdToRouteToStatusLogger;
        //Diags.Mask level1Mask;
        //Diags.Mask level2Mask
        //Diags.Mask level3Mask
        //Diags.Mask level4Mask
    }
    
    /*!
     *  @_nodoc
     *  ======== InstanceView ========
     */
    metaonly struct InstanceView {        
        String    label;
        Bool      enabled;
        SizeT     transferBufSize;                
        SizeT     maxEventSize;                
        Bits16    serial;
        Int       numCores;        
        IUIATransfer.TransferType transferType;        
        Bool      flush;        
        Int       droppedEvents;
    }

    metaonly struct RecordView {
        Int     serial;
        Long    timestampRaw;
        String  modName;
        String  text;
        Int     eventId;
        String  eventName;
        IArg    arg0;
        IArg    arg1;
        IArg    arg2;
        IArg    arg3;
        IArg    arg4;
        IArg    arg5;
        IArg    arg6;
        IArg    arg7;
    }
    
    /*!
     *  @_nodoc
     *  ======== rovViewInfo ========
     */    
    @Facet
    metaonly config ViewInfo.Instance rovViewInfo =
        ViewInfo.create({
            viewMap: [
                ['Module',   
                    {
                        type: ViewInfo.MODULE,   
                        viewInitFxn: 'viewInitModule', 
                        structName: 'ModuleView'
                    }
                ],
                ['Instances',   
                    {
                        type: ViewInfo.INSTANCE,   
                        viewInitFxn: 'viewInitInstances', 
                        structName: 'InstanceView'
                    }
                ],
                ['Records', 
                    {
                        type: xdc.rov.ViewInfo.INSTANCE_DATA,
                        viewInitFxn: 'viewInitRecords',
                        structName: 'RecordView'
                    }
                ]
            ]
        });

    /*! Error raised if get or setFilterLevel receive a bad level value */
    config Error.Id E_badLevel =
        {msg: "E_badLevel: Bad filter level value: %d"};

    /*!
     *  ======== isTimestampEnabled ========
     *  Enable or disable logging the 64b local CPU timestamp
     *  at the start of each event
     */
    config Bool isTimestampEnabled = true;
    
    /*!
     *  ======== enableFlush ========
     *  Flush all logs at system exit
     */
    config Bool enableFlush = false;

   /*!
     *  ======== statusLogger ========
     *  Route all 'STATUS' (error and warning) events to this logger.
     *
     *  If a statusLogger is specified AND the filterByLevel is true, 
     *  all LoggerProbePoint instances will check to determine if any of the events
     *  they receive are errors or warnings (if their diags mask includes the 
     *  STATUS category) or if the event is from the module specified by 
     *  moduleIdToRouteToStatusLogger, and if so, will log these
     *  events to the statusLogger.
     *
     *  Error events are infrequent, but it's generally critical that they be
     *  seen. In a typical system, non-error events easily outnumber any error
     *  events, and the logger is likely to wrap, overwriting any error events.
     *  To protect these events from being overwritten and lost, they can be
     *  sent to their own separate logger to preserve them.
     *
     *  The default value is null, indicating that the STATUS events will just
     *  be logged by the logger they were sent to.
     */
    config xdc.runtime.IFilterLogger.Handle statusLogger = null;

   /*!
     *  ======== overflowLogger ========
     *  Route all events that cannot be stored in the main (transfer) 
     *  event buffer to this logger
     *
     *  If an overflowLogger is specified and there is not enough room in the
     *  instance's buffer, the event will be passed to this logger instead.
     *
     *  The overflow Logger is intended to ensure that the last 'N' events 
     *  leading up to a breakpoint are captured and are available for stop-mode
     *  debugging.  The overflow logger should be designed to automatically
     *  wrap, overwriting the oldest events and preserving the most recent 
     *  events. An example is xdc.runtime.LoggerBuf.
     *
     *  The default value is null, indicating that overflow events that occur 
     *  because the event transport is not fast enough to upload them will 
     *  just be dropped.
     */
    config ILogger.Handle overflowLogger = null;
    
    /*!
     *  ======== level1Mask ========
     *  Mask of diags categories whose initial filtering level is Diags.LEVEL1
     *
     *  See '{@link #level4Mask}' for details.
     */
    config Diags.Mask level1Mask = 0;

    /*!
     *  ======== level2Mask ========
     *  Mask of diags categories whose initial filtering level is Diags.LEVEL2
     *
     *  See '{@link #level4Mask}' for details.
     */
    config Diags.Mask level2Mask = 0;

    /*!
     *  ======== level3Mask ========
     *  Mask of diags categories whose initial filtering level is Diags.LEVEL3
     *
     *  See '{@link #level4Mask}' for details.
     */
    config Diags.Mask level3Mask = 0;

    /*!
     *  ======== level4Mask ========
     *  Mask of diags categories whose initial filtering level is Diags.LEVEL4
     *
     *  If 'filterByLevel' is true, then all LoggerBuf instances will filter
     *  incoming events based on their event level.
     *
     *  The LoggerProbePoint module allows for specifying a different filter level for
     *  every Diags bit. These filtering levels are module wide; LoggerBuf does
     *  not support specifying the levels on a per-instance basis.
     *
     *  The setFilterLevel API can be used to change the filtering levels at
     *  runtime.
     *
     *  The default filtering levels are assigned using the 'level1Mask' -
     *  'level4Mask' config parameters. These are used to specify, for each of
     *  the four event levels, the set of bits which should filter at that
     *  level by default.
     *
     *  The default filtering configuration sets the filter level to
     *  Diags.LEVEL4 for all logging-related diags bits so that all events are
     *  logged by default.
     */
    config Diags.Mask level4Mask = Diags.ALL_LOGGING;

    /*!
     *  ======== moduleToRouteToStatusLogger ========
     *  events from this module will be routed to the statusLogger (if configured)     
     */    
    metaonly config String moduleToRouteToStatusLogger;

    /*!
     *  ======== setModuleIdToRouteToStatusLogger ========
     *  Specifies which module to route events to the statusLogger for
     *
     *  @param(mid)    the module ID to route events for.  Set to -1 for 'none'
     */
    @DirectCall
    Void setModuleIdToRouteToStatusLogger(Types.ModuleId mid);
    
    /*!
     *  ======== flushAll ========
     *  Flush logs of all instances of `LoggerProbePoint`
     *
     *  The user is responsible for making sure that no `LoggerProbePoint` 
     *  instances are created or deleted while in this API, by using an 
     *  appropriate gate.
     */
    Void flushAll();    
    
    /*!
     *  ======== flushAllInternal ========
     *  @_nodoc
     */
    @DirectCall
    Void flushAllInternal(Int stat);

    /*!
     * @_nodoc
     *  ======== initDecoder ========
     *  Initialize the Java LoggerProbePointDecoder for use in the LoggerProbePoint
     *  'Records' ROV view.
     */
    function initDecoder();
    
instance:
    /*!
     *  ======== create ========
     *  Create a `LoggerProbePoint` logger
     *
     *  @see LoggerProbePoint#Params
     */
    @DirectCall
    create();

    /*!
     *  ======== transferBufSize ========
     *  Number of minimum addressable units (e.g. bytes) in transfer buffer
     *
     *  The transfer buffer is used to store events that can be read by
     *  the transport.  Since the transport is typically bandwidth limited,
     *  it is possible to drop events if the buffer fills up before the
     *  event can be transmitted.  If this occurs and the 
     *  `{@link #overflowLogger} is not null, the event will be written to 
     *  the overflow buffer.
     */
    config SizeT transferBufSize = 512;

    /*!
     * ======== maxEventSize ========
     * The maximum event size (in Maus) that can be written with a single event.
     *
     * Determines the size of the area following the circular buffer
     * that is used to provide a linear copy space to speed up
     * copying data into the buffer in a circular manner.  
     * Must be less than or equal to transferBufSize.
     */
    config SizeT maxEventSize = 128;
    
    /*!
     *  ======== exitFlush ========
     *  Flush log at system exit
     *
     *  Only used when module parameter `{@link #enableFlush}` is `true`.
     */
    config Bool exitFlush = true;

    /*!
     *  ======== bufSection ========
     *  Section name for the buffer managed by the static instance.
     *
     *  The default section is the 'dataMemory' in the platform.
     */
    metaonly config String bufSection = null;

    /*!
     *  ======== bufHeap ========
     *  The heap that contains the `Log` buffer for dynamic instances.
     *
     *  The default value `null` means the buffer will be allocated from
     *  the `{@link Memory#defaultHeapInstance}` heap.
     */
    config IHeap.Handle bufHeap = null;    
    
    /*!
     *  ======== numCores ========
     *  Number of cores running the same image with an instance in shared memory
     *
     *  A common use case is to have the same binary image (e.g. .out file)
     *  run on multiple cores of multi-core device. This causes a problem if the
     *  logger's buffer is in shared memory (e.g. DDR). Since the image is the
     *  same for all the cores, each core will attempt to write to the same 
     *  buffer in the shared memory. To avoid this, either the logger's buffers
     *  must be in non-shared memory or by setting the numCores parameter to
     *  the number of cores on the device.
     *
     *  Note: the `{@link #bufSection}` along with the Program.sectMap is how
     *  a logger instance's buffer is placed into specific memory.
     *
     *  Setting numCores to a value great than 1 signals LoggerProbePoint to 
     *  statically set aside additional memory ((x numCores) to allow each 
     *  core to have `{@link #transferBufSize}` amount of memory. 
     *
     *  Warning: setting this parameter to a value greater than one should only
     *  be done when there is a single image used on multiple cores of a 
     *  multi-core device AND the logger instance's buffer is in shared memory.
     *  While functionally it will still work, memory will be wasted if both
     *  these conditions are not met.
     * 
     *  The default is 1, which means do not reserve any additional memory
     *  for the logger.
     */
    config Int numCores = 1;

    /*!
     *  ======== flush ========
     *  Read, clear, and output the contents of the log
     *
     *  This method reads, clears, and "prints" each `Log` event (via
     *  `{@link System#printf}`) in the log.
     */
    @DirectCall
    Void flush();

    /*!
     *  ======== getNumDropped =========
     *  Returns the number of dropped events for this logger instance
     */
    @DirectCall
    Int getNumDropped();
    
    /*!
     *  ======== enable ========
     *  Enable a log
     *
     *  @a(returns)
     *  The function returns the state of the log (`TRUE` if enabled,
     *  `FALSE` if disabled) before the call. That allow clients to restore
     *  the previous state.
     */
    @DirectCall
    override Bool enable();

    /*!
     *  ======== disable ========
     *  Disable a log
     *
     *  Events written to a disabled log are silently discarded.
     *
     *  @a(returns)
     *  The function returns the state of the log (`TRUE` if enabled,
     *  `FALSE` if disabled) before the call. That allow clients to restore
     *  the previous state.
     */
    @DirectCall
    override Bool disable();

    /*!
     *  ======== write0 ========
     *  Process a log event with 0 arguments and the calling address.
     *
     *  Same as `write4` except with 0 arguments rather than 4.
     *  @see #write4()
     */
    @DirectCall
    override Void write0(Log.Event evt, Types.ModuleId mid);

    /*!
     *  ======== write1 ========
     *  Process a log event with 1 arguments and the calling address.
     *
     *  Same as `write4` except with 0 arguments rather than 4.
     *  @see #write4()
     */
    @DirectCall
    override Void write1(Log.Event evt, Types.ModuleId mid, IArg a1);

    /*!
     *  ======== write2 ========
     *  Process a log event with 2 arguments and the calling address.
     *
     *  Same as `write4` except with 2 arguments rather than 4.
     *
     *  @see #write4()
     */
    @DirectCall
    override Void write2(Log.Event evt, Types.ModuleId mid, IArg a1, IArg a2);

    /*!
     *  ======== write4 ========
     *  Process a log event with 4 arguments and the calling address.
     *
     *  @see ILogger#write4()
     */
    @DirectCall
    override Void write4(Log.Event evt, Types.ModuleId mid, IArg a1, IArg a2, 
                         IArg a3, IArg a4);

    /*!
     *  ======== write8 ========
     *  Process a log event with 8 arguments and the calling address.
     *
     *  Same as `write4` except with 8 arguments rather than 4.
     *
     *  @see #write4()
     */
    @DirectCall
    override Void write8(Log.Event evt, Types.ModuleId mid, IArg a1, IArg a2, 
                         IArg a3, IArg a4, IArg a5, IArg a6, IArg a7, IArg a8);

    /*!
     *  ======== setFilterLevel ========
     *  Sets the level of detail that instances will log.
     *
     *  Events with the specified level or higher will be logged, events
     *  below the specified level will be dropped.
     *
     *  Events are filtered first by diags category, then by level. If an
     *  event's diags category is disabled in the module's diags mask, then it
     *  will be filtered out regardless of level. The event will not even be
     *  passed to the logger.
     *
     *  This API allows for setting the filtering level for more than one
     *  diags category at a time. The mask parameter can be a single category
     *  or multiple categories combined, and the level will be set for all of
     *  those categories.
     *
     *  @param(mask) The diags categories to set the level for
     *  @param(filterLevel) The new filtering level for the specified
     *                      categories
     */
    @DirectCall
    override Void setFilterLevel(Diags.Mask mask, Diags.EventLevel filterLevel);

    /*!
     *  ======== getFilterLevel ========
     *  Returns the mask of diags categories currently set to the specified
     *  level.
     *
     *  See '{@link #setFilterLevel}' for an explanation of level filtering.
     */
    @DirectCall
    override Diags.Mask getFilterLevel(Diags.EventLevel level);
    
    /*!
     * ======== getFreeSize =========
     * Determines how much free space exist (in Maus)
     */
    @DirectCall
    SizeT getFreeSize();
    
    /*!
     * ======== getUnreadSize =========
     * Determines how much unread data exist (in Maus)
     */
    @DirectCall
    SizeT getUnreadSize();
    
internal:
    /*!
     *  ======== readBlockOfMemory ========
     */
    @DirectCall
    Bool readBlockOfMemory(Handle obj, Ptr pMemBlock, SizeT sizeToRead);    
    
    /*!
     *  ======== writeBlockOfMemory ========
     */
    @DirectCall
    Bool writeBlockOfMemory(Handle obj, Ptr newWrPtr, Ptr pMemBlock, 
                            SizeT size);

    /*!
     *  ======== filterOutEvent ========
     */
    @DirectCall
    Bool filterOutEvent(Diags.Mask mask);

    struct Module_State {
        Diags.Mask level1;
        Diags.Mask level2;
        Diags.Mask level3;
        Types.ModuleId moduleIdToRouteToStatusLogger;
    };
    
    /*!
     *  @_nodoc    
     * ======== postIncrementPtr =========
     * returns the buffer size in MAUs (min. addressable units)
     */
     @DirectCall
     UArg *postIncrementPtr(Object *obj, UArg *myRdPtr);

    struct Instance_State {
        QueueDescriptor.Header hdr;    
        IHeap.Handle bufHeap;
        SizeT maxEventSizeInBits32;      
        Bits16 serial;
        IUIATransfer.TransferType transferType;
        Bool enabled;
        Bool flush;
        Int  droppedEvents;
        Ptr  queueStartAdrs;  /* Replicates hdr.queueStartAdrs to reduce CPU overhead */
        SizeT  queueSizeInMAUs; /* Replicates hdr.queueSizeInMAUs to reduce CPU overhead */   
        Ptr  endOfBufferAdrsPlus1; /* pre-calculate the end address to reduce CPU overhead.
                                      = (Bits32)obj->queueStartAdrs + obj->queueSizeInMAUs */
        Char bufferArray[];
        Int numCores;
    };
}

/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:25; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

