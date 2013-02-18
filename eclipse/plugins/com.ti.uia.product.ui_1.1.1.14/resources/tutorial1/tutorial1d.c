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
 * ======== System Analyzer Tutorial 1D : Logging Dynamically Allocated Strings ========
 * This tutorial demonstrates the use of the LogSnapshot module to
 * upload the contents of dynamically allocated strings, so that references
 * to that string that are made in subsequent events will be able to be displayed
 * as text in System Analyzer.  It also demonstrates the steps needed to configure
 * a UIA module for use with an application.
 *
 * See http://processors.wiki.ti.com/index.php/SystemAnalyzerTutorial1D for more info.
 */

/* We need to use the XDC standard types defined.
 * The .h file for this module is referenced as follows: */
#include <xdc/std.h>

/* Including the following .h file would seem to be sufficient to allow the C
 * code to use the events defined in the LogSnapshot module.
 * If you try to compile this file, however, it will fail unless the LogSnapshot module
 * has been configured for use in the project's .cfg file!
 */
#include <ti/uia/runtime/LogSnapshot.h>
/* We also need to use APIs defined in the xdc.runtime.Log module,
 * and the Diags_USER1 mask definition.
 * The .h files for these module are referenced below: */
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>
#include <stdio.h>   /* for sprintf */
#include <string.h>  /* for strlen */

void tutorial_1D();

void tutorial_1D(){
    char szMyString[256];
        /* initialize the szMyString contents */
    sprintf(szMyString,"%s","A dynamically allocated string.\n");
    
        /* The first time we try to log an event that references szMyString,
         * System Analyzer will not be able to determine what text to display,
         * since what we are actually logging is the address of the string, not
         * the array of characters that starts at that address.
         * Note that Diags_USER6 is configured as Diags.RUNTIME_ON in the .cfg file
         * enabling the event to be logged. */
    Log_print1(Diags_USER6,"szMyString=%s.",(IArg)szMyString);

    /* The following LogSnapshot_writeString API call logs an event that
     * includes a snapshot of the memory contents of the string 'szMyString'
     * so that System Analyzer will be able to determine what text is associated
     * with the string's address */
    LogSnapshot_writeString(0,"szMyString",szMyString, strlen(szMyString));

        /* Now that the string memory contents have been uploaded,
         * subsequent events that reference the string will be properly
         * rendered. */
    Log_print1(Diags_USER6,"szMyString=%s.",(IArg)szMyString);
}


/*
 *  @(#) ti.uia.examples.tutorial1; 1, 0, 0, 0,1; 7-13-2012 11:16:57; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

