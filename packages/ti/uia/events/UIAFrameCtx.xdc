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
 * ======== UIAFrameCtx.xdc
 */
import xdc.runtime.Types;
import xdc.runtime.Diags;
import ti.uia.events.IUIACtx;

/*!
 * UIA Frame Context Instrumentation
 *
 * The UIAFrameCtx module defines context change events
 * and methods that allow tooling to identify frame context
 * switches and to enable frame-aware filtering, trace and
 * analysis.
 *
 * It inherits IUIACtx, which defines a function pointer to
 * an isLoggingEnabled function which, if configured to point to
 * a function, will evaluate the function prior to logging the context
 * change event and will determine whether to log the event based on the
 * return value of the function.  If the function is not configured,
 * logging will be conditional upon ti_uia_runtime_CtxFilter_gIsLoggingEnabled.
 *
 * The generation of UIAFrameCtx events is also controlled by a module's diagnostics
 * mask, which is described in details in `{@link xdc.runtime.Diags}`.
 * UIAFrameCtx` events are generated only when the Diags.ANALYSIS bit is set 
 * in the module's diagnostics mask. 
 *
 * The following configuration script demonstrates how the application might
 * control the logging of ANALYSIS events embedded in the `Mod` module at configuration
 * time. In this case, the configuration script arranges for the `Log`
 * statements within modules to always generate ANALYSIS events.
 * Without these configuration statements, no ANALYSIS events would be generated
 * by any modules.
 *
 * @a(Examples)
 * Example 1: This is part of the XDC configuration file for the application:
 *
 *  @p(code)
 *  var LogCtxChg = xdc.useModule('ti.uia.runtime.LogCtxChg');
 *  var Diags = xdc.useModule('xdc.runtime.Diags');
 *  var LoggerSys = xdc.useModule('xdc.runtime.LoggerSys');
 *  var Defaults = xdc.useModule('xdc.runtime.Defaults');
 *  var logger = LoggerSys.create();
 *  
 *  Defaults.common$.diags_ANALYSIS = Diags.ALWAYS_ON; 
 *  Defaults.common$.logger = logger;
 *  @p
 *
 *  @p(html)
 *  <hr />
 *  @p
 *
 * Example 2: The following example configures a module to support logging
 * of ANALYSIS events, but defers the actual activation and deactivation of the
 * logging until runtime. See the `{@link Diags#setMask Diags_setMask()}`
 * function for details on specifying the control string.
 *
 * This is a part of the XDC configuration file for the application:
 *
 *  @p(code)
 *  var LogCtxChg = xdc.useModule('ti.uia.runtime.LogCtxChg');
 *  var Diags = xdc.useModule('xdc.runtime.Diags');
 *  var Mod = xdc.useModule('my.pkg.Mod');
 *
 *  Mod.common$.diags_ANALYSIS = Diags.RUNTIME_OFF;
 *  @p
 *
 *  This is a part of the C code for the application:
 *
 *  @p(code)
 *  // turn on logging of ANALYSIS events in the module
 *  Diags_setMask("my.pkg.Mod+Z");
 *
 *  // turn off logging of ANALYSIS events in the module
 *  Diags_setMask("my.pkg.Mod-Z");
 *  @p
 */

@CustomHeader
module UIAFrameCtx inherits IUIACtx {

    /*!
     *  ======== ctxChg ========
     *  Frame Context Change event
     *
     *  Used to log the start of a new frame
     *  If ti_uia_events_UIAFrameCtx_isLoggingEnabledFxn is not NULL
     *  it is called and its return value determines whether logging is enabled or not.
     *
     *  @a(Example)
     *   The following C code shows how to log a Context Change 
     *   event that identifies a new Frame ID
     *  
     *  @p(code)
     *  #include <ti/uia/runtime/LogCtxChg.h>
     *  ...
     *  Void processFrame(Int frameId){
     *    ...
     *    LogCtxChg_frame("New Frame ID=0x%x",frameId);
     *    ...
     *  }
     *  @p
     *  This event prints the Log call site (%$F) and a format string (%$S)
     *  which is recursively formatted with any addition arguments.
     *  The following text is an example of what will be displayed for the event:
     *  @p(code)     
     *  "Frame Ctx Change at Line 123 in demo.c [Prev. Frame ID=0x1234] New Frame ID=0x1235"
     *
     *  @param(fmt)   a constant string that describes the context change and provides a format specifier for newFrameId
     *  @param(newFrameId)   an integer which uniquely identifies the new context
     */
    config xdc.runtime.Log.Event ctxChg = {
        mask: Diags.ANALYSIS,
        msg: "Frame Ctx Change at %$F [prev. Frame ID=0x%x] %$S"};

    /*!
     *  ======== metaEventFrameCtxChg ========
     *  Metadata description of the Frame Context Change event
     *
     *  @_nodoc
     */
    metaonly config DvtTypes.MetaEventDescriptor metaEventFrameCtxChg = {
        versionId: "2.0",
        analysisType: DvtTypes.DvtAnalysisType_CONTEXTCHANGE,
        displayText: "Frame Ctx Change",
        tooltipText: "Frame ID Context Change",
        numParameters: 5,
        paramInfo: [
        {   name: '__FILE__',
            dataDesc: DvtTypes.DvtDataDesc_FILENAMESTR,
            dataTypeName: 'String',
            units: 'none',
            isHidden: false
        },
        {   name: '__LINE__',
            dataDesc: DvtTypes.DvtDataDesc_LINENUM,
            dataTypeName: 'Int',
            units: 'none',
            isHidden: false
        },
        {   name: 'Prev. Frame ID',
            dataDesc: DvtTypes.DvtDataDesc_FRAMEID,
            dataTypeName: 'Int',
            units: 'none',
            isHidden: false
        },
        {   name: 'fmt',
            dataDesc: DvtTypes.DvtDataDesc_FMTSTR,
            dataTypeName: 'String',
            units: 'none',
            isHidden: false
        },
        {   name: 'New Frame ID',
            dataDesc: DvtTypes.DvtDataDesc_FRAMEID,
            dataTypeName: 'Int',
            units: 'none',
            isHidden: false
        }]

    };
    /*!
     * ======== getCtxId ========
     * Get the ID for the current frame
     *
     *  @a(returns)
     *  returns the frame ID logged by the last call to UIAFrameCtx_logCtxChg.
     */
    @Macro UInt getCtxId();

    /*!
     * ======== isLoggingEnabled ========
     * returns true if the new context matches the value to enable logging with.
     *
     *  Default implementation of the IUIACtx_IsLoggingEnabledFxn for user context.
     *  To enable context-aware filtering, assign UIAFrameCtx_isLoggingEnabledFxn = &UIAFrameCtx_isLoggingEnabled
     *  in the config script or programmatically, or assign your own implementation of this
     *  function.
     *  @param(newFrameId) the new frame ID
     *  @a(returns) true if logging is enabled
     */
     @DirectCall
     Bool isLoggingEnabled(UInt newFrameId);

    /*!
     * ======== setOldValue =========
     * sets the ti_uia_events_UIAFrameCtx_gLastValue to the new value and returns the old value before it was updated.
     *
     * @param(newValue) the new value to save in the global variable
     * @a(return0       the original value of the global variable before it was updated.
     */
     @DirectCall
     UInt setOldValue(UInt newValue);
}

/*
 */
/*
 *  @(#) ti.uia.events; 1, 0, 0, 2,1; 7-13-2012 11:12:09; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

