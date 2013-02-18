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
 * ======== UIAProfile.xdc ========
 */

import xdc.runtime.Diags;
import xdc.runtime.Types;
import ti.uia.events.DvtTypes;

/*!
 * UIA Profile Events
 *
 * The UIAProfile module defines events that allow
 * tooling to analyze the performance of the software
 * (processing time, latency, etc.)
 *  
 *  The generation of UIAProfile events is controlled by a module's diagnostics
 *  mask, which is described in detail in `{@link xdc.runtime.Diags}`.
 * `UIAProfile_enterFunction` events are generated only when the Diags.ENTRY bit  
 *  in the module's diagnostics mask is set, and 'UIAProfile_exitFunction' events 
 *  are generated only when the Diags.EXIT bit is set.
 * 
 *  The following configuration script demonstrates how the application might
 *  control the logging of events embedded in the `Mod` module at configuration
 *  time. In this case, the configuration script arranges for the `Log`
 *  statements within modules to always generate ENTRY and EXIT events.
 *  Without these configuration statements, no events would be generated
 *  by any modules.
 *
 * @a(Examples)
 * Example 1: This is part of the XDC configuration file for the application:
 *
 *  @p(code)
 *  var UIAProfile = xdc.useModule('ti.uia.events.UIAProfile');
 *  var Diags = xdc.useModule('xdc.runtime.Diags');
 *  var LoggerSys = xdc.useModule('xdc.runtime.LoggerSys');
 *  var Defaults = xdc.useModule('xdc.runtime.Defaults');
 *  var logger = LoggerSys.create();
 *  
 *  Defaults.common$.diags_ENTRY = Diags.ALWAYS_ON; 
 *  Defaults.common$.diags_EXIT = Diags.ALWAYS_ON;
 *  Defaults.common$.logger = logger;
 *  @p
 *
 *  @p(html)
 *  <hr />
 *  @p
 *
 *  Example 2: The following example configures a module to support logging
 *  of ENTRY and EXIT events, but defers the actual activation and deactivation of the
 *  logging until runtime. See the `{@link Diags#setMask Diags_setMask()}`
 *  function for details on specifying the control string.
 *
 *  This is a part of the XDC configuration file for the application:
 *
 *  @p(code)
 *  var UIAProfile = xdc.useModule('ti.uia.events.UIAProfile');
 *  var Diags = xdc.useModule('xdc.runtime.Diags');
 *  var Mod = xdc.useModule('my.pkg.Mod');
 *
 *  Mod.common$.diags_ENTRY = Diags.RUNTIME_OFF;
 *  Mod.common$.diags_EXIT = Diags.RUNTIME_OFF;
 *  @p
 *
 *  This is a part of the C code for the application.
 *  The diags_ENTRY mask is set by "E", and the diags_EXIT mask is set by "X".
 *
 *  @p(code)
 *  // turn on logging of ENTRY and EXIT events in the module
 *  Diags_setMask("my.pkg.Mod+EX");
 *
 *  // turn off logging of ENTRY and EXIT events in the module
 *  Diags_setMask("my.pkg.Mod-EX");
 *  @p
 *
 *  
 */
module UIAProfile inherits IUIAEvent {

    /*!
     *  ======== enterFunction ========
     *  Profiling event used to log the entry point of a function
     *
     * @a(Example)
     * To add entry and exit hook functions to every function 
     * 1. Use the following compiler options when compiling the source
     *  @p(code)
     *  --entry_hook=functionEntryHook
     *  --entry_param=address
     *  --exit_hook=functionExitHook
     *  --exit_param=address
     *  @p
     * 2. Add the following c code to implement the hook functions:
     *   The first parameter (the taskHandle) is set to  0 in this example.  
     *   @see exitFunction for an example of how to log the current task ID
     *   for task-aware function profiling.
     *  
     *  @p(code)
     *  #include <xdc/runtime/Log.h>
     *  #include <ti/uia/events/UIAProfile.h>
     *  ...
     * void functionEntryHook( void (*addr)() ){
     *    Log_write2(UIAProfile_enterFunction, 0,(IArg)addr);
     *   ...
     * void functionExitHook( void (*addr)() ){
     *    Log_write2(UIAProfile_exitFunction, 0,(IArg)addr);
     * }
     *  @p
     *  The following text will be displayed for the event:
     *  @p(code)
     *  enterFunction: taskHandle=0x0, adrs=0x820060
     *  exitFunction: taskHandle0x0, adrs=0x820060
     *  @p     
     *  @param(taskHandle)          task handle that identifies the currently active task (use 0 if not required)
     *  @param(functionAdrs)        the address of a function that can differentiate this pair of start and stop events from others
     */
    config xdc.runtime.Log.Event enterFunction = {
        mask: Diags.ENTRY,
        msg: "enterFunction: taskHandle=0x%x, adrs=0x%x"    
    };

    /*!
     *  ======== metaEventEnterFunction ========
     *  Metadata description of the enterFunction event
     *
     *  @_nodoc
     */
    metaonly config DvtTypes.MetaEventDescriptor metaEventEnterFunction = {
        versionId: "2.0",
        analysisType: DvtTypes.DvtAnalysisType_START,
        displayText: "enterFunction",
        tooltipText: "function entry",
        numParameters: 2,
        paramInfo: [
        {   name: 'Qualifier',
            dataDesc: DvtTypes.DvtDataDesc_INSTANCE,
            dataTypeName: 'Int',
            units: 'none',
            isHidden: false
        },
        {   name: 'FunctionAdrs',
            dataDesc: DvtTypes.DvtDataDesc_FUNCTIONADRS,
            dataTypeName: 'Int',
            units: 'none',
            isHidden: false
        }
        ]
    };


    /*!
     *  ======== exitFunction ========
     *  Profiling event used to log the exit point of a function
     *
     * @a(Example)
     * To add entry and exit hook functions to every function 
     * 1. Use the following compiler options when compiling the source
     *  @p(code)
     *  --entry_hook=functionEntryHook
     *  --entry_param=address
     *  --exit_hook=functionExitHook
     *  --exit_param=address
     *  @p
     * 2. Add the following c code to implement the hook functions:
     *   Task_selfMacro() is used to get the current task handle in this example.  
     *   @see enterFunction for an example of how to save CPU by logging 0 
     *   instead of the task handle if task-aware profiling is not required.
     *  
     *  @p(code)
     *  #include <xdc/runtime/Log.h>
     *  #include <ti/uia/events/UIAProfile.h>
     *  #include <ti/sysbios/knl/Task.h>
     *  ...
     * void functionEntryHook( void (*addr)() ){
     *    Log_write2(UIAProfile_enterFunction, (IArg)Task_selfMacro(),(IArg)addr);
     *   ...
     * void functionExitHook( void (*addr)() ){
     *    Log_write2(UIAProfile_exitFunction, (IArg)Task_selfMacro(),(IArg)addr);
     * }
     *  @p
     *  The following text will be displayed for the event:
     *  @p(code)
     *  enterFunction: taskHandle=0x0, adrs=0x820060
     *  exitFunction: taskHandle=0x0, adrs=0x820060
     *  @p     
     *  @param(taskHandle)          task handle that identifies the currently active task (use 0 if not required)
     *  @param(functionAdrs)        the address of a function that can differentiate this pair of start and stop events from others
     */
    config xdc.runtime.Log.Event exitFunction = {
        mask: Diags.EXIT,
        msg: "exitFunction: taskHandle=0x%x, adrs=0x%x"
    };

    /*!
     *  ======== metaEventExitFunction ========
     *  Metadata description of the exitFunction event
     *
     *  @_nodoc
     */
    metaonly config DvtTypes.MetaEventDescriptor metaEventExitFunction = {
        versionId: "2.0",
        analysisType: DvtTypes.DvtAnalysisType_STOP,
        displayText: "exitFunction",
        tooltipText: "Marks the end of analysis for a module instance",
        numParameters: 2,
        paramInfo: [
        {   name: 'Qualifier',
            dataDesc: DvtTypes.DvtDataDesc_INSTANCE,
            dataTypeName: 'Int',
            units: 'none',
            isHidden: false
        },
        {   name: 'FunctionAdrs',
            dataDesc: DvtTypes.DvtDataDesc_FUNCTIONADRS,
            dataTypeName: 'Int',
            units: 'none',
            isHidden: false
        }
        ]
    };
    
    
}

/*
 */
/*
 *  @(#) ti.uia.events; 1, 0, 0, 2,1; 7-13-2012 11:12:09; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

