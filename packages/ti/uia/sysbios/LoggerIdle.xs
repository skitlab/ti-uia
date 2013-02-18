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
 *  ======== LoggerIdle.xs ========
 */

var LoggerIdle;
var Timestamp;
var Types;
var UIAMetaData;
var EventHdr;

/*
 *  ======== module$use ========
 */
function module$use()
{
    LoggerIdle = this;
    
    Idle = xdc.useModule("ti.sysbios.knl.Idle");
    Types = xdc.useModule('xdc.runtime.Types');    
    Timestamp = xdc.useModule('xdc.runtime.Timestamp');
    EventHdr = xdc.useModule('ti.uia.runtime.EventHdr');
    UIAMetaData = xdc.useModule('ti.uia.runtime.UIAMetaData');
        
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{    
    Idle.addFunc(LoggerIdle.idleWrite);
    if (params.transportFxn == null) {
        this.$logError("LoggerIdle cannot have a null transport function", this);
    } 
    mod.loggerFxn = params.transportFxn;
    mod.enabled = true;
    mod.empty = true;
    mod.idleSequence = 0;
    mod.bufferSize = params.bufferSize;
    mod.idleBuffer.length = params.bufferSize;
    mod.bufferRead = mod.idleBuffer.$addrof(0);
    mod.bufferWrite = mod.idleBuffer.$addrof(0);
    mod.bufferPad = mod.idleBuffer.$addrof(params.bufferSize - 1);
    if (params.isTimestampEnabled) {
        mod.bufferEnd = mod.idleBuffer.$addrof(params.bufferSize - 12);
    }
    else {
        mod.bufferEnd = mod.idleBuffer.$addrof(params.bufferSize - 10);
    }
    
    var transportType;    
    switch(params.transportType){
        case this.TransportType_UART:
            transportType = "UART";
            break;
        case this.TransportType_USB:
            transportType = "USB";
            break;
        case this.TransportType_ETHERNET:
            transportType = "ETHERNET";
            break;
        case this.TransportType_CUSTOM:
            transportType = "CUSTOM";
            break;
        default:
            //TODO build error/warning?
            break;        
    }
    UIAMetaData.setTransportFields(false, 
                                   UIAMetaData.UploadMode_NONJTAGTRANSPORT,
                                   transportType, 
                                   "UIAEVENTHDR", false, 
                                   params.customTransportType);
}

/*
 *  ======== instance$static$init ========
 */
function instance$static$init(obj, params)
{
}

/*
 *  ======== viewInitModule ========
 *  Initializes the Module view in ROV.
 */
function viewInitModule(view, mod)
{
    LoggerIdle  = xdc.useModule("ti.uia.sysbios.LoggerIdle");
    var loggerIdleModConfig = Program.getModuleConfig(LoggerIdle.$name);

    /* Populate ROV module view */
    view.isEnabled = mod.enabled;
    view.isTimestampEnabled = loggerIdleModConfig.isTimestampEnabled;
    view.bufferSize = loggerIdleModConfig.bufferSize;
    view.sequenceNumber = mod.idleSequence;
    view.transportType = loggerIdleModConfig.transportType; 
    if (loggerIdleModConfig.transportType == 
        LoggerIdle.TransportType_CUSTOM) {
        view.customTransport = loggerIdleModConfig.customTransport;
    }
    else {
        view.customTransport = "N/A"
    }
}

/*
 *  ======== viewInitRecords ========
 *  Initializes the Records view in ROV.
 */
function viewInitRecords(view)
{
    xdc.loadPackage('ti.uia.runtime');
    xdc.loadPackage('ti.uia.sysbios');
    var Model = xdc.useModule('xdc.rov.Model');
    var Program = xdc.useModule('xdc.rov.Program');
    var LoggerCircBuf = xdc.useModule('ti.uia.runtime.LoggerCircBuf');
    var loggerIdleModConfig = Program.getModuleConfig(LoggerIdle.$name);
    var timestamp = loggerIdleModConfig.isTimestampEnabled;
    
    /* 
     * Retrieve the module's state. 
     * If this throws an exception, just allow it to propogate up.
     */
    var rawView = Program.scanRawView('ti.uia.sysbios.LoggerIdle');

    /* Get the memory reader */
    var memReader = Model.getMemoryImageInst();
        
    /* Initialize the LoggerCircBufDecoder */
    var decoder;
    try {
        decoder = LoggerCircBuf.initDecoder();
    }
    catch (e) {
        print("Caught exception while initiailizing decoder: " + e);
    }
    
    if (rawView.modState.empty) {
        return;
    }
    
    /* Read the buffer. */
    var buffer;
    try {
        if (Number(rawView.modState.bufferRead) == Number(rawView.modState.bufferWrite)) {
            if (Number(rawView.modState.bufferWrite) == Number(rawView.modState.idleBuffer)) {
                buffer =
                decoder.readTargetBuffer(memReader, rawView.modState.idleBuffer,
                                         (rawView.modState.bufferPad + 4) - rawView.modState.idleBuffer, 
                                         rawView.modState.bufferRead, rawView.modState.bufferPad);
            }
            else {
                buffer =
                decoder.readTargetBuffer(memReader, rawView.modState.idleBuffer,
                                         (rawView.modState.bufferPad + 4) - rawView.modState.idleBuffer, 
                                         rawView.modState.bufferRead, (rawView.modState.bufferWrite - 4));
            }                
        }
        else if (Number(rawView.modState.bufferWrite) > Number(rawView.modState.bufferRead)) {
            buffer =
            decoder.readTargetBuffer(memReader, rawView.modState.idleBuffer,
                                     rawView.modState.bufferPad - rawView.modState.idleBuffer + 4, 
                                     rawView.modState.idleBuffer, rawView.modState.bufferWrite);
        }
        else {
            buffer =
            decoder.readTargetBuffer(memReader, rawView.modState.idleBuffer,
                                     rawView.modState.bufferPad - rawView.modState.idleBuffer + 4, 
                                     rawView.modState.bufferRead, rawView.modState.bufferWrite);
        }
    }
    catch (e) {
        print("Caught exception while reading buffer: " + e);
        
        /* Create a new view element to display the exception. */
        var evtView = Program.newViewStruct('ti.uia.sysbios.LoggerIdle', 
                                            'Records');
        
        /* Dispaly the exception in the 'sequence' field. */
        Program.displayError(evtView, 'sequence', 
                             "Caught exception while reading buffer: " + e);
        
        /* Add the element and return. */
        view.elements = [evtView];
        
        return;
    }
    
    /* Decode the buffer and display the records. */
    var eventViews = new Array();
    var offset = 0;             /* Offset */
    var evtView =                 /* Create a new view element. */
        Program.newViewStruct('ti.uia.sysbios.LoggerIdle', 'Records');
    var evt;                    /* Host event */
    var match = false;            /* found a valid event */
    
    /* Find the first host event */
    for (var i = 2; i < buffer.length - 1; i++) {
        /* Event length a multiple of four and correct event type */
        if ( (buffer[i] % 4 == 0) && (buffer[i] != 0) && ((timestamp && buffer[i+1] == 8) || (!timestamp && buffer[i+1] == 0) ) ) {
            var tempEvt = decoder.decodeEvent(buffer, i - 2, buffer.length);
            /* Check if the event is valid */
            if (tempEvt != null 
                && tempEvt.getModuleName() != null 
                && tempEvt.getEventMsg() != null 
                && tempEvt.getEventName() != null) {
                evt = tempEvt;
                offset = i - 2;
                match = true;
                break;
            }
        }
    }
    
    /* Add event to ROV view */
    if (match) {
        evtView.sequence = evt.sequenceNum;
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
        
        /* Add the element to the view. */
        eventViews[eventViews.length] = evtView;
    }
    else {
        offset = buffer.length;
    }
    
    /* process rest of events */
    while (offset < buffer.length) {
        /* Create a new view element. */
        var evtView = 
            Program.newViewStruct('ti.uia.sysbios.LoggerIdle', 'Records');
            
        /* Decode the next event. */
        var evt;
        try {
            evt = decoder.decodeEvent(buffer, offset, buffer.length);
            
            /* Fill in the element. */
            evtView.sequence = evt.sequenceNum;
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
            print("offset: ", +offset);
            
            /* Display the exception in the 'sequence' column. */
            Program.displayError(evtView, 'sequence', 
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
 *  @(#) ti.uia.sysbios; 1, 0, 0, 0,1; 7-13-2012 11:12:38; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

