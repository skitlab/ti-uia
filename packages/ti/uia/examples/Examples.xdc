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
 *  ======== Examples.xdc ========
 */
import xdc.tools.product.IProductTemplate;

metaonly module Examples inherits IProductTemplate 
{
    config String name = "System Analyzer (UIA) Examples";

    config IProductTemplate.TemplateGroup root = {
        id          : "ti.uia.examples.root",
        name        : "System Analyzer (UIA)",
        description : "System Analyzer (UIA) Tutorials, Examples and Project Templates"
    };

    config IProductTemplate.TemplateGroup level1 = {
        id          : "ti.uia.examples.root.level1",
        name        : "Single-core Examples",
        description : "System Analyzer (UIA) Single-core Examples",
        groups      : ["ti.uia.examples.root"]
    };

    config IProductTemplate.TemplateGroup level2 = {
        id          : "ti.uia.examples.root.level2",
        name        : "Multi-core Projects",
        description : "System Analyzer (UIA) Multi-core Examples",
        groups      : ["ti.uia.examples.root"]
    };
    
    config IProductTemplate.TemplateGroup level3 = {
        id          : "ti.uia.examples.root.level3",
        name        : "Tutorials",
        description : "System Analyzer (UIA) Tutorials",
        groups      : ["ti.uia.examples.root"]
    };

    override config IProductTemplate.TemplateGroup templateGroupArr [] =
                                  [root, level1, level2, level3];

    config IProductTemplate.TemplateInfo c6472_message = {
        title: "evm6472: MessageQ (single image for all cores) with UIA",
        fileList: [
            { path: "./evm6472/message.c" },
            { path: "./evm6472/message.cfg" },
        ],
        description: "The message example shows how to use MessageQ on EVM6472 and UIA. It is a single-image example that must be loaded on all cores.\\n\\nA message is sent from core 0 to core 1 to core 2...back to core 0. The UIABenchmark_start and stop is used on core 0 to determine the duration of a round trip.\\n\\nThe Log data is obtained via Ethernet.",
        buildProfile: "release",
        platform: "ti.platforms.evm6472:core0",
        groups:["ti.uia.examples.root.level2"],
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC", "com.ti.rtsc.NDK" ],
        linkerCommandFile: ""
    };
        
    config IProductTemplate.TemplateInfo stairstep_JTAGStopMode = {
        title: "Stairstep JTAG StopMode",
        fileList: [
            { path: "./single/stairstep.c" },
            { path: "./single/stairstep_JTAGStopMode.cfg" },
        ],
        description: "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained when the target is halted.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.",
        buildProfile: "release",
        groups:["ti.uia.examples.root.level1"],
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
            { deviceFamily: "ARM",   toolChain: "TI" },
            { deviceFamily: "C2000", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC" ],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo logger = {
        title: "LoggerStreamer Example",
        fileList: [
            { path: "./single/logger.c" },
            { path: "./single/logger.cfg" },
        ],
        description: "Example showing the usage of LoggerStreamer and LogUC.h",
        buildProfile: "release",
        groups:["ti.uia.examples.root.level1"],
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
            { deviceFamily: "ARM",   toolChain: "TI" },
            { deviceFamily: "C2000", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC" ],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo stairstep_ProbePoint = {
        title: "Stairstep ProbePoint",
        fileList: [
            { path: "./single/stairstep.c" },
            { path: "./single/stairstep_ProbePoint.cfg" },
        ],
        description: "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained by temporarily stopping the target when the Log call is made.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.\\n\\nTo build this example, the XDC version must be 3.22 (or later) or the RTSC Build-Profile must be \"release\" or \"debug\" (not \"whole_program\").",
        buildProfile: "release",
        groups:["ti.uia.examples.root.level1"],
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
            { deviceFamily: "ARM",   toolChain: "TI" },
            { deviceFamily: "C2000", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC" ],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo stairstep_JTAGRunMode = {
        title: "Stairstep JTAG RunMode",
        fileList: [
            { path: "./single/stairstep.c" },
            { path: "./single/stairstep_JTAGRunMode.cfg" },
        ],
        description: "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained by reading the running target (only works on C64X+ and C66 CPUs).\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.",
        buildProfile: "release",
        groups:["ti.uia.examples.root.level1"],
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC" ],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo stairstep_Ethernet = {
        title: "Stairstep Ethernet",
        fileList: [
            { path: "./single/stairstep.c" },
            { path: "./single/stairstep_Ethernet.cfg" },
        ],
        description: "The stairstep example runs continuously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nLog data is obtained via Ethernet.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.\\n\\nThis example, as is, only works for the EVM6472 board. Refer to the bottom of the .cfg file on how to use on a different board.",
        buildProfile: "release",
        groups:["ti.uia.examples.root.level1"],
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
            { deviceFamily: "ARM",   toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC", "com.ti.rtsc.NDK" ],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo stairstep_Simulator = {
        title: "Stairstep Simulator",
        fileList: [
            { path: "./single/stairstep.c" },
            { path: "./single/stairstep_Simulator.cfg" },
        ],
        description: "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained by temporarily stopping the target when the Log call is made.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory\\n\\nTo build this example, the XDC version must be 3.22 (or later) or the RTSC Build-Profile must be \"release\" or \"debug\" (not \"whole_program\").",
        buildProfile: "release",
        groups:["ti.uia.examples.root.level1"],
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
            { deviceFamily: "ARM",   toolChain: "TI" },
            { deviceFamily: "C2000", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC" ],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo evmti816x_dspLoggerCircBuf = {
        title: "evmti816x: SimpleTask w/ LoggerCircBuf for the DSP",
        fileList: [
            { path: "./evmti816x/simpleTask.c" },
            { path: "./evmti816x/dspLoggerCircBuf.cfg" },
        ],
        description: "This DSP example uses LoggerCircBuf to log benchmark events. The events are routed through the ServiceMgr on Linux.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.",
        groups:["ti.uia.examples.root.level2"],
        buildProfile: "release",
        platform: "ti.uia.examples.platforms.evmTI816X.dsp",
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo evmti816x_videoM3LoggerCircBuf = {
        title: "evmti816x: SimpleTask w/ LoggerCircBuf for the video M3",
        fileList: [
            { path: "./evmti816x/simpleTask.c" },
            { path: "./evmti816x/videoM3LoggerCircBuf.cfg" },
        ],
        description: "This Video M3 example uses LoggerCircBuf to log benchmark events. The events are routed through the ServiceMgr on Linux.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.",
        groups:["ti.uia.examples.root.level2"],        
        buildProfile: "release",
        platform: "ti.uia.examples.platforms.evmTI816X.video",
        isHybrid: true,
        filterArr: [
            { deviceFamily: "ARM", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo evmti816x_vpssM3LoggerCircBuf = {
        title: "evmti816x: SimpleTask w/ LoggerCircBuf for the vpss M3",
        fileList: [
            { path: "./evmti816x/simpleTask.c" },
            { path: "./evmti816x/vpssM3LoggerCircBuf.cfg" },
        ],
        description: "This VPSS M3 example uses LoggerCircBuf to log benchmark events. The events are routed through the ServiceMgr on Linux.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.",
        groups:["ti.uia.examples.root.level2"],        
        buildProfile: "release",
        platform: "ti.uia.examples.platforms.evmTI816X.vpss",
        isHybrid: true,
        filterArr: [
            { deviceFamily: "ARM", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo evmti816x_dspLoggerSM = {
        title: "evmti816x: SimpleTask w/ LoggerSM for the DSP",
        fileList: [
            { path: "./evmti816x/simpleTask.c" },
            { path: "./evmti816x/dspLoggerSM.cfg" },
        ],
        description: "This DSP example uses LoggerSM to log benchmark events. The events can be displayed to the Linux console or written to a binary file.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.",
        groups:["ti.uia.examples.root.level2"],        
        buildProfile: "release",
        platform: "ti.uia.examples.platforms.evmTI816X.dsp",
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo evmti816x_videoM3LoggerSM = {
        title: "evmti816x: SimpleTask w/ LoggerSM for the video M3",
        fileList: [
            { path: "./evmti816x/simpleTask.c" },
            { path: "./evmti816x/videoM3LoggerSM.cfg" },
        ],
        description: "This Video M3 example uses LoggerSM to log benchmark events. The events can be displayed to the Linux console or written to a binary file.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.",
        groups:["ti.uia.examples.root.level2"],
        buildProfile: "release",
        platform: "ti.uia.examples.platforms.evmTI816X.video",
        isHybrid: true,
        filterArr: [
            { deviceFamily: "ARM", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo evmti816x_vpssM3LoggerSM = {
        title: "evmti816x: SimpleTask w/ LoggerSM for the vpss M3",
        fileList: [
            { path: "./evmti816x/simpleTask.c" },
            { path: "./evmti816x/vpssM3LoggerSM.cfg" },
        ],
        description: "This VPSS M3 example uses LoggerSM to log benchmark events. The events can be displayed to the Linux console or written to a binary file.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.",
        groups:["ti.uia.examples.root.level2"],
        buildProfile: "release",
        platform: "ti.uia.examples.platforms.evmTI816X.vpss",
        isHybrid: true,
        filterArr: [
            { deviceFamily: "ARM", toolChain: "TI" },
        ],
        requiredProducts: [ "com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"],
        linkerCommandFile: ""
    };
        
    config IProductTemplate.TemplateInfo tutorial1 = {
        title: "System Analyzer and UIA Tutorial 1: Logging events, benchmarking, controlling events.",
        fileList: [
            { path: "./tutorial1/main.c" },
            { path: "./tutorial1/tutorial1a.c" },
            { path: "./tutorial1/tutorial1b.c" },
            { path: "./tutorial1/tutorial1c.c" },
            { path: "./tutorial1/tutorial1d.c" },
            { path: "./tutorial1/systemAnalyzerTutorial1.gel" },
            { path: "./tutorial1/systemAnalyzerTutorial1.cfg" }
        ],
        description: "This tutorial shows how to log errors, warnings and info events, benchmark code and control which events are logged. Refer to http://processors.wiki.ti.com/index.php/McsaTutorial1 for more details.",        
        groups:["ti.uia.examples.root.level3"],        
        buildProfile: "release",
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
            { deviceFamily: "ARM",   toolChain: "TI" },
            { deviceFamily: "C2000", toolChain: "TI" },
        ],
        requiredProducts: [],
        linkerCommandFile: ""
    };
    
    config IProductTemplate.TemplateInfo tutorial2 = {
        title: "System Analyzer and UIA Tutorial 2: Graphing events, using JTAG Run-Mode (C64X+ or C66X emulation target)",
        fileList: [
            { path: "./tutorial2/main.c" },
            { path: "./tutorial2/systemAnalyzerTutorial2.gel" },
            { path: "./tutorial2/systemAnalyzerTutorial2.cfg" }
        ],
        description: "This tutorial shows how to log data that can be graphed and analyzed for min/max/average statistics.  Also demonstrates how to use LoggerCircBuf and JTAG Run-Mode to upload events while a target is running . Refer to http://processors.wiki.ti.com/index.php/McsaTutorial2 for more details.",        
        groups:["ti.uia.examples.root.level3"],        
        buildProfile: "release",
        isHybrid: true,
        filterArr: [
            { deviceFamily: "C6000", toolChain: "TI" },
        ],
        requiredProducts: [],
        linkerCommandFile: ""
    };

    override config IProductTemplate.TemplateInfo templateArr[] = [
        c6472_message,
        stairstep_JTAGStopMode,
        stairstep_Ethernet,
        stairstep_JTAGRunMode,
        stairstep_ProbePoint,
        logger,
        stairstep_Simulator,
        evmti816x_dspLoggerCircBuf,
        evmti816x_dspLoggerSM,
        evmti816x_videoM3LoggerCircBuf,
        evmti816x_vpssM3LoggerCircBuf,
        evmti816x_videoM3LoggerSM,
        evmti816x_vpssM3LoggerSM,
        tutorial1,
        tutorial2
    ];
}
/*
 *  @(#) ti.uia.examples; 1,0,0,1; 7-13-2012 11:16:17; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

