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
 *  ======== LoggerIdle.xdc ========
 */
import xdc.runtime.ILogger;
import xdc.runtime.Log;
import xdc.rov.ViewInfo;

/*!
 *  ======== LoggerIdle ========
 *  A logger which routes `Log` events to a users transport function.
 *
 *  This logger processes log events as they are generated, stores them in 
 *  a buffer and durring idle sends a section of the buffer to the users  
 *  transport function.  If you are seeing no log events or dropping too
 *  many events check that you are not logging too often and have enough idle
 *  time to send. LoggerIdle is compatable with StellarisWare and MWare
 *  devices. Example transports for UART (B92 and F28M35x) and USB (F28M35x)
 *  as well as initialization functions are included in the evmF28M35x.c files
 *  under the device folder in the ti.examples directory.
 *
 *  @a(Examples)
 *  Configuration example: The following XDC configuration statements
 *  create a logger module, and assign it as the default logger for all
 *  modules.
 *
 *  @p(code)
 *  var Defaults = xdc.useModule('xdc.runtime.Defaults');
 *  var Diags = xdc.useModule('xdc.runtime.Diags');
 *  var LoggerIdle = 
                xdc.useModule('ti.mcusdk.utils.LoggerIdle');
 *
 *  LoggerIdle.bufferSize = 60;
 *  LoggerIdle.timestamp = false;
 *  LoggerIdle.transportType = LoggerIdle.TransportType_UART;
 *  LoggerIdle.transportFxn = '&LoggerIdle_uartSend';
 *  var LoggerIdleParams = new LoggerIdle.Params();
 *  Defaults.common$.logger = LoggerIdle.create(LoggerIdleParams);
 *  @p
 */

module LoggerIdle inherits ILogger {

    /*!
     *  ======== TransportType ========
     *  Used to specify the type of transport to use
     *
     *  This enum is used by the instrumentation host to determine what
     *  the transport is. It is not used by the target code.
     */
    enum TransportType {
        TransportType_UART = 0,
        TransportType_USB = 1, 
        TransportType_ETHERNET = 2, 
        TransportType_CUSTOM = 3
    };
    
    /*!
     *  @_nodoc
     *  ======== ModuleView ========
     */
    metaonly struct ModuleView {        
        Bool       isEnabled;
        Bool       isTimestampEnabled;
        Int        bufferSize;
        UInt       sequenceNumber;
        String     transportType;        
        String     customTransport;
    }

    metaonly struct RecordView {
        Int     sequence;
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
                ['Records', 
                    {
                        type: xdc.rov.ViewInfo.MODULE_DATA,
                        viewInitFxn: 'viewInitRecords',
                        structName: 'RecordView'
                    }
                ]
            ]
        });
    
    /*!
     *  ======== LoggerFxn ========
     *  Typedef for the transport function pointer. 
     */
    typedef Int (*LoggerFxn)(UChar *, Int);
    
    /*!
     *  ======== bufferSize ========
     *  LoggerIdle buffer size in MAUS
     */
    config SizeT bufferSize = 256;
    
    /*!
     *  ======== isTimestampEnabled ========
     *  Enable or disable logging the 64b local CPU timestamp
     *  at the start of each event
     *
     *  Having a timestamp allows an instrumentation host (e.g.
     *  System Analyzer) to display events with the correct system time.
     */
    config Bool isTimestampEnabled = true;        
        
    /*!
     *  ======== transportType ========
     *  Transport used to send the records to an instrumentation host
     *
     *  This parameter is used to specify the transport that the 
     *  `{@link #transportFxn}` function will use to send the buffer to
     *  an instrumentation host (e.g. System Analyzer in CCS).
     *
     *  This parameter is placed into the generated UIA XML file. The 
     *  instrumentation host can use the XML file to help it auto-detect as
     *  much as possible and act accordingly.
     *
     *  If the desired transport is not in the `{@link #TransportType}` enum,
     *  select `{@link #TransportType_CUSTOM}` and set the 
     *  `{@link #customTransportType}` string with the desired string.
     */
    metaonly config TransportType transportType = TransportType_UART;
    
    /*!
     *  ======== customTransportType ========
     *  Custom transport used to send the records to an instrumentation host
     *
     *  If the desired transport is not in the `{@link #TransportType}` enum,
     *  and `{@link #transportType}` is set to `{@link #TransportType_CUSTOM}`,
     *  this parameter must be filled in with the correct transport name.
     *
     *  If `{@link #transportType}` is NOT set to 
     *  `{@link #TransportType_CUSTOM}`, this parameter is ignored.
     */
    config String customTransportType = null;
    
    /*! 
     *  ======== transportFxn ========
     *  User defined transport function responsible for transmitted the records 
     */
    config LoggerFxn transportFxn = null;
    
    /*! 
     *  @_nodoc
     *  ======== L_test ========
     *  Event used for benchmark tests
     */
    config xdc.runtime.Log.Event L_test = {
        mask: xdc.runtime.Diags.USER1,    
        msg: "Test Event"
    };
    
instance:
    /*!
     *  ======== create ========
     *  Create a `LoggerIdle` logger
     *     
     *  The logger instance will route all log events it receives to
     *  the Uart.
     */
    create();
    
    @DirectCall   
    override Void write0(xdc.runtime.Log.Event evt, xdc.runtime.Types.ModuleId mid);
    
    @DirectCall   
    override Void write1(xdc.runtime.Log.Event evt, xdc.runtime.Types.ModuleId mid, 
                            IArg a1);
                            
    @DirectCall   
    override Void write2(xdc.runtime.Log.Event evt, xdc.runtime.Types.ModuleId mid, 
                            IArg a1, IArg a2);
                            
    @DirectCall   
    override Void write4(xdc.runtime.Log.Event evt, xdc.runtime.Types.ModuleId mid, 
                            IArg a1, IArg a2, IArg a3, IArg a4);
                            
    @DirectCall   
    override Void write8(xdc.runtime.Log.Event evt, xdc.runtime.Types.ModuleId mid, 
                            IArg a1, IArg a2, IArg a3, IArg a4,
                            IArg a5, IArg a6, IArg a7, IArg a8);

internal:
    
    /*! 
     *  ======== idleWrite =========
     *  Idle function that calls the transport function.
     */
    Void idleWrite();
    
    struct Module_State {
        LoggerFxn loggerFxn;
        Bool enabled;          /* If the logger is enabled or not */
        Bool empty;         /* True if there is data in the buffer */
        UInt idleSequence;     /* Sequence number for the log event */
        UInt bufferSize;       /* Size of the buffer in words */
        UInt32 idleBuffer[];   /* Stores log events to be sent */
        UInt32 *bufferRead;    /* Pointer to the first word to be read */
        UInt32 *bufferWrite;   /* Pointer to the next word to write to */
        UInt32 *bufferPad;     /* Pointer to the last word in the buffer when 
                                  the buffer overflows into the 10 word pad */
        UInt32 *bufferEnd;     /* Pointer to begining of the buffer pad */
    };
    
    struct Instance_State {
    };
}
/*
 *  @(#) ti.uia.sysbios; 1, 0, 0, 0,1; 7-13-2012 11:12:38; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

