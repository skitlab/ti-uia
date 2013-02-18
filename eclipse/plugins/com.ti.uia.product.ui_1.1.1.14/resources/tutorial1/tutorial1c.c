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
 * ======== System Analyzer Tutorial 1C : Using the Diags module ========
 * This tutorial demonstrates the use of the Diags module
 * to control which events are logged.
 *
 * See http://processors.wiki.ti.com/index.php/McsaTutorial1 for more info.
 */

#include <xdc/std.h>

#include <xdc/runtime/Log.h>

/* We need to use events defined in the xdc.runtime.Diags module.
 * The .h file for this module is referenced as follows: */
#include <xdc/runtime/Diags.h>

void tutorial_1C();

void tutorial_1C(){
        Log_print0(Diags_USER1,"Diags_USER1 is configured as ALWAYS_OFF, so this event will not be logged");
        Log_print0(Diags_USER2,"Diags_USER2 is configured as RUNTIME_OFF, so this event will not be logged");
        Log_print0(Diags_USER3,"Diags_USER3 is configured as RUNTIME_ON, so this event will be logged");

        /* The following code shows how to enable logging of events that
         * belong to the Diags_USER2 category.  See the CDoc
         * for the xdc.runtime.Diags module for more information.*/
        Diags_setMask("xdc.runtime.Main+2");
        Log_print0(Diags_USER2,"Diags_USER2 has now been reconfigured as RUNTIME_ON, so this event will be logged");
        /* The following code shows how to disable logging of events that
         * belong to the Diags_USER2 category.  This restores the state of
         * the masks to the way they were at the entry of tutorial_1C().
         */
        Diags_setMask("xdc.runtime.Main-2");
        return;
}
/*
 *  @(#) ti.uia.examples.tutorial1; 1, 0, 0, 0,1; 7-13-2012 11:16:57; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

