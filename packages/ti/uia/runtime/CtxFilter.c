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
 *  ======== CtxFilter.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Types.h>
#include <ti/uia/events/UIAChanCtx.h>
#include <ti/uia/events/UIAFrameCtx.h>
#include <ti/uia/events/UIAThreadCtx.h>
#include <ti/uia/events/UIAUserCtx.h>

#include "package/internal/CtxFilter.xdc.h"

/*
 * Define global variables needed to enable / disable event logging
 * using IDE tooling
 */
volatile Bits16 ti_uia_runtime_CtxFilter_gFlags = 0;
volatile Bits16 ti_uia_runtime_CtxFilter_gEnableMask = CtxFilter_ALWAYS_ENABLED;
volatile Bool ti_uia_runtime_CtxFilter_gIsLoggingEnabled = TRUE;

/*
 * ====== setCtxFilterFlags ======
 * sets the context filter flags global variable 
 */
Void CtxFilter_setCtxFilterFlags(Bits16 flags) {
    ti_uia_runtime_CtxFilter_gFlags = flags;
}


/*
 * ======== isLoggingEnabledForChanCtx ========
 * optional function to enable context-aware filtering based on channel context
 */
Bool CtxFilter_isLoggingEnabledForChanCtx(Int newChanId){
    Bool result = FALSE;
    if (newChanId == ti_uia_events_UIAChanCtx_gEnableOnValue)
       ti_uia_runtime_CtxFilter_gFlags  |= ti_uia_events_UIAChanCtx_ENABLEMASK;
    else
       ti_uia_runtime_CtxFilter_gFlags  &= ~(ti_uia_events_UIAChanCtx_ENABLEMASK);

    if ((ti_uia_runtime_CtxFilter_gEnableMask == CtxFilter_ALWAYS_ENABLED) ||
        (ti_uia_runtime_CtxFilter_gFlags == ti_uia_runtime_CtxFilter_gEnableMask)) {
            result = TRUE;
    }
    return(result);
}

/*
 * ======== isLoggingEnabledForFrameCtx ========
 * optional function to enable context-aware filtering based on frame context
 */
Bool CtxFilter_isLoggingEnabledForFrameCtx(Int newFrameId){
    Bool result = FALSE;
    if (newFrameId == ti_uia_events_UIAFrameCtx_gEnableOnValue)
       ti_uia_runtime_CtxFilter_gFlags  |= ti_uia_events_UIAFrameCtx_ENABLEMASK;
    else
       ti_uia_runtime_CtxFilter_gFlags  &= ~(ti_uia_events_UIAFrameCtx_ENABLEMASK);

    if ((ti_uia_runtime_CtxFilter_gEnableMask == CtxFilter_ALWAYS_ENABLED) ||
        (ti_uia_runtime_CtxFilter_gFlags == ti_uia_runtime_CtxFilter_gEnableMask)) {
            result = TRUE;
    }
    return(result);
}

/*
 * ======== isLoggingEnabledForThreadCtx ========
 * optional function to enable context-aware filtering based on user context
 */
Bool CtxFilter_isLoggingEnabledForThreadCtx(Int newThreadId){
    Bool result = FALSE;
    if (newThreadId == ti_uia_events_UIAThreadCtx_gEnableOnValue)
       ti_uia_runtime_CtxFilter_gFlags  |= ti_uia_events_UIAThreadCtx_ENABLEMASK;
    else
       ti_uia_runtime_CtxFilter_gFlags  &= ~(ti_uia_events_UIAThreadCtx_ENABLEMASK);

    if ((ti_uia_runtime_CtxFilter_gEnableMask == CtxFilter_ALWAYS_ENABLED) ||
        (ti_uia_runtime_CtxFilter_gFlags == ti_uia_runtime_CtxFilter_gEnableMask)) {
            result = TRUE;
    }
    return(result);
}

/*
 * ======== isLoggingEnabledForUserCtx ========
 * optional function to enable context-aware filtering based on user context
 */
Bool CtxFilter_isLoggingEnabledForUserCtx(Int newUserCtx){
    Bool result = FALSE;
    if (newUserCtx == ti_uia_events_UIAUserCtx_gEnableOnValue)
       ti_uia_runtime_CtxFilter_gFlags  |= ti_uia_events_UIAUserCtx_ENABLEMASK;
    else
       ti_uia_runtime_CtxFilter_gFlags  &= ~(ti_uia_events_UIAUserCtx_ENABLEMASK);

    if ((ti_uia_runtime_CtxFilter_gEnableMask == CtxFilter_ALWAYS_ENABLED) ||
        (ti_uia_runtime_CtxFilter_gFlags == ti_uia_runtime_CtxFilter_gEnableMask)) {
            result = TRUE;
    }
    return(result);
}

/*
 */
/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:23; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

