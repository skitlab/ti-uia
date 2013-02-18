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
 *  ======== LogSync.xs ========
 */
var isEnableDebugPrintf = false;
var finalized = false;
var device;
var platform;
var exeContext;  
var deviceName;
var catalogName; 
var Rta;
var isRtaActive = false;
var isLoggingSetupActive = false;
var isLogSyncActive = false;
var isNonJtagLogger = false;
var isProbePointLogger = false;
var isStreamLogger = false;
var SyncLogger = xdc.module('ti.uia.runtime.LoggerStopMode');

/* ======== isUsedByRta ======== 
 * called from the Rta.module$use(), so it is
 * ok to useModules in this function.
 */
function isUsedByRta(){
        isRtaActive = true;
        isNonJtagLogger = true;
        SyncLogger = xdc.useModule('ti.uia.runtime.LoggerCircBuf');
        if (isEnableDebugPrintf){
                print("UIA LogSync.xs: isUsedByRta = true. ");
        }    
}

function setSyncLogger(loggerModuleName){
   SyncLogger = xdc.useModule(loggerModuleName);
}

/* ======== isUsedByLoggingSetup ======== 
 * called from the LoggingSetup.module$use(), so it is
 * ok to useModules in this function.
 */
function isUsedByLoggingSetup(isNonJtagLoggerFlag, isProbePointLoggerFlag, 
                              isStopModeLoggerFlag, isStreamLoggerFlag, 
                              isIdleLoggerFlag) {
        isLoggingSetupActive = true;
        isNonJtagLogger = isNonJtagLoggerFlag;
        isProbePointLogger = isProbePointLoggerFlag;
        isStreamLogger = isStreamLoggerFlag;
        //TODO: can't do synchronization with ProbePoint loggers!
        if (isIdleLoggerFlag) {
                SyncLogger = xdc.useModule('ti.uia.sysbios.LoggerIdle');
        }
        else if (isNonJtagLogger) {
            SyncLogger = xdc.useModule('ti.uia.runtime.LoggerCircBuf');
        } 
        else {
            if (isStopModeLoggerFlag || isProbePointLoggerFlag){
               SyncLogger = xdc.useModule('ti.uia.runtime.LoggerStopMode');
            }
            else if (isStreamLogger) {
                SyncLogger = xdc.useModule('ti.uia.sysbios.LoggerStreamer');
            }
            else {
               SyncLogger = xdc.useModule('ti.uia.runtime.LoggerCircBuf');
            }    
        }
        if (isEnableDebugPrintf){
            print("UIA LogSync.xs: isLoggingSetupActive = "+isLoggingSetupActive+".  isNonJtagLogger = "+isNonJtagLogger+
            ".  isProbePointLoggerFlag = "+isProbePointLoggerFlag+
            ".  isStopModeLoggerFlag = "+isStopModeLoggerFlag+
            ".  isStreamLogger = "+isStreamLogger+
            ".  SyncLogger = "+SyncLogger);
        }   
}
/*
 *  ======== module$use ========
 */
function module$use() {

        var Types = xdc.module('xdc.runtime.Types');
        var Diags = xdc.module("xdc.runtime.Diags");
        var Text = xdc.module('xdc.runtime.Text');
        var UIASync = xdc.useModule('ti.uia.events.UIASync');
        var IUIATimestampProvider = xdc.useModule('ti.uia.runtime.IUIATimestampProvider');
        var IUIATraceSyncProvider = xdc.useModule('ti.uia.runtime.IUIATraceSyncProvider');
        var IUIATraceSyncClient = xdc.useModule('ti.uia.runtime.IUIATraceSyncClient');
        var IUIAMetaProvider = xdc.useModule('ti.uia.events.IUIAMetaProvider');
        var IUIATransfer = xdc.useModule('ti.uia.runtime.IUIATransfer');
        var Timestamp = xdc.useModule('xdc.runtime.Timestamp');
        var UIAMetaData = xdc.useModule('ti.uia.runtime.UIAMetaData');        
        /* Let other modules do the useModule for the appropriate logger so that
         * e.g. LoggerStopMode is not added unnecessarily to the build.
         *
        var LoggerStopMode = xdc.useModule('ti.uia.runtime.LoggerStopMode'); */

        var QueueDescriptor = xdc.useModule('ti.uia.runtime.QueueDescriptor');
        var TimestampNull;
        device = Program.cpu.deviceName;
        platform = Program.platform;
        exeContext = platform.getExeContext(Program);  
        deviceName = exeContext.deviceName;
        catalogName = exeContext.catalogName;     

        /*!
         *  ======== CpuTimestampProxy ========
         *  This proxy provides a timestamp server that can be different
         *  from the one provided by `{@link xdc.runtime.Timestamp}`. However, if
         *  not supplied by a user, this proxy defaults to whichever timestamp
         *  server is provided by `xdc.runtime.Timestamp`.
         */    
        LogSync = this;

        try{
                if (LogSync.CpuTimestampProxy == null)  {
                        if (isEnableDebugPrintf){
                                print("UIA LogSync.xs: CpuTimestampProxy = null. ");
                        }                       
                        var LocalTimestamp = Timestamp;
                        if (Timestamp == null){
                                TimestampNull = xdc.module('xdc.runtime.TimestampNull');
                                LocalTimestamp = TimestampNull;
                        }
                        if (LocalTimestamp.Module.$name.indexOf('xdc.runtime.TimestampNull')>= 0){
                                if (isEnableDebugPrintf){
                                        print("UIA LogSync.xs: Timestamp maps to TimestampNull. ");
                                }                               

                                /* 
                                 * Determine what the best default timestamp to use is:
                                 * Example of the ti.platforms.evm6472 Platform.xdc contents:
                                readonly config xdc.platform.IExeContext.Cpu CPU = {        
                                        id:             "0",
                                        clockRate:      700,
                                        catalogName:    "ti.catalog.c6000",
                                        deviceName:     "TMS320C6472",
                                        revision:       "",
                                };
                                catalogName for cortexm3: ti.catalog.arm.cortexm3
                                 */

                                if (catalogName.indexOf('ti.catalog.c60000') ){
                                        /* all C6000 devices can use either the ti.uia.family.c64p.TimestampC64XLocal timestamp
                                         or ti.uia.family.c66.TimestampC66Local timestamp to describe the local timestamp.
                                         Determine which is the best fit to avoid confusion */

                                        if ((deviceName.indexOf('C66')>0)||(deviceName.indexOf('TCI66')>0)||(deviceName.indexOf('DM66')>0)){
                                                if (isEnableDebugPrintf){
                                                        print("UIA LogSync.xs: configuring default CpuTimestampProxy to TimestampC66XLocal. ");
                                                }                       
                                                LocalTimestamp = xdc.useModule('ti.uia.family.c66.TimestampC66XLocal');
                                        } else {
                                                if (isEnableDebugPrintf){
                                                        print("UIA LogSync.xs: configuring default CpuTimestampProxy to TimestampC64XLocal. ");
                                                }                       
                                                LocalTimestamp = xdc.useModule('ti.uia.family.c64p.TimestampC64XLocal');
                                        } 

                                } else {
                                        print("Warning: Timestamping of UIA events disabled.  (Timestamp is currently set to"+
                                                        " xdc.runtime.TimestampNull). \n (See ti.uia.runtime.LogSync for more info)");
                                }
                        }
                        LogSync.CpuTimestampProxy = LocalTimestamp;

                        if (isEnableDebugPrintf){
                                print("UIA LogSync.module$use: configuring CpuTimestampProxy to "+
                                                LocalTimestamp);
                                print("UIA LogSync.module$use: LogSync.CpuTimestampProxy.delegate$ = "+
                                                LogSync.CpuTimestampProxy.delegate$);

                        }               
                        LogSync.CpuTimestampProxy.delegate$ = LocalTimestamp;
                        if (isEnableDebugPrintf){
                                print("UIA LogSync.module$use: after assiging delegate$: LogSync."+
                                                "CpuTimestampProxy.delegate$ = "+LogSync.CpuTimestampProxy.delegate$);

                        }               


                } else {
                        xdc.useModule(LogSync.CpuTimestampProxy);
                        xdc.useModule(LogSync.CpuTimestampProxy.delegate$);
                        if (isEnableDebugPrintf){
                                print("UIA LogSync.module$use: CpuTimestampProxy configured by user:\n"+
                                                "   LogSync.CpuTimestampProxy = "+LogSync.CpuTimestampProxy +
                                                "   LogSync.CpuTimestampProxy.delegate$ = "+LogSync.CpuTimestampProxy.delegate$);

                        }                          
                }   
        }
        catch(ex){
                print("UIA LogSync.xs: Error configuring LogSync.CpuTimestampProxy.   "+ex+
                                "\n   Multicore event correlation disabled.");
                LogSync.isEnabled = false;      
        }
        /* disable trace on cpu timestamp proxy to prevent recursive callbacks */
        Diags = xdc.module("xdc.runtime.Diags");
        var modName = LogSync.CpuTimestampProxy.$name;
        Diags.setMaskMeta(modName, Diags.ALL_LOGGING, Diags.ALWAYS_OFF);

        try{
                if (LogSync.GlobalTimestampProxy == null)  {
                        if (isEnableDebugPrintf){
                                print("UIA LogSync.xs: GlobalTimestampProxy == null, so auto-configuring. deviceName = "+deviceName);
                        }
                        var GlobalTimestamp;

                        if ((deviceName.indexOf('C66')>0)||(deviceName.indexOf('TCI66')>0)||(deviceName.indexOf('DM66')>0)){
                                if (isEnableDebugPrintf){
                                        print("UIA LogSync.xs: configuring default GlobalTimestampProxy to "+
                                                        "TimestampC66XGlobal. Setting LogSync.isEnabled = true.");
                                }
                                GlobalTimestamp = xdc.useModule('ti.uia.family.c66.TimestampC66XGlobal');
                                LogSync.isEnabled = true;
                        } else if (deviceName.indexOf('C6472')>0){
                                if (isEnableDebugPrintf){
                                        print("UIA LogSync.xs: configuring default GlobalTimestampProxy to "+
                                                        "TimestampC6472Timer. Setting LogSync.isEnabled = true.");
                                }
                                GlobalTimestamp = xdc.useModule('ti.uia.family.c64p.TimestampC6472Timer');
                                LogSync.isEnabled = true;
                        } else if (deviceName.indexOf('C6474')>0){
                                if (isEnableDebugPrintf){
                                        print("UIA LogSync.xs: configuring default GlobalTimestampProxy to "+
                                                        "TimestampC6474Timer. Setting LogSync.isEnabled = true.");
                                }
                                GlobalTimestamp = xdc.useModule('ti.uia.family.c64p.TimestampC6474Timer');
                                LogSync.isEnabled = true;
                        } else {
                                if (isEnableDebugPrintf){
                                        print("UIA LogSync.xs: configuring default GlobalTimestampProxy to "+
                                                        "TimestampNULL. Setting LogSync.isEnabled = false.");
                                }
                                if (TimestampNull === undefined){
                                        TimestampNull = xdc.useModule('xdc.runtime.TimestampNull');
                                }
                                GlobalTimestamp = TimestampNull;
                                LogSync.isEnabled = false;
                        }

                        LogSync.GlobalTimestampProxy = GlobalTimestamp;
                        LogSync.GlobalTimestampProxy.delegate$ = GlobalTimestamp;

                        if (isEnableDebugPrintf){
                                print("UIA LogSync.module$use: configuring GlobalTimestampProxy to "+GlobalTimestamp);
                                print("UIA LogSync.module$use: LogSync.GlobalTimestampProxy.delegate$ = "+
                                                LogSync.CpuTimestampProxy.delegate$);
                        }                       
                        LogSync.GlobalTimestampProxy.delegate$ = GlobalTimestamp;
                        if (isEnableDebugPrintf){
                                print("UIA LogSync.module$use: After assiging delegate$: LogSync."+
                                                "GlobalTimestampProxy.delegate$ = "+LogSync.GlobalTimestampProxy.delegate$);

                        }               
                } else {
                        xdc.useModule(LogSync.GlobalTimestampProxy);
                        xdc.useModule(LogSync.GlobalTimestampProxy.delegate$);
                        if (isEnableDebugPrintf){
                                print("UIA LogSync.module$use: GlobalTimestampProxy configured by user:\n"+
                                                "   LogSync.GlobalTimestampProxy = "+LogSync.GlobalTimestampProxy +
                                                "   LogSync.GlobalTimestampProxy.delegate$ = "+LogSync.GlobalTimestampProxy.delegate$);

                        }                  
                }       
        }
        catch(ex1){
                print("UIA LogSync.xs: Error configuring LogSync.GlobalTimestampProxy.  "+ex1+
                                "\n   Multicore event correlation disabled.");
                LogSync.isEnabled = false;      
        }

        /* disable trace on global timestamp proxy to prevent recursive callbacks */
        modName = LogSync.GlobalTimestampProxy.delegate$.$name;
        Diags.setMaskMeta(modName, Diags.ALL_LOGGING, Diags.ALWAYS_OFF);    
        if (isEnableDebugPrintf){
                print("UIA: LogSync.module$use: LogSync.CpuTimestampProxy.delegate$ = "+
                                LogSync.CpuTimestampProxy.delegate$);   
                print("UIA: LogSync.module$use: LogSync.GlobalTimestampProxy.delegate$ = "+
                                LogSync.GlobalTimestampProxy.delegate$);   
        }
        var moduleName = ""+LogSync.$name;
        var isEnabled = true;
        isEnabled = LogSync.isEnabled;
                
        UIAMetaData.setLogSyncInfo(moduleName,isEnabled);
                 
}

/*
 *  ======== decode ========
 *  ROV code
 */
function decode( info, evtId, args) {
        var Program = xdc.useModule('xdc.rov.Program');

        info.modName = Program.moduleIdToName(evtId & 0x0000FFFF);
        info.eventId = evtId >> 16;

        /* Look up the event name. */
        info.eventName = evtIdToName(info.eventId);

        for (var i = 0; i < cfg.NUMARGS; i++) {
                info.arg[i] = args[i];
        }

        /* Get the event's formatted message. */
        info.text = getEventMsg(info.eventId, args);
}

/*
 *  ======== Event$alignof ========
 *  Return alignment required for an encoded value of an EventDesc
 */
function Event$alignof() {
        return (Program.build.target.stdTypes.t_Int32.align);
}

/*
 *  ======== Event$encode ========
 *  Return a C expression that evaluates to the encoded value of an EventDesc
 */
function Event$encode( desc) {
        var encodedDesc = "0";
        if (desc) {
                encodedDesc = "(((ti_uia_runtime_LogSync_Event)" + desc.$private.id
                                + ") << 16 | " + (desc.mask & 0xFFFF) + ")";
        }
        return (encodedDesc);
}

/*
 *  ======== Event$sizeof ========
 *  Return sizeof the encoded value of an EventDesc
 */
function Event$sizeof() {
        return (Program.build.target.stdTypes.t_Int32.size);
}

/*
 *  ======== module$static$init ========
 */
function module$static$init( obj, params) {
        var Diags = xdc.module('xdc.runtime.Diags');
        var ITimestampProvider = xdc.module('xdc.runtime.ITimestampProvider');
        var IUIATimestampProvider = xdc.module('ti.uia.runtime.IUIATimestampProvider');
        var IUIATransfer = xdc.module('ti.uia.runtime.IUIATransfer');
        var mod = xdc.module('ti.uia.runtime.LogSync');

        var numModules = 0;
        isLogSyncActive = true; /* flag that is tested in finalize to make sure LogSync was actually configured */

        obj.numTimesHalted = 0;
        obj.serialNumber = 1;
        obj.isEnabled = true;

        if (params.maxGlobalClockFreq.lo === undefined) {
                mod.maxGlobalClockFreq.hi = 0;
                mod.maxGlobalClockFreq.lo = 0;
        }
        if (isEnableDebugPrintf) {
                print("UIA: ti.uia.runtime.LogSync.xs module$static$init()");
                if (mod.common$.logger != null)
                        print("UIA: LogSync.xs logger = "+mod.common$.logger.$orig.$module.$name);
                else
                        print("UIA: LogSync.xs logger = NULL");

        }
        if (isEnableDebugPrintf) {
                print("UIA LogSync.module$static$init: ti.uia.runtime.LogSync.isEnabled = "+mod.isEnabled);

                if (mod.GlobalTimestampProxy.delegate$ instanceof ITimestampProvider.Module) {
                        print("UIA LogSync.module$static$init: mod.GlobalTimestampProxy.delegate$"+
                                        " is an instanceof ITimestampProvider");
                        print("UIA LogSync.module$static$init: mod.GlobalTimestampProxy.delegate$.$orig.$name = "+ 
                                        mod.GlobalTimestampProxy.delegate$.$orig.$name);
                        var GTimestamp = xdc.module(mod.GlobalTimestampProxy.delegate$.$orig.$name);
                        print("UIA: LogSync.xs GTimestamp.$name = "+ GTimestamp.$name);
                        if (GTimestamp instanceof IUIATimestampProvider.Module){
                                print("UIA LogSync.module$static$init: GTimestamp.canCpuCyclesPerTickBeChanged = "+
                                                GTimestamp.canCpuCyclesPerTickBeChanged);
                                print("UIA LogSync.module$static$init: GTimestamp.cpuCyclesPerTick = "+
                                                GTimestamp.cpuCyclesPerTick);
                                print("UIA LogSync.module$static$init: GTimestamp.canFrequencyBeChanged = "+
                                                GTimestamp.canCpuCyclesPerTickBeChanged);
                                print("UIA LogSync.module$static$init: GTimestamp.maxBusClockFreq.lo = "+
                                                GTimestamp.maxBusClockFreq.lo);
                                print("UIA LogSync.module$static$init: GTimestamp.maxBusClockFreq.hi = "+
                                                GTimestamp.maxBusClockFreq.hi);
                        }

                } else {
                        print("UIA LogSync.module$static$init: mod.GlobalTimestampProxy.delegate$ "+
                                        "is NOT an instance of ITimestampProvider.Module!");
                        if (mod.GlobalTimestampProxy.delegate$.$orig instanceof ITimestampProvider.Module) {
                                print("UIA LogSync.module$static$init: mod.GlobalTimestampProxy.$orig is "+
                                                "an instance of ITimestampProvider.Module");
                        } else {
                                print("UIA LogSync.module$static$init: mod.GlobalTimestampProxy.$orig "+
                                                "is NOT an instance of ITimestampProvider.Module!");
                        }
                }
        }

        if (params.maxCpuClockFreq.lo === undefined) {
                mod.maxCpuClockFreq.lo = 1000000.0*exeContext.clockRate;
                mod.maxCpuClockFreq.hi = 0;
        } else {
                mod.maxCpuClockFreq.lo = params.maxCpuClockFreq.lo;
                mod.maxCpuClockFreq.hi = params.maxCpuClockFreq.hi;
        }

        if (params.maxGlobalClockFreq.lo === undefined) {
                mod.maxGlobalClockFreq.lo = 0;
                mod.maxGlobalClockFreq.hi = 0;
        } else {
                mod.maxGlobalClockFreq.lo = params.maxGlobalClockFreq.lo;
                mod.maxGlobalClockFreq.hi = params.maxGlobalClockFreq.hi;
        }        
}

function isLoggerUsedInBuild(loggerMod){
        var result = false;
        for each (var mod in Program.targetModules()) {
                if (mod.$name == loggerMod.$name){
                        result = true;
                        break;
                }
        }
        if (isEnableDebugPrintf) {
                print("LogSync.isLoggerUsedInBuild("+loggerMod.$name+") returned "+result);
        }       
        return result;
}

function configureSyncLogger(){  
        var disableLogSync = false;
        var IUIATransfer = xdc.module('ti.uia.runtime.IUIATransfer');
        var mod = xdc.module('ti.uia.runtime.LogSync');
        mod.$unseal('Module__loggerObj');
        mod.$unseal('Module__loggerDefined');
        if (mod.isEnabled) {
                if (isEnableDebugPrintf) {
                     print("UIA: ti.uia.runtime.LogSync.configureSyncLogger()");
                }
                mod.$unseal('syncLogger');
                if (isEnableDebugPrintf){
                        print("UIA LogSync.xs configureSyncLogger() : mod.syncLogger= "+mod.syncLogger);                
                }                          
                if ((mod.syncLogger == null)||(mod.syncLogger === undefined)){          
                        //   var SyncLogger;

                        if (!isLoggingSetupActive){
                                if (isRtaActive){
                                        /* Sync point events will be logged each time the host
                                         * starts or ends transmission.
                                         */
                                        if (isEnableDebugPrintf) {
                                                print("LogSync: RTA module is used, so LoggerCircBuf should "+
                                                                "be used for SyncLogger. SyncLogger = "+SyncLogger);
                                        }               
                                        SyncLogger = xdc.module('ti.uia.runtime.LoggerCircBuf');
                                } else {

                                        /* Persist the sync-point events by using a 
                                         * LoggerStopMode logger, since the JTAG transport
                                         * will not update the logger's read pointer, leaving
                                         * the original sync point event in the buffer.
                                         */
                                        if (mod.enableEventCorrelationForJTAG){
                                                SyncLogger = xdc.module('ti.uia.runtime.LoggerStopMode');
                                                if (isEnableDebugPrintf) {
                                                        print("LogSync: RTA module is not used, so LoggerStopMode should "+
                                                                        "be used for SyncLogger. SyncLogger = "+SyncLogger);
                                                }                                                      
                                        } else {
                                                if (isEnableDebugPrintf) {
                                                        print("LogSync: isLoggingSetupActive = false, RTA module is not used, "+
                                                                        "enableEventCorrelationForJTAG = false.");
                                                }                                               
                                                disableLogSync = true;
                                        }
                                }
                        } else {
                                var LoggingSetup = xdc.module('ti.uia.sysbios.LoggingSetup');
                                if (isEnableDebugPrintf) {
                                        print("LogSync: LoggingSetup.eventUploadMode="+LoggingSetup.eventUploadMode);
                                }
                                switch (LoggingSetup.eventUploadMode){
                                case LoggingSetup.UploadMode_SIMULATOR:
                                case LoggingSetup.UploadMode_PROBEPOINT:
                                case LoggingSetup.UploadMode_JTAGSTOPMODE:
                                case LoggingSetup.UploadMode_JTAGRUNMODE:
                                    /* Only enable sync point events for JTAG transports if the
                                     * user has explicitly configured the LogSync module to enable
                                     * them (indicating that they will actively log the events)
                                     */
                                    if (mod.enableEventCorrelationForJTAG){
                                            // let the LogSync.isUsedByLoggingSetup function set the SyncLogger
                                            if (isEnableDebugPrintf) {
                                                    print("UIA: ti.uia.runtime.LogSync.configureSyncLogger():"+
                                                                    " LoggingSetup.eventUploadMode = "+LoggingSetup.eventUploadMode+
                                                                    " (JTAG), and enableEventCorrelationForJTAG = true.  SyncLogger = "+SyncLogger);
                                            }                                               
                                            
                                    } else {
                                            if (isEnableDebugPrintf) {
                                                    print("UIA: ti.uia.runtime.LogSync.configureSyncLogger():"+
                                                                    " LoggingSetup.eventUploadMode = "+LoggingSetup.eventUploadMode+
                                                                    " (JTAG), and enableEventCorrelationForJTAG = false. ");
                                            }
                                            disableLogSync = true;
                                    }
                                    break;         
                                case LoggingSetup.UploadMode_NONJTAGTRANSPORT:
                                case LoggingSetup.UploadMode_NONJTAG_AND_JTAGSTOPMODE:
                                    /* Sync point events will be logged each time the host
                                     * starts or ends transmission.  The host will not
                                     * update the loggerCircBuf's read pointer when it reads
                                     * the events, so the last written sync point event
                                     * will remain in the logger's buffer.
                                     */
                                    SyncLogger = xdc.module('ti.uia.runtime.LoggerCircBuf');
                                    break;
                                case LoggingSetup.UploadMode_STREAMER:
                                }       
                        }
                        if (isEnableDebugPrintf) {
                                print("UIA: ti.uia.runtime.LogSync.configureSyncLogger()");
                        }      
                        if (!isLoggerUsedInBuild(SyncLogger)){
                                print("remark: Multicore event correlation disabled! To enable, please add the following line to your .cfg file:\n"+
                                                "    var LoggerSync = xdc.useModule('"+SyncLogger.$name+"');");
                                disableLogSync = true;
                        }
                        if (disableLogSync){
                                if (isEnableDebugPrintf) {
                                        print("UIA: ti.uia.runtime.LogSync.configureSyncLogger():"+
                                                        " Disabling LogSync module.");
                                }
                                mod.$unseal('isEnabled');
                                mod.isEnabled = false;
                                mod.$seal('isEnabled');
                        }

                        if (SyncLogger instanceof IUIATransfer.Module) {
                            /* Create a logger named 'SyncLog' for the LogSync module. 
                             * Using a dedicated log buffer for capturing sync point events is
                             * recommended in order to ensure that sufficient timing information
                             * is captured in order to enable accurate multicore event correlation.
                             */
                            var loggerParams = new SyncLogger.Params();
                            if ("tranferBufSize" in SyncLogger){
                                if (isEnableDebugPrintf) {
                                    print("UIA: ti.uia.runtime.LogSync setting syncLogger.transferBufSize to "+
                                                    mod.defaultSyncLoggerSize);
                                }                               
                                loggerParams.transferBufSize = mod.defaultSyncLoggerSize;
                            } 
                            /* set the priority of the logger to 'highest' */
                            loggerParams.priority = IUIATransfer.Priority_SYNC;
                            var syncLog = SyncLogger.create(loggerParams);
                            syncLog.instance.$unseal('name');
                            syncLog.instance.name = "SyncLog";
                            syncLog.instance.$seal('name');
                            mod.syncLogger = syncLog;
                            mod.common$.logger = syncLog;
                            mod.Module__loggerObj = syncLog;
                            mod.Module__loggerDefined = true;
                            if (isEnableDebugPrintf) {
                                    print("UIA: ti.uia.runtime.LogSync created new syncLogger:["+
                                                    SyncLogger.Module.$name+"] instanceId = "+
                                                    SyncLogger.getLoggerInstanceId(syncLog));
                            }
                        }
                        else {
                            /* Set LogSync to use the LoggerStreamer module.
                             * LoggerStreamer is module based so there are no instances
                             * and the module parameters should not be changed.
                             */
                             mod.syncLogger = SyncLogger.create();
                             mod.common$.logger = mod.syncLogger;
                             mod.Module__loggerObj = mod.syncLogger;
                             mod.Module__loggerDefined = true;                                                   
                             if (isEnableDebugPrintf) {
                                    print("UIA: ti.uia.runtime.LogSync created new LoggerStreamer syncLogger:["+
                                                    SyncLogger.Module.$name+"]");
                            }
                        }
                } else {
                    /* Logger assigned by user.*/
                    if ("priority" in mod.syncLogger) {
                        if (isEnableDebugPrintf) {
                             print("UIA: ti.uia.runtime.LogSync syncLogger.priority set to Priority_SYNC");
                        }
                        /* Ensure that the priority of the logger is set to 'highest' */
                        SyncLogger.setLoggerPriority(mod.syncLogger,IUIATransfer.Priority_SYNC);
                    }
                    if ("isSyncPointLogger" in mod.syncLogger) {
                        if (isEnableDebugPrintf) {
                             print("UIA: ti.uia.runtime.LogSync syncLogger.isSyncPointLogger set to TRUE");
                        }
                        /* Tag the logger as being used to log sync points so that it can 
                                                 * generate the correct metadata to allow System Analyzer to route the data accordingly */
                        SyncLogger.setIsSyncPointLogger(true);
                    }
                    mod.common$.logger = mod.syncLogger;
                    mod.Module__loggerDefined = true;
                    mod.Module__loggerObj = mod.syncLogger;
                    if (isEnableDebugPrintf) {
                                print("UIA: ti.uia.runtime.LogSync using user-created syncLogger:["+
                                                SyncLogger.Module.$name+"]");
                    }
                }
                if ((isEnableDebugPrintf) && ("priority" in mod.syncLogger)){
                        var theLogger = mod.common$.logger;
                        print("UIA: ti.uia.runtime.LogSync.syncLogger: instanceId = "+
                                        theLogger.$module.getLoggerInstanceId(theLogger)+
                                        ", priority = "+theLogger.$module.getLoggerPriority(theLogger));
                }
                mod.$seal('syncLogger');

        } 
        if (!mod.isEnabled) {
                // not enabled
                mod.Module__loggerDefined = false;
                mod.Module__loggerObj = null;
                if (isEnableDebugPrintf) {
                        print("UIA: ti.uia.runtime.LogSync.isEnabled = false - event correlation disabled");
                }
        }
        mod.$seal('Module__loggerObj');
        mod.$seal('Module__loggerDefined');
        //initClockSettings();
                
         if (isEnableDebugPrintf) {
            print("UIA: LogSync.configureSyncLogger complete. LogSync.common$.logger = "+mod.common$.logger);
         }              
}

function initClockSettings(){
        var ITimestampProvider = xdc.module('xdc.runtime.ITimestampProvider');
        var IUIATimestampProvider = xdc.module('ti.uia.runtime.IUIATimestampProvider');
        var mod = xdc.module('ti.uia.runtime.LogSync');
        if (mod.isEnabled) {

                /*
                 * ======== cpuTimestamp parameters ========
                 * Provide default values for maxCpuClockFreq if undefined or 0.  
                 * TODO: get these from the Settings module.
                 */
                if (mod.maxCpuClockFreq.lo === undefined){
                        mod.maxCpuClockFreq.lo = 1000000.0*exeContext.clockRate;
                        mod.maxCpuClockFreq.hi = 0;
                }

                if (mod.maxCpuClockFreq.hi === undefined){
                        mod.maxCpuClockFreq.hi = 0;
                }

                if ((mod.maxCpuClockFreq.lo == 0)&&(mod.maxCpuClockFreq.hi == 0)){
                        mod.maxCpuClockFreq.lo = 1000000.0*exeContext.clockRate;
                        mod.maxCpuClockFreq.hi = 0;             
                }
                /*
                 * ======== globalTimestamp parameters ========
                 * Automatically copy this value from the GlobalTimestampProxy.cpuCyclesPerTick 
                 * configuration value at configuration time if GlobalTimestampProxy.cpuCyclesPerTick > 0.
                 */    
                if ((mod.GlobalTimestampProxy != null) && 
                                (mod.GlobalTimestampProxy.delegate$ instanceof IUIATimestampProvider.Module)){
                        var gtsMod = xdc.module(mod.GlobalTimestampProxy.delegate$.$orig.$name);
                        /* Note: since the timer frequency is derived by dividing the timer's bus clock frequency
                         * by some integer number of cycles, we will often get non-integer timer frequency values.
                         * To avoid this, the sync point events log the bus clock frequency and the cycles per tick
                         * values so that the division can be done by the host to maintain accuracy.
                         */
                        if ((mod.maxGlobalClockFreq.lo == 0)&&(mod.maxGlobalClockFreq.hi == 0)) {
                                if ((gtsMod.maxBusClockFreq.lo === undefined)||(gtsMod.maxBusClockFreq.hi === undefined)) {
                                        mod.maxGlobalClockFreq.hi = 0;
                                        mod.maxGlobalClockFreq.lo = 0;    
                                } else {
                                        mod.maxGlobalClockFreq.lo = gtsMod.maxBusClockFreq.lo;
                                        mod.maxGlobalClockFreq.hi = gtsMod.maxBusClockFreq.hi;
                                        mod.$unseal('globalTimestampCpuCyclesPerTick');
                                        mod.globalTimestampCpuCyclesPerTick = gtsMod.cpuCyclesPerTick;
                                        mod.$seal('globalTimestampCpuCyclesPerTick');
                                }
                                if (isEnableDebugPrintf) {
                                        print("UIA: LogSync.xs: Changed maxGlobalClockFreq.lo to "+
                                                        mod.maxGlobalClockFreq.lo+", globalTimestampCpuCyclesPerTick = "+
                                                        mod.globalTimestampCpuCyclesPerTick);
                                }
                        }
                } else {
                        /* make sure everything is initialized in order to avoid build errors */
                        if (mod.maxGlobalClockFreq.lo === undefined)  {
                                mod.maxGlobalClockFreq.$unseal('lo');
                                mod.maxGlobalClockFreq.lo = 0;
                                mod.maxGlobalClockFreq.$seal('lo');
                        }
                        if (mod.maxGlobalClockFreq.hi === undefined) {
                                mod.maxGlobalClockFreq.$unseal('hi');         
                                mod.maxGlobalClockFreq.hi = 0;        
                                mod.maxGlobalClockFreq.$seal('hi');         
                        }

                        var disable = false;
                        if ((mod.GlobalTimestampProxy == null)||(mod.GlobalTimestampProxy.delegate$ == null)) {
                                disable = true;
                                // fail quietly in order to support cases where multicore
                                // event correlation is not desired.
                        } else if ((mod.maxGlobalClockFreq.lo == 0) && 
                                        (mod.maxGlobalClockFreq.hi == 0)){
                                disable = true;
                                print("Warning: UIA Event correlation disabled.  "+
                                                "Please configure LogSync.globalClkFreq (.lo,.hi)"+
                                                " to a non-zero value to enable.");        
                        }
                        if (disable){
                                mod.$unseal('isEnabled');
                                mod.isEnabled = false;
                                mod.$seal('isEnabled');                   
                        }
                }


                if (isEnableDebugPrintf) {
                        print("UIA: LogSync.initClockSettings(): LogSync.GlobalTimestampProxy.delegate$ = "+
                                        mod.GlobalTimestampProxy.delegate$);            
                        print("UIA: LogSync.globalTimestampCpuCyclesPerTick="+mod.globalTimestampCpuCyclesPerTick);
                        print("UIA: LogSync.maxGlobalClockFreq.hi="+mod.maxGlobalClockFreq.hi);        
                        print("UIA: LogSync.maxGlobalClockFreq.lo="+mod.maxGlobalClockFreq.lo);        
                }
        }  else {
                /* make sure everything is initialized in order to avoid build errors */

                mod.maxGlobalClockFreq.$unseal('lo');
                mod.maxGlobalClockFreq.lo = 0;
                mod.maxGlobalClockFreq.$seal('lo');       
                mod.maxGlobalClockFreq.$unseal('hi');         
                mod.maxGlobalClockFreq.hi = 0;        
                mod.maxGlobalClockFreq.$seal('hi');          
        }
}
/*
 *  ======== writeUIAMetaData ========
 * generates XML metadata describing the clocks used for multicore correlation
 *
 *  NOTE: This should only be called by ti.uia.runtime.UIAMetaData.xs in order
 *  to ensure that the UIA xml file has been properly opened and is ready for
 *  writing.
 *  @param(inst) instance of the module to generate data for, null for module-level info 
 *  @param(instNum) the instance number used in .h files
 *  @param(indent) the number of spaces to preceed the xml tag with     
 */
function writeUIAMetaData(inst, instNum, indent)
{
        var mod = xdc.module('ti.uia.runtime.LogSync');
        if (isLogSyncActive){
                var IUIATimestampProvider = xdc.useModule('ti.uia.runtime.IUIATimestampProvider');
                var ITimestampProvider = xdc.useModule('xdc.runtime.ITimestampProvider');
                var UIAMetaData = xdc.module('ti.uia.runtime.UIAMetaData');
                var gtsMod = null;
                if ((mod.GlobalTimestampProxy != null)&&(mod.GlobalTimestampProxy.delegate$ != null)) {
                        gtsMod = mod.GlobalTimestampProxy.delegate$;  
                        if (isEnableDebugPrintf) {
                                print("UIA: LogSync.writeUIAMetaData LogSync.GlobalTimestampProxy.delegate$ = "+
                                                LogSync.GlobalTimestampProxy.delegate$);
                        }
                }
                if (isEnableDebugPrintf) {
                        print("UIA: LogSync.writeUIAMetaData instNum = "+instNum);
                        print("UIA: LogSync.isEnabled = "+ mod.isEnabled);
                        if (gtsMod == null){
                                print("UIA: LogSync.GlobalTimestampProxy = null");              
                        } else {
                                print("UIA: LogSync.GlobalTimestampProxy = "+gtsMod.$name);
                        }
                        if (mod.common$.logger != null){
                                print("UIA: LogSync.common$.logger = "+mod.common$.logger);
                        } else {
                                print("UIA: LogSync.common$.logger = null");
                        }
                        if (gtsMod instanceof IUIATimestampProvider.Module){
                                print("UIA: LogSync.GlobalTimestampProxy instanceof IUIATimestampProvider = true");
                        } else {
                                print("UIA: LogSync.GlobalTimestampProxy instanceof IUIATimestampProvider = false");
                        } 
                }
                var turnOffLogSync = false;

                if ((mod.syncLogger == null)||(gtsMod == null)){
                        turnOffLogSync = true;
                        if (isEnableDebugPrintf) {                                              
                             print("UIA: LogSync: setting turnOffLogSync = true and LogSync.isEnabled = false. mod.syncLogger = "+mod.syncLogger+
                             ", mod.common$.logger = "+mod.common$.logger+",gtsMod = "+gtsMod);
                        }
                } else {
                       if (mod.common$.logger == null){
                            mod.common$.logger = mod.syncLogger;
                       }
                }
                                
                if (turnOffLogSync){
                        mod.$unseal('isEnabled');
                        mod.isEnabled = false;
                        mod.$seal('isEnabled');
                }

                /* If LogSync is not enabled, then UIAMetaData.xs will handle it
                 * as if the user did not include the LogSync module at all.
                 * Only emit metadata if the module is enabled.
                 */
                if (mod.isEnabled) {
                        UIAMetaData.genXmlEntryOpen(indent,"eventCorrelation");
                        var LoggerCircBuf = xdc.module('ti.uia.runtime.LoggerCircBuf');
                        var IUIATransfer = xdc.module('ti.uia.runtime.IUIATransfer');
                        var ctsMod = mod.CpuTimestampProxy;
                        var syncLogger = mod.common$.logger;
                        var syncLoggerModule = mod.common$.logger.$module;
                        var instanceId = "";
                        UIAMetaData.genXmlEntry(indent+3,"isEnabled", "true");
                        indent = indent+3;

                        UIAMetaData.genXmlEntryOpen(indent,"syncPointLogger");
                        UIAMetaData.genXmlEntry(indent+3,"moduleName", syncLoggerModule.$name);
                        UIAMetaData.genXmlEntry(indent+3,"moduleId", syncLoggerModule.Module__id.toString());
                        instanceId = "" + syncLogger.$module.getLoggerInstanceId(syncLogger);
                        UIAMetaData.genXmlEntry(indent+3,"instanceId", instanceId);
                        if ((mod.injectIntoTraceFxn == null)||(mod.isInjectIntoTraceEnabled == false)) {
                                UIAMetaData.genXmlEntry(indent+3,"isInjectIntoTraceEnabled","false");
                        } else {
                                UIAMetaData.genXmlEntry(indent+3,"isInjectIntoTraceEnabled","true");
                                var strFxn = ""+mod.injectIntoTraceFxn;
                                var indexOfAmp = strFxn.indexOf("&");
                                if (indexOfAmp >= 0){
                                        strFxn = strFxn.substring(indexOfAmp+1);
                                }  
                                UIAMetaData.genXmlEntry(indent+3,"injectIntoTraceFxn",strFxn);
                        }
                        UIAMetaData.genXmlEntryClose(indent,"syncPointLogger");
                        UIAMetaData.genXmlEntryOpen(indent,"cpuTimestamp");
                        UIAMetaData.genXmlEntry(indent+3,"moduleName", ctsMod.delegate$.$name);
                        UIAMetaData.genXmlEntry(indent+3,"moduleId", ctsMod.delegate$.Module__id.toString());
                        UIAMetaData.genXmlEntry(indent+3,"maxTimerFreqMSW",""+mod.maxCpuClockFreq.hi);
                        UIAMetaData.genXmlEntry(indent+3,"maxTimerFreqLSW",""+mod.maxCpuClockFreq.lo);
                        UIAMetaData.genXmlEntry(indent+3,"canFrequencyBeChanged",""+mod.canCpuFrequencyBeChanged);
                        UIAMetaData.genXmlEntry(indent+3,"cyclesPerTick", ""+mod.cpuTimestampCyclesPerTick);
                        UIAMetaData.genXmlEntry(indent+3,"canCyclesPerTickBeChanged",""+mod.canCpuCyclesPerTickBeChanged);
                        UIAMetaData.genXmlEntryClose(indent,"cpuTimestamp");

                        UIAMetaData.genXmlComment(indent,"Global timer: maxClockFreq is the bus frequency "+
                                        "that clocks the timer, maxTimerFreq is the tick count frequency")
                                        UIAMetaData.genXmlEntryOpen(indent,"globalClock");

                        if (gtsMod instanceof IUIATimestampProvider.Module){
                                var GTimestamp = xdc.module(mod.GlobalTimestampProxy.delegate$.$orig.$name);
                                if (isEnableDebugPrintf){
                                        print("LogSync.writeUIAMetaData: GlobalTimestamp maxBusClockFreq.lo = "+GTimestamp.maxBusClockFreq.lo);
                                        print("LogSync.writeUIAMetaData: GlobalTimestamp maxTimerClockFreq.lo = "+GTimestamp.maxTimerClockFreq.lo);
                                }        
                                UIAMetaData.genXmlEntry(indent+3,"maxClockFreqMSW",""+GTimestamp.maxBusClockFreq.hi);
                                UIAMetaData.genXmlEntry(indent+3,"maxClockFreqLSW",""+GTimestamp.maxBusClockFreq.lo);
                                UIAMetaData.genXmlEntry(indent+3,"canFrequencyBeChanged",""+GTimestamp.canFrequencyBeChanged);
                                UIAMetaData.genXmlEntryClose(indent,"globalClock");
                                UIAMetaData.genXmlEntryOpen(indent,"globalTimestamp");
                                UIAMetaData.genXmlEntry(indent+3,"moduleName", gtsMod.$name);
                                UIAMetaData.genXmlEntry(indent+3,"moduleId", gtsMod.Module__id.toString());
                                UIAMetaData.genXmlEntry(indent+3,"maxTimerFreqMSW",""+GTimestamp.maxTimerClockFreq.hi);
                                UIAMetaData.genXmlEntry(indent+3,"maxTimerFreqLSW",""+GTimestamp.maxTimerClockFreq.lo);
                                UIAMetaData.genXmlEntry(indent+3,"canFrequencyBeChanged",""+GTimestamp.canFrequencyBeChanged);
                                UIAMetaData.genXmlEntry(indent+3,"cyclesPerTick", ""+GTimestamp.cpuCyclesPerTick);
                                UIAMetaData.genXmlEntry(indent+3,"canCyclesPerTickBeChanged",""+GTimestamp.canCpuCyclesPerTickBeChanged);
                                UIAMetaData.genXmlEntryClose(indent,"globalTimestamp");
                        } else {
                                UIAMetaData.genXmlEntry(indent+3,"maxClockFreqMSW",""+mod.maxGlobalClockFreq.hi);
                                UIAMetaData.genXmlEntry(indent+3,"maxClockFreqLSW",""+mod.maxGlobalClockFreq.lo);
                                UIAMetaData.genXmlEntry(indent+3,"canFrequencyBeChanged","false");
                                UIAMetaData.genXmlEntryClose(indent,"globalClock");
                                UIAMetaData.genXmlEntryOpen(indent,"globalTimestamp");
                                UIAMetaData.genXmlEntry(indent+3,"moduleName", gtsMod.$name);
                                UIAMetaData.genXmlEntry(indent+3,"moduleId", gtsMod.Module__id.toString());
                                var timerFreqLo = mod.maxGlobalClockFreq.lo;
                                var timerFreqHi = mod.maxGlobalClockFreq.hi;
                                if (mod.globalTimestampCpuCyclesPerTick > 0){
                                        timerFreqLo = timerFreqLo / mod.globalTimestampCpuCyclesPerTick;
                                        timerFreqHi = timerFreqHi / mod.globalTimestampCpuCyclesPerTick;
                                }
                                UIAMetaData.genXmlEntry(indent+3,"maxTimerFreqMSW",""+timerFreqHi);
                                UIAMetaData.genXmlEntry(indent+3,"maxTimerFreqLSW",""+timerFreqLo);
                                UIAMetaData.genXmlEntry(indent+3,"canFrequencyBeChanged","false");
                                UIAMetaData.genXmlEntry(indent+3,"cyclesPerTick", ""+mod.globalTimestampCpuCyclesPerTick);
                                UIAMetaData.genXmlEntry(indent+3,"canCyclesPerTickBeChanged","false");
                                UIAMetaData.genXmlEntryClose(indent,"globalTimestamp");
                        }
                        indent = indent - 3;
                        UIAMetaData.genXmlEntryClose(indent,"eventCorrelation");
                }
        }
}    

/*
 * ======== finalize ========
 * get configured clock settings from timer modules and configure logger to log
 * sync events with
 */
function finalize(){
        if (!finalized){
                var LogSync = xdc.module('ti.uia.runtime.LogSync');
                var Rta = xdc.module('ti.uia.services.Rta');
                var LoggerStopMode = xdc.module('ti.uia.runtime.LoggerStopMode');
                var IUIATransfer = xdc.module('ti.uia.runtime.IUIATransfer');
                if (isEnableDebugPrintf){
                        print("UIA LogSync.xs finalize() : LogSync.syncLogger= "+LogSync.syncLogger);
                        print("UIA LogSync.xs finalize() : isLogSyncActive = "+isLogSyncActive+
                                        ", isRtaActive = "+isRtaActive+", isEnabled = "+LogSync.isEnabled);
                }       
                if (isLogSyncActive){
                        initClockSettings();
                        configureSyncLogger();
                        if ((isRtaActive)&&(SyncLogger != null)){
                                if ((!(SyncLogger instanceof LoggerStopMode.Module)) && (SyncLogger instanceof IUIATransfer.Module)){
                                        if (isEnableDebugPrintf){
                                                print("UIA LogSync.xs calling Rta.registerLoggers.");
                                        }                  
                                        Rta.registerLoggers(Rta.$object);      
                                } else {
                                        if (isEnableDebugPrintf){
                                                print("UIA LogSync.xs not calling Rta.registerLoggers.  SyncLogger either LoggerStopMode or not IUIATransfer.");
                                        }                           
                                }
                        }
                        finalized = true;
                        if (isEnableDebugPrintf){
                                print("UIA LogSync.xs finalize() completed.");
                        }      
                }
        }
}

/*
 *  ======== viewInitModule ========
 *  Initializes the Module view in ROV.
 */
function viewInitModule(view, mod)
{
        LogSync  = xdc.useModule("ti.uia.runtime.LogSync");

        var logSyncModConfig = Program.getModuleConfig(LogSync.$name);

        view.numTimesHalted = logSyncModConfig.numTimesHalted;
        view.serialNumber = logSyncModConfig.serialNumber;
        view.isEnabled = logSyncModConfig.isEnabled;
}
/*
 *  ======== validate ========
 */
function validate()
{
        /* Only process during "cfg" phase */
        if (xdc.om.$name != "cfg") {
                return;
        }
        if (!finalized)
                finalize();

}


/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:24; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

