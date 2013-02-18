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
 *  ======== LoggerProbePoint.xs ========
 */

var LoggerProbePoint = null;
var isEnableDebugPrintf = false;
var UIAMetaData;

/*
 *  ======== module$use ========
 */
function module$use() {
    var System = xdc.useModule('xdc.runtime.System');
    var Defaults = xdc.useModule('xdc.runtime.Defaults');
    var Diags = xdc.module("xdc.runtime.Diags");
    var Types = xdc.useModule('xdc.runtime.Types');    
    var QueueDescriptor = xdc.useModule('ti.uia.runtime.QueueDescriptor');
    var IUIATransfer = xdc.useModule('ti.uia.runtime.IUIATransfer');
    var Memory = xdc.useModule('xdc.runtime.Memory');
    var Timestamp = xdc.useModule('xdc.runtime.Timestamp');
    
    /* Ensure that UIAMetaData is used (e.g. for JTAG transports with no target-side services) */
    UIAMetaData = xdc.useModule('ti.uia.runtime.UIAMetaData');
    LoggerProbePoint = this;

    if (LoggerProbePoint.enableFlush) {
        System.atexitMeta(LoggerProbePoint.flushAllInternal);
    }
    
    /* Memory module is needed only if memoryPolicy is not STATIC_POLICY. */
    if (Defaults.getCommon(LoggerProbePoint, "memoryPolicy") != 
        Types.STATIC_POLICY) {
        xdc.useModule('xdc.runtime.Memory');
    }

    /* disable trace on timestamp proxy to prevent recursive callbacks */
    var modName = Timestamp.SupportProxy.delegate$.$name;
    Diags.setMaskMeta(modName, Diags.ALL & (~Diags.ASSERT), Diags.ALWAYS_OFF);
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    /* Assign the default filtering levels based on the configuration. */
    mod.level1 = params.level1Mask;
    mod.level2 = params.level2Mask;
    mod.level3 = params.level3Mask;    

    if ((params.moduleToRouteToStatusLogger != null) &&
        (params.statusLogger != null)){
        var toRoute = xdc.module(params.moduleToRouteToStatusLogger);
        mod.moduleIdToRouteToStatusLogger = toRoute.Module__id;        
    }
    else {
        mod.moduleIdToRouteToStatusLogger = 65535;
    }
    
    if (this.$name.toLowerCase().indexOf('probepoint') > 0) {
        UIAMetaData.setTransportFields(false, 
                                       UIAMetaData.UploadMode_PROBEPOINT,
                                       "NONE", "UIAEVENTHDR", false, null);
    }
    else {
        if (this.$name.toLowerCase().indexOf('stopmode') > 0) {
            UIAMetaData.setTransportFields(false, 
                                           UIAMetaData.UploadMode_JTAGSTOPMODE,
                                           "NONE", "UIAEVENTHDR", false, null);
        } 
        else {
            UIAMetaData.setTransportFields(false, 
                                           UIAMetaData.UploadMode_JTAGRUNMODE,
                                           "NONE", "UIAEVENTHDR", false, null);
        }
    }
}

/*
 *  ======== instance$static$init ========
 */
function instance$static$init( obj, prms) {

    var QueueDescriptor = xdc.module('ti.uia.runtime.QueueDescriptor');
    var LoggerProbePoint = xdc.module('ti.uia.runtime.LoggerProbePoint');
    var IUIATransfer = xdc.useModule('ti.uia.runtime.IUIATransfer');
    var moduleName = this.$name;
    var sizeOfInt32 = Program.build.target.stdTypes.t_Int32.size;
    
    if (prms.transferBufSize > 0){
        /* Create circular buffer for transferBuf */

        var Memory = xdc.module('xdc.runtime.Memory');
        var QueueDescriptor = xdc.module('ti.uia.runtime.QueueDescriptor');

        /*
         *  The following will place a memory buffer into section name. This
         *  buffer is the memory that this instance will manage.
         */
        var adjustedSize = prms.transferBufSize + prms.maxEventSize;
        if (prms.numCores > 1) {
            adjustedSize = adjustedSize * prms.numCores;
        }

        obj.bufferArray.length = adjustedSize;
        Memory.staticPlace(obj.bufferArray, 0, prms.bufSection);
        obj.maxEventSizeInBits32 = prms.maxEventSize / sizeOfInt32;

        /* structSize is used for version control if newer fields are avail. */
        obj.queueSizeInMAUs = prms.transferBufSize;
        obj.queueStartAdrs = obj.bufferArray.$addrof(0);
        obj.endOfBufferAdrsPlus1 = obj.bufferArray.$addrof(prms.transferBufSize);
        obj.hdr.structSize = QueueDescriptor.Header.$sizeof();
        if (moduleName.toLowerCase().indexOf('stopmode') > 0) {
            obj.hdr.queueType = 
                QueueDescriptor.QueueType_TOHOST_EVENT_OVERFLOW_BUFFER;
        } else {
            obj.hdr.queueType = 
                QueueDescriptor.QueueType_TOHOST_EVENT_CIRCULAR_BUFFER;
        }
        obj.hdr.queueSizeInMAUs = prms.transferBufSize;
        obj.hdr.queueStartAdrs = obj.bufferArray.$addrof(0);
        obj.hdr.readPtr = obj.bufferArray.$addrof(0);
        obj.hdr.writePtr = obj.bufferArray.$addrof(0);
        obj.hdr.ownerModuleId = LoggerProbePoint.Module__id;
        obj.hdr.instanceId = QueueDescriptor.generateInstanceId();
        obj.hdr.priority = Number(prms.priority);
        obj.hdr.numDroppedCtrAdrs = obj.$addrof("droppedEvents");
        obj.hdr.next = null;
        if (isEnableDebugPrintf){
            print("UIA LoggerProbePoint.xs: instance$static$init: instanceId = "+obj.hdr.instanceId+", priority = "+obj.hdr.priority);
        }        
    }
    else {
        obj.queueSizeInMAUs = 0;
        obj.queueStartAdrs = null;
        obj.endOfBufferAdrsPlus1 = null;
        obj.hdr.structSize = QueueDescriptor.Header.$sizeof();
        obj.hdr.queueType = QueueDescriptor.QueueType_NONE;
        obj.hdr.queueSizeInMAUs = 0;
        obj.hdr.queueStartAdrs = null;
        obj.hdr.readPtr = null;
        obj.hdr.writePtr = null;
        obj.hdr.ownerModuleId = LoggerProbePoint.Module__id;
        obj.hdr.priority = Number(IUIATransfer.Priority_STANDARD);        
        obj.hdr.next = null;
        obj.hdr.instanceId = 0;
        obj.hdr.numDroppedCtrAdrs = null;
        if (isEnableDebugPrintf){
            print("UIA LoggerProbePoint.xs: instance$static$init: transferBufSize = 0, instanceId = "+obj.hdr.instanceId+", priority = "+obj.hdr.priority);
        }        
    }
    /*
     * Note: not really needed in static case since the app
     * should not free this object. Here for completeness.
     */
    obj.bufHeap = null;
    obj.transferType = prms.transferType;
    obj.flush = prms.exitFlush;
    obj.maxEventSizeInBits32 = prms.maxEventSize / sizeOfInt32;
    obj.numCores = prms.numCores;
    obj.serial = 1;
    obj.droppedEvents = 0;
    obj.enabled = true;


    //TODO: find some way to initialize the address of the queue descriptor
    // for this instance and make it available to the UIAMetaData.xs script.

    var adrs = obj.hdr.$addrof("structSize");
    LoggerProbePoint.setPtrToQueueDescriptorMeta(this, obj.$addrof("hdr"));
}


/*
 *  ======== getLoggerInstanceId ========
 *  Parses the string returned from the instance (e.g. Mod.Instance#1) 
 *  Returns the trailing number +1 as the instance ID.  This can then 
 *  be used to look up the instance using mod.$instances[instanceId].
 *  It is also used as a unique identifier in the Queue Descriptor header
 *  and UIA Metadata to identify which instance of a logger is being used
 *  for a specific purpose within UIA. Note that a LoggerInstanceId of 0 
 *  is reserved for dynamically created instances of the logger - the
 *  target code can test to see if the logger's queue descriptor header
 *  has an ID field of 0, and scan through the list of queue descriptors
 *  to determine what the maximum logger ID that is in use is in order
 *  to initialize the instance ID to a unique value for that logger module.
 */
function getLoggerInstanceId(inst){
   var mod = xdc.module('ti.uia.runtime.LoggerProbePoint');
   var obj = inst.$object;
   var id = obj.hdr.instanceId;
   return (id);
}

/*
 *  ======== getLoggerPriority ========
 *  returns the priority of this logger instance.  
 */
function getLoggerPriority(inst){
   var mod = xdc.module('ti.uia.runtime.LoggerProbePoint');
   var priority = inst.$object.hdr.priority;
   return (priority);
}

/* 
 *  ======== setLoggerPriority ========
 *  sets the priority of this logger instance.  
 */
function setLoggerPriority(inst, priority){
   var mod = xdc.module('ti.uia.runtime.LoggerProbePoint');
   inst.$object.hdr.priority = Number(priority);
}

/*
 *  ======== getPtrToQueueDescriptorMeta ========
 */
function getPtrToQueueDescriptorMeta(inst){
   return(inst.ptrToQueueDescriptorMeta);
}

/*
 *  ======== setPtrToQueueDescriptorMeta ========
 */
function setPtrToQueueDescriptorMeta(inst,queueDescriptorAdrs){
    inst.ptrToQueueDescriptorMeta = queueDescriptorAdrs;
}

/*
 *  ======== getMetaArgs ========
 *  Returns meta data to support stop-mode RTA.
 */
function getMetaArgs(inst, instNum)
{
    var LoggerProbePoint = xdc.module('ti.uia.runtime.LoggerProbePoint');

    /* Create a new StopModeData structure to populate. */
    var data = new LoggerProbePoint.MetaData();
    data.instanceId = inst.$object.hdr.instanceId;
    data.priority = inst.$object.hdr.priority;
    return (data);
}

/*
 *  ======== validate ========
 *  This function is called by this package's validate() method (defined
 *  in package.xs).
 */
function validate() {
    /* this is the module's object */
    if (!this.$used) {
        return;
    }

    /* If Memory is not used, and the memory policy is not static, it is an
     * error.
     */
    var Defaults = xdc.module('xdc.runtime.Defaults');
    var Types = xdc.module('xdc.runtime.Types');
    if ((Defaults.getCommon(this, "memoryPolicy") != Types.STATIC_POLICY)
            && xdc.module('xdc.runtime.Memory').$used != true) {
        this.$logError("'common$.memoryPolicy' must be 'STATIC_POLICY' "
                + "when 'xdc.runtime.Memory' is not used", this,
                "common$.memoryPolicy");
    }
}

/*
 *  ======== viewInitModule ========
 *  Initializes the Module view in ROV.
 */
function viewInitModule(view, mod)
{
    LoggerProbePoint  = xdc.useModule("ti.uia.runtime.LoggerProbePoint");

    var loggerCircBufModConfig = Program.getModuleConfig(LoggerProbePoint.$name);

    view.isTimestampEnabled = loggerCircBufModConfig.isTimestampEnabled;
    view.enableFlush = loggerCircBufModConfig.enableFlush;
    view.statusLogger = String(loggerCircBufModConfig.statusLogger); 
    if (mod.moduleIdToRouteToStatusLogger == 65535) {
        view.moduleIdToRouteToStatusLogger = "N/A"; 
    }
    else {
        view.moduleIdToRouteToStatusLogger = String(mod.moduleIdToRouteToStatusLogger);
    }
    
    //view.level1Mask = loggerCircBufModConfig.level1Mask;
    //view.level2Mask = loggerCircBufModConfig.level2Mask;
    //view.level3Mask = loggerCircBufModConfig.level3Mask;
    //view.level4Mask = loggerCircBufModConfig.level4Mask;
}

/*
 *  ======== viewInitProxy ========
 *  Initializes the Proxy view in ROV.
 */
function viewInitInstances(view, obj)
{
    /* Retrieve the LoggerProbePoint instance's name */
    view.label = Program.getShortName(obj.$label);
    
    view.enabled = obj.enabled;
    view.transferBufSize = obj.endOfBufferAdrsPlus1 - obj.queueStartAdrs;
    view.maxEventSize = obj.maxEventSize;
    view.droppedEvents = obj.droppedEvents;
    view.serial = obj.serial;
    view.numCores = obj.numCores;
    view.flush = obj.flush;
    view.transferType = obj.transferType;    
}

/*
 *  ======== viewInitRecords ========
 *  Initializes the Records view in ROV.
 */
function viewInitRecords(view, obj)
{
    xdc.loadPackage('ti.uia.runtime');
    var Model = xdc.useModule('xdc.rov.Model');
    var Program = xdc.useModule('xdc.rov.Program');
    var LoggerProbePoint = xdc.useModule('ti.uia.runtime.LoggerProbePoint');
    
    /* Populate the Program.InstDataView structure */
    view.label = Program.getShortName(obj.$label);
    if (view.label.equals("")) {
        view.label = String(obj.$addr);
    }
    
    /* Get the memory reader */
    var memReader = Model.getMemoryImageInst();
        
    /* Initialize the LoggerProbePointDecoder */
    var decoder;
    try {
        decoder = LoggerProbePoint.initDecoder();
    }
    catch (e) {
        print("Caught exception while initiailizing decoder: " + e);
    }
    
    /* Read the buffer. */
    var buffer;
    try {
        buffer =
            decoder.readTargetBuffer(memReader, obj.hdr.queueStartAdrs,
                                     obj.hdr.queueSizeInMAUs, 
                                     obj.hdr.readPtr, obj.hdr.writePtr);
    }
    catch (e) {
        print("Caught exception while reading buffer: " + e);
        
        /* Create a new view element to display the exception. */
        var evtView = Program.newViewStruct('ti.uia.runtime.LoggerProbePoint', 
                                            'Records');
        
        /* Dispaly the exception in the 'serial' field. */
        Program.displayError(evtView, 'serial', 
                             "Caught exception while reading buffer: " + e);
        
        /* Add the element and return. */
        view.elements = [evtView];
        
        return;
    }
    
    /* Decode the buffer and display the records. */
    var eventViews = new Array();    
    
    var offset = 0;
    
    /* 
     * Loop over all of the records in the buffer.
     * 'buffer' contains only valid, contiguous records.
     */
    while (offset < buffer.length) {
        /* Create a new view element. */
        var evtView = 
            Program.newViewStruct('ti.uia.runtime.LoggerProbePoint', 'Records');

        /* Decode the next event. */
        var evt;
        try {
            evt = decoder.decodeEvent(buffer, offset, buffer.length);
            
            /* Fill in the element. */
            evtView.serial = evt.sequenceNum;
            evtView.timestampRaw = evt.timestamp;
            evtView.modName = evt.getModuleName();        
            evtView.text = evt.getEventMsg();
            evtView.eventId = evt.eventId;
            evtView.eventName = evt.getEventName();
            evtView.arg0 = evt.args[0];
            evtView.arg1 = evt.args[1];
            evtView.arg2 = evt.args[2];
            evtView.arg3 = evt.args[3];
            evtView.arg4 = evt.args[4];
            evtView.arg5 = evt.args[5];
            evtView.arg6 = evt.args[6];
            evtView.arg7 = evt.args[7];
            
            /* Move the offset to the next record. */
            offset += decoder.getEventLength(buffer, offset);
        }
        catch (e) {
            print("Caught exception decoding event: " + e);
            
            /* Display the exception in the 'serial' column. */
            Program.displayError(evtView, 'serial', 
                                 "Caught exception while decoding event: " + e);
            
            /* Add the element to the view and return. */
            eventViews[eventViews.length] = evtView;
            
            view.elements = eventViews;
            
            return;
        }

        /* Add the element to the view. */
        eventViews[eventViews.length] = evtView;
    }

    /* Assign the view elements to the view object before returning. */
    view.elements = eventViews;    
}

/*
 *  ======== initDecoder ========
 *  Creates an instance of the ti.uia.runtime.LoggerProbePointDecoder class.
 *  The LoggerProbePoint 'Records' ROV view uses the LoggerProbePointDecoder class 
 *  to decode the raw bytes into xdc.rta.HostEvent objects. This decoder is 
 *  shared between this ROV view and UIA.
 */
function initDecoder()
{      
    var Program = xdc.useModule('xdc.rov.Program');
    var LoggerProbePoint = xdc.useModule('ti.uia.runtime.LoggerProbePoint');
    var Model = xdc.useModule('xdc.rov.Model');
    var Log = xdc.useModule('xdc.runtime.Log');
    
    /* Check if the decoder has already been created. */
    if (LoggerProbePoint.$private.decoder != undefined) {
        return (LoggerProbePoint.$private.decoder);
    }
   
    /* Get the IOFReader instance */
    var ofReader = Model.getIOFReaderInst();

    /* 
     * In order to decode the events in a LoggerProbePoint, the 
     * LoggerProbePointDecoder class requires an object which implements the 
     * IEventMetaData interface to provide log event information such as the
     * mapping of an event id to the event's message. 
     *
     * For ROV, we create a JavaScript object which implements all of the APIs
     * in the IEventMetaData class, then place a Java wrapper on this so that
     * it can be called by the LoggerProbePointDecoder class.
     */
    var eventData = {
        getOFReader: 
            function() { 
                return (ofReader); 
            },
        lookupEventMessage: 
            function (eventId) { 
                return (Log.lookupEventMessage(eventId)); 
            },    
        getTargetArgSize: 
            function() {
                return (Program.build.target.stdTypes.t_IArg.size * 
                        Program.build.target.bitsPerChar / 8); 
            },
        lookupEventName: 
            function(eventId) {
                return (Log.lookupEventName(eventId));
            },
        lookupModuleName: 
            function(modId) {
                return (Log.lookupModuleName(modId)); 
            },
        getTargetEventRecSize: 
            function() {
                return (Log.EventRec.$sizeof() *
                        Program.build.target.bitsPerChar / 8); 
            }
    };
    
    /* Load the Java classes in the xdc.rta package. */
    xdc.loadPackage('xdc.rta');
    
    /* Create the Java wrapper for the IEventMetaData object. */    
    var jEventData = new Packages.xdc.rta.IEventMetaData(eventData);

    /* Required target information */
    var bitsPerChar = Program.build.target.bitsPerChar;    
    var endianStr = Program.build.target.model.endian;
    var endianess = xdc.jre.xdc.rov.TargetType.strToEndianess(endianStr);
    
    /* Create an instance of the LoggerProbePointDecoder */
    var decoder = 
        new Packages.ti.uia.runtime.LoggerProbePointDecoder(endianess, 
                                                         bitsPerChar,
                                                         jEventData);
    
    /* 
     * Store off the LoggerProbePoint Decoder instance so we only have to create it
     * once.
     */
    LoggerProbePoint.$private.decoder = decoder;
    
    return (decoder);
}

/*
 */

/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:25; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

