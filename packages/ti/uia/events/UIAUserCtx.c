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
 *  ======== UIAUserCtx.c ========
 */

#include <xdc/std.h>
#include "package/internal/UIAUserCtx.xdc.h"

/*
 * User-defined Context Instrumentation
 */

volatile UInt ti_uia_events_UIAUserCtx_gLastValue = 0;
volatile UInt ti_uia_events_UIAUserCtx_gEnableOnValue = 0;

/*
 * ======== isLoggingEnabled ========
 * returns true if the new context matches the value to enable logging with.
 */
Bool UIAUserCtx_isLoggingEnabled(UInt newUserCtx){
    return (newUserCtx == ti_uia_events_UIAUserCtx_gEnableOnValue);
}

/*
 * ======== setOldValue =========
 * sets ti_uia_events_UIAUserCtx_gLastValue to the new value and returns the old value before it was updated.
 */
UInt UIAUserCtx_setOldValue(UInt newValue) {
    UInt retValue = ti_uia_events_UIAUserCtx_gLastValue;
    if (ti_uia_events_UIAUserCtx_gLastValue != newValue)
        ti_uia_events_UIAUserCtx_gLastValue = newValue;
    return(retValue);
}

/*
 */
/*
 *  @(#) ti.uia.events; 1, 0, 0, 2,1; 7-13-2012 11:12:10; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */
