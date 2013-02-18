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
 *  ======== LoggingSetup.xs ========
 */

var LoggingSetup;
var Logger;
var Load;
var Diags;
var Main;
var isOverflowLoggerAssigned = false;
var isEnableDebugPrintf = false;
var loggerStream = null;
var loggerIdle = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    var logger;
    /* Use the most common event defintion modules */
    var UIAEvt = xdc.useModule('ti.uia.events.UIAEvt');
    var UIAErr = xdc.useModule('ti.uia.events.UIAErr');
    var UIABenchmark = xdc.useModule('ti.uia.events.UIABenchmark');
    var UIARoundtrip = xdc.useModule('ti.uia.events.UIARoundtrip');
    var UIAStatistic = xdc.useModule('ti.uia.events.UIAStatistic');
    var UIAMetaData = xdc.useModule('ti.uia.runtime.UIAMetaData');

    /* Work-around to TimestampProvider plugging issue with pre-BIOS 6.32 */
    var Settings = xdc.module("ti.sysbios.family.Settings");
    xdc.useModule(Settings.getDefaultTimestampDelegate());

    LoggingSetup = this;

    UIAMetaData.setLoggingSetupConfigured();

    Diags = xdc.useModule('xdc.runtime.Diags');
    if (!LoggingSetup.disableMulticoreEventCorrelation){
        /* provide enough info to the LogSync module so that it can
         * use the correct type of logger to log the sync points with
         */
        var isNonJtagLogger = false;
        var isProbePointLogger = false;
        var isStopModeLogger = false;
        var isStreamLogger = false;
        var isIdleLogger = false;
        switch (LoggingSetup.eventUploadMode){
        case LoggingSetup.UploadMode_SIMULATOR:
        case LoggingSetup.UploadMode_PROBEPOINT:
            isProbePointLogger = true;
            xdc.useModule('ti.uia.runtime.LoggerStopMode');
            break;
        case LoggingSetup.UploadMode_JTAGSTOPMODE:
            isStopModeLogger = true;
            xdc.useModule('ti.uia.runtime.LoggerStopMode');
            break;
        case LoggingSetup.UploadMode_JTAGRUNMODE:
            xdc.useModule('ti.uia.runtime.LoggerCircBuf');
            break;
        case LoggingSetup.UploadMode_NONJTAGTRANSPORT:
        case LoggingSetup.UploadMode_NONJTAG_AND_JTAGSTOPMODE:
            isNonJtagLogger = true;
            xdc.useModule('ti.uia.runtime.LoggerCircBuf');
            break;
        case LoggingSetup.UploadMode_STREAMER:
            isStreamLogger = true;
            xdc.useModule('ti.uia.sysbios.LoggerStreamer');
            break;
        case LoggingSetup.UploadMode_IDLE:
            isIdleLogger = true;
            xdc.useModule('ti.uia.sysbios.LoggerIdle');
            break;
        }

        var LogSync = xdc.useModule('ti.uia.runtime.LogSync');
        LogSync.isUsedByLoggingSetup(isNonJtagLogger, isProbePointLogger,
                                     isStopModeLogger, isStreamLogger, isIdleLogger);
    }

    /* Setup the Load modules loggers and diags mask */
    if (LoggingSetup.loadLogging == true) {

        var setting = getDiagsSetting(LoggingSetup.loadLogging,
                                  LoggingSetup.loadLoggingRuntimeControl);

        /* Turn on the Load module diags mask */
        var Load = xdc.useModule('ti.sysbios.utils.Load');

        if (Load.common$.diags_USER4 === undefined) {
            Load.common$.diags_USER4 = setting;
        }

        /* If no logger supplied to this module, create one */
        if (LoggingSetup.loadLogger == null) {
            /* Create the logger instance */
            logger = createLogger(LoggingSetup.loadLoggerSize,"Load Logger",null);
        }
        else {
            logger = LoggingSetup.loadLogger;
        }

        /* Plug it*/
        setLogger(Load, logger);
    }

    /* Setup Main and non-xdc modules loggers and diags mask */
    if (LoggingSetup.mainLogging == true) {

        var setting = getDiagsSetting(LoggingSetup.mainLogging,
                                  LoggingSetup.mainLoggingRuntimeControl);

        /* Turn on the Main module diags mask */
        var Main = xdc.useModule('xdc.runtime.Main');

        if (Main.common$.diags_STATUS === undefined) {
            Main.common$.diags_STATUS = setting;
        }
        if (Main.common$.diags_ANALYSIS === undefined) {
            Main.common$.diags_ANALYSIS = setting;
        }
        if (Main.common$.diags_INFO === undefined) {
            Main.common$.diags_INFO = setting;
        }
        if (Main.common$.diags_USER1 === undefined) {
            Main.common$.diags_USER1 = setting;
        }
        if (Main.common$.diags_USER2 === undefined) {
            Main.common$.diags_USER2 = setting;
        }
        if (Main.common$.diags_USER3 === undefined) {
            Main.common$.diags_USER3 = setting;
        }
        if (Main.common$.diags_USER4 === undefined) {
            Main.common$.diags_USER4 = setting;
        }
        if (Main.common$.diags_USER5 === undefined) {
            Main.common$.diags_USER5 = setting;
        }
        if (Main.common$.diags_USER6 === undefined) {
            Main.common$.diags_USER6 = setting;
        }

        /* If no logger supplied to this module, create one */
        if (LoggingSetup.mainLogger == null) {
            logger = createLogger(LoggingSetup.mainLoggerSize,
                                  "Main Logger", null);
        }
        else {
            logger = LoggingSetup.mainLogger;
        }

        /* Plug it*/
        setLogger(Main, logger);

        /* Plug Registry's logger also if not defined */
        var Registry = xdc.useModule('xdc.runtime.Registry');
        setLogger(Registry, logger);
    }

    /* Setup SYSBIOS modules loggers and diags mask */
    var createHwiLogger = false;
    var createSwiLogger = false;
    var createTaskLogger = false;

    /* Setup the SYSBIOS Hwi and Clock diags masks */
    if (LoggingSetup.sysbiosHwiLogging == true) {

        var setting = getDiagsSetting(LoggingSetup.sysbiosHwiLogging,
                                  LoggingSetup.sysbiosHwiLoggingRuntimeControl);

        var Hwi = xdc.useModule('ti.sysbios.hal.Hwi');
        var HwiDelegate = Hwi.HwiProxy.delegate$;

        if (HwiDelegate.common$.diags_USER1 === undefined) {
            HwiDelegate.common$.diags_USER1 = setting;
        }
        if (HwiDelegate.common$.diags_USER2 === undefined) {
            HwiDelegate.common$.diags_USER2 = setting;
        }
        if (Hwi.common$.diags_USER1 === undefined) {
            Hwi.common$.diags_USER1 = setting;
        }
        if (Hwi.common$.diags_USER2 === undefined) {
            Hwi.common$.diags_USER2 = setting;
        }

        Clock = xdc.useModule('ti.sysbios.knl.Clock');
        if (Clock.common$.diags_USER1 === undefined) {
            Clock.common$.diags_USER1 = setting;
        }
        if (Clock.common$.diags_USER2 === undefined) {
            Clock.common$.diags_USER2 = setting;
        }
        if (Clock.common$.diags_USER3 === undefined) {
            Clock.common$.diags_USER3 = setting;
        }

        /* If no logger supplied to this module, create one */
        if (LoggingSetup.sysbiosLogger == null) {
            createHwiLogger = true;
        }
        else {
            Hwi.common$.logger = LoggingSetup.sysbiosLogger;
            HwiDelegate.common$.logger = LoggingSetup.sysbiosLogger;
            Clock.common$.logger = LoggingSetup.sysbiosLogger;
        }
    }

    /* Setup SYSBIOS Swi diags mask */
    if (LoggingSetup.sysbiosSwiLogging == true) {

        var setting = getDiagsSetting(LoggingSetup.sysbiosSwiLogging,
                                  LoggingSetup.sysbiosSwiLoggingRuntimeControl);

        var Swi = xdc.useModule('ti.sysbios.knl.Swi');

        if (Swi.common$.diags_USER1 === undefined) {
            Swi.common$.diags_USER1 = setting;
        }
        if (Swi.common$.diags_USER2 === undefined) {
            Swi.common$.diags_USER2 = setting;
        }

        /* If no logger supplied to this module, create one */
        if (LoggingSetup.sysbiosLogger == null) {
            createSwiLogger = true;
        }
        else {
            Swi.common$.logger = LoggingSetup.sysbiosLogger;
        }
    }

    /* Setup SYSBIOS Task and related modules diags mask */
    if (LoggingSetup.sysbiosTaskLogging == true) {

        var setting = getDiagsSetting(LoggingSetup.sysbiosTaskLogging,
                                  LoggingSetup.sysbiosTaskLoggingRuntimeControl);

        Task = xdc.useModule('ti.sysbios.knl.Task');
        if (Task.common$.diags_USER1 === undefined) {
            Task.common$.diags_USER1 = setting;
        }
        if (Task.common$.diags_USER2 === undefined) {
            Task.common$.diags_USER2 = setting;
        }

        Semaphore = xdc.useModule('ti.sysbios.knl.Semaphore');
        if (Semaphore.common$.diags_USER1 === undefined) {
            Semaphore.common$.diags_USER1 = setting;
        }
        if (Semaphore.common$.diags_USER2 === undefined) {
            Semaphore.common$.diags_USER2 = setting;
        }

        Event = xdc.useModule('ti.sysbios.knl.Event');
        if (Event.common$.diags_USER1 === undefined) {
            Event.common$.diags_USER1 = setting;
        }
        if (Event.common$.diags_USER2 === undefined) {
            Event.common$.diags_USER2 = setting;
        }

        /* If no logger supplied to this module, create one */
        if (LoggingSetup.sysbiosLogger == null) {
            createTaskLogger = true;
        }
        else {
            Task.common$.logger = LoggingSetup.sysbiosLogger;
            Semaphore.common$.logger = LoggingSetup.sysbiosLogger;
            Event.common$.logger = LoggingSetup.sysbiosLogger;
        }
    }

    /* Setup SYSBIOS Task and related modules diags mask */
    if ((createHwiLogger == true) || (createSwiLogger == true) ||
        (createTaskLogger == true)) {

        /* Create the logger for all SYSBIOS modules */
        logger = createLogger(LoggingSetup.sysbiosLoggerSize,
                              "SYSBIOS System Logger",null);
    }

    if (createHwiLogger == true) {
        setLogger(Hwi, logger);
        setLogger(HwiDelegate, logger);
        setLogger(Clock, logger);
    }

    if (createSwiLogger == true) {
        setLogger(Swi, logger);
    }

    if (createTaskLogger == true) {
        setLogger(Task, logger);
        setLogger(Semaphore, logger);
        setLogger(Event, logger);
    }

    /* Make sure add Rta in when we need it */
    if ((LoggingSetup.eventUploadMode ==
         LoggingSetup.UploadMode_NONJTAGTRANSPORT) ||
       (LoggingSetup.eventUploadMode ==
        LoggingSetup.UploadMode_NONJTAG_AND_JTAGSTOPMODE)) {
        var Rta = xdc.useModule('ti.uia.services.Rta');
    }
}

/*
 * ======== createLogger =========
 * internal helper function that creates the type of logger
 * appropriate for the LoggingSetup.uploadMode that has been configured.
 *
 * param loggerSize: the size of the logger in MAUs
 * param loggerInstanceName: the name to assign to the logger instance
 * param loggerPriority: the IUIATransfer.Priority to assign to the logger instance
 * returns the logger instance that was created
 */
function createLogger(loggerSize,loggerInstanceName,loggerPriority){
    /* Create the logger instance */
    var IUIATransfer = xdc.module('ti.uia.runtime.IUIATransfer');
    switch(LoggingSetup.eventUploadMode){
    case LoggingSetup.UploadMode_SIMULATOR: /* note that simulators use probe points */
    case LoggingSetup.UploadMode_PROBEPOINT:
        if (isEnableDebugPrintf){
            print("LoggingSetup: LoggerProbePoint used for "+loggerInstanceName);
        }
        Logger = xdc.useModule('ti.uia.runtime.LoggerProbePoint');
        break;
    case LoggingSetup.UploadMode_JTAGSTOPMODE:
        if (isEnableDebugPrintf){
            print("LoggingSetup: LoggerStopMode used for "+loggerInstanceName);
        }
        Logger = xdc.useModule('ti.uia.runtime.LoggerStopMode');
        break;
    case LoggingSetup.UploadMode_NONJTAGTRANSPORT:
        if (isEnableDebugPrintf){
            print("LoggingSetup: LoggerCircBuf used for "+loggerInstanceName);
        }
        Logger = xdc.useModule('ti.uia.runtime.LoggerCircBuf');
        break;
    case LoggingSetup.UploadMode_JTAGRUNMODE:
    case LoggingSetup.UploadMode_NONJTAG_AND_JTAGSTOPMODE:
        if (isEnableDebugPrintf){
            print("LoggingSetup: LoggerCircBuf with OverflowLogger used for "+loggerInstanceName);
        }
        Logger = xdc.useModule('ti.uia.runtime.LoggerCircBuf');
        /*
         *  Since the overflow logger is a module-level config option for
         *  the LoggerCircBuf module, must only create it once.
         */
         /* 
          *  Set isOverflowLoggerAssigned to true to avoid the following bug:
          *  SDOCM00094008: Overflow logger not supported for JTAGRUNMODE and 
          *                 NONJTAG_AND_JTAGSTOPMODE
          */
        isOverflowLoggerAssigned = true;
        if (!isOverflowLoggerAssigned) {
            OverflowLogger = xdc.useModule('ti.uia.runtime.LoggerStopMode');
            var overflowLoggerParams = new OverflowLogger.Params();
            var isOverflowLoggerEnabled = true;
            if (LoggingSetup.overflowLoggerSize != null){
                if (LoggingSetup.overflowLoggerSize == 0) {
                  isOverflowLoggerEnabled = false;
                } else {
                  overflowLoggerParams.transferBufSize = LoggingSetup.overflowLoggerSize;
                }
            }
                        
            if (isOverflowLoggerEnabled) {
              var overflowLog = OverflowLogger.create(overflowLoggerParams);
              overflowLog.instance.name = "OverflowLogger";
              Logger.overflowLogger = overflowLog;
            }
            isOverflowLoggerAssigned = true;
        }
        break;
    case LoggingSetup.UploadMode_STREAMER:
        if (isEnableDebugPrintf){
            print("LoggingSetup: LoggerStreamer used for "+loggerInstanceName);
        }
        Logger = xdc.useModule('ti.uia.sysbios.LoggerStreamer');
        if (loggerStream == null) {
            loggerStream = Logger.create();
        }
        return loggerStream;
    case LoggingSetup.UploadMode_IDLE:
        if (isEnableDebugPrintf){
            print("LoggingSetup: LoggerIdle used for "+loggerInstanceName);
        }
        Logger = xdc.useModule('ti.uia.sysbios.LoggerIdle');
        if (loggerIdle == null) {
            loggerIdle = Logger.create();
        }
        return loggerIdle;
    }

    var loggerParams = new Logger.Params();
    if (loggerSize != null){
        loggerParams.transferBufSize = loggerSize;
    }
    if (loggerPriority != null){
        loggerParams.priority = IUIATransfer.Priority_SYNC;
    }
    logger = Logger.create(loggerParams);
    logger.instance.name = loggerInstanceName;
    return logger;
}

/*
 *  ======== setLogger ========
 *
 */
function setLogger(mod, logger)
{
    /* Warn if the user has already set the logger for this module. */
    if (mod.common$.logger != undefined) {
        mod.$logWarning(mod.$name + ".common$.logger has already " +
                        "been assigned, LoggingSetup reassigning logger to " +
                        logger.instance.name, mod);
    }

    mod.common$.logger = logger;
}

/*
 *  ======== getDiagsSetting ========
 */
function getDiagsSetting(enabled, runtimeCtrl)
{
    if (!enabled && !runtimeCtrl) {
        return (Diags.ALWAYS_OFF);
    }
    else if (!enabled && runtimeCtrl) {
        return (Diags.RUNTIME_OFF);
    }
    else if (enabled && !runtimeCtrl) {
        return (Diags.ALWAYS_ON);
    }
    else if (enabled && runtimeCtrl) {
        return (Diags.RUNTIME_ON);
    }
}

/*
 */
/*
 *  @(#) ti.uia.sysbios; 1, 0, 0, 0,1; 7-13-2012 11:12:39; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

