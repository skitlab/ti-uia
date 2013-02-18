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

#ifndef LOGUC_H_
#define LOGUC_H_

#include <xdc/runtime/Log.h>
/*
 * This file extends the Log API macros that are defined in
 * xdc.runtime.Log_epilogue.h with versions of the event logging
 * APIs that do not test for the condition:
 * ((Module__LOGDEF && xdc_runtime_Diags_query(evt)).
 *
 * This removes the CPU overhead associated with
 * checking the Diags masks associated with the current module,
 * at the cost of no longer be able to control which events are
 * logged via the Diags masks associated with the module.
 */

/*
 *  ======== xdc_runtime_Log_writeUC* ========
 */

#warn LogUC.h is a preliminary set of optimized Log APIs. The API names might change slightly and/or be moved to Log.h or another location in the future. Please make sure to configure a logger if you are using the LogUC API's.


#define Log_writeUC0(evt) \
    (xdc_runtime_Log_doPut0((evt), Module__MID))

#define Log_writeUC1(evt, a1) \
        (xdc_runtime_Log_doPut1((evt), Module__MID, (a1)))

#define Log_writeUC2(evt, a1, a2) \
        (xdc_runtime_Log_doPut2((evt), Module__MID, (a1), (a2)))

#define Log_writeUC3(evt, a1, a2, a3) \
        (xdc_runtime_Log_doPut4((evt), Module__MID, (a1), (a2), (a3), 0))

#define Log_writeUC4(evt, a1, a2, a3, a4) \
        (xdc_runtime_Log_doPut4((evt), Module__MID, (a1), (a2), (a3), (a4)))

#define Log_writeUC5(evt, a1, a2, a3, a4, a5) \
        (xdc_runtime_Log_doPut8((evt), Module__MID, \
            (a1), (a2), (a3), (a4), (a5), 0, 0, 0))

#define Log_writeUC6(evt, a1, a2, a3, a4, a5, a6) \
        (xdc_runtime_Log_doPut8((evt), Module__MID, \
            (a1), (a2), (a3), (a4), (a5), (a6), 0, 0))

#define Log_writeUC7(evt, a1, a2, a3, a4, a5, a6, a7) \
        (xdc_runtime_Log_doPut8((evt), Module__MID, \
            (a1), (a2), (a3), (a4), (a5), (a6), (a7), 0))

#define Log_writeUC8(evt, a1, a2, a3, a4, a5, a6, a7, a8) \
        (xdc_runtime_Log_doPut8((evt), Module__MID, \
            (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8)))

/*
 *  ======== xdc_runtime_Log_printUC* ========
 */
#define Log_printUC0(mask, fmt) \
    (xdc_runtime_Log_doPut1(mask, Module__MID, (IArg) fmt))

#define Log_printUC1(mask, fmt, a1) \
    (xdc_runtime_Log_doPut2(mask, Module__MID, (IArg) fmt, (a1)))

#define Log_printUC2(mask, fmt, a1, a2) \
    (xdc_runtime_Log_doPut4(mask, Module__MID, (IArg) fmt,(a1), (a2), 0))

#define Log_printUC3(mask, fmt, a1, a2, a3) \
    (xdc_runtime_Log_doPut4(mask, Module__MID, (IArg) fmt,(a1), (a2), (a3)))

#define Log_printUC4(mask, fmt, a1, a2, a3, a4) \
    (xdc_runtime_Log_doPut8(mask, Module__MID, \
            (IArg)fmt, (a1), (a2), (a3), (a4), 0, 0, 0))

#define Log_printUC5(mask, fmt, a1, a2, a3, a4, a5) \
    (xdc_runtime_Log_doPut8(mask, Module__MID, \
            (IArg)fmt, (a1), (a2), (a3), (a4), (a5), 0, 0))

#define Log_printUC6(mask, fmt, a1, a2, a3, a4, a5, a6) \
    (xdc_runtime_Log_doPut8(mask, Module__MID, \
            (IArg)fmt, (a1), (a2), (a3), (a4), (a5), (a6), 0))

/*
 *  ======== xdc_runtime_Log_errorUC* ========
 */
#define Log_errorUC0(fmt) \
    (xdc_runtime_Log_doPut4((Log_L_error), Module__MID, \
            (IArg) xdc_FILE__, (IArg)__LINE__, (IArg)fmt, 0))

#define Log_errorUC1(fmt, a1) \
    (xdc_runtime_Log_doPut4((Log_L_error), Module__MID, \
            (IArg) xdc_FILE__, (IArg)__LINE__, (IArg)fmt, (a1)))

#define Log_errorUC2(fmt, a1, a2) \
    (xdc_runtime_Log_doPut8((Log_L_error), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), 0, 0, 0))

#define Log_errorUC3(fmt, a1, a2, a3) \
    (xdc_runtime_Log_doPut8((Log_L_error), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), 0, 0))

#define Log_errorUC4(fmt, a1, a2, a3, a4) \
    (xdc_runtime_Log_doPut8((Log_L_error), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), (a4), 0))

#define Log_errorUC5(fmt, a1, a2, a3, a4, a5) \
    (xdc_runtime_Log_doPut8((Log_L_error), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), \
             (a4), (a5)))

/*
 *  ======== xdc_runtime_Log_warningUC* ========
 */
#define Log_warningUC0(fmt) \
    (xdc_runtime_Log_doPut4((Log_L_warning), Module__MID, \
            (IArg) xdc_FILE__, (IArg)__LINE__, (IArg)fmt, 0))

#define Log_warningUC1(fmt, a1) \
    (xdc_runtime_Log_doPut4((Log_L_warning), Module__MID, \
            (IArg) xdc_FILE__, (IArg)__LINE__, (IArg)fmt, (a1)))

#define Log_warningUC2(fmt, a1, a2) \
    (xdc_runtime_Log_doPut8((Log_L_warning), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), 0, 0, 0))

#define Log_warningUC3(fmt, a1, a2, a3) \
    (xdc_runtime_Log_doPut8((Log_L_warning), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), 0, 0))

#define Log_warningUC4(fmt, a1, a2, a3, a4) \
    (xdc_runtime_Log_doPut8((Log_L_warning), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), (a4), 0))

#define Log_warningUC5(fmt, a1, a2, a3, a4, a5) \
    (xdc_runtime_Log_doPut8((Log_L_warning), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), \
             (a4), (a5)))

/*
 *  ======== xdc_runtime_Log_info* ========
 */
#define Log_infoUC0(fmt) \
    (xdc_runtime_Log_doPut4((Log_L_info), Module__MID, \
            (IArg) xdc_FILE__, (IArg)__LINE__, (IArg)fmt, 0))

#define Log_infoUC1(fmt, a1) \
    (xdc_runtime_Log_doPut4((Log_L_info), Module__MID, \
            (IArg) xdc_FILE__, (IArg)__LINE__, (IArg)fmt, (a1)))

#define Log_infoUC2(fmt, a1, a2) \
    (xdc_runtime_Log_doPut8((Log_L_info), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), 0, 0, 0))

#define Log_infoUC3(fmt, a1, a2, a3) \
    (xdc_runtime_Log_doPut8((Log_L_info), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), 0, 0))

#define Log_infoUC4(fmt, a1, a2, a3, a4) \
    (xdc_runtime_Log_doPut8((Log_L_info), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), (a4), 0))

#define Log_infoUC5(fmt, a1, a2, a3, a4, a5) \
    (xdc_runtime_Log_doPut8((Log_L_info), Module__MID, (IArg) xdc_FILE__, \
             (IArg)__LINE__, (IArg)fmt, (a1), (a2), (a3), \
             (a4), (a5)))


#endif /* LOGUC_H_ */
/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:25; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

