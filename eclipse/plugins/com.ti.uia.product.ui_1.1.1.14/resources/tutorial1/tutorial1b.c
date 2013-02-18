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
 * ======== System Analyzer Tutorial 1B : Performance Analysis ========
 * This tutorial demonstrates the use of the UIABenchmark events
 * to measure the time it takes various APIs to execute, and how
 * to display the resulting statistics that are logged using the 
 * System Analyzer Duration Analysis view.
 *
 * See http://processors.wiki.ti.com/index.php/McsaTutorial1 for more info.
 */
#include <xdc/std.h>
#include <xdc/runtime/Log.h>

/* We need to use events defined in the ti.uia.events.UIABenchmark module.
 * The .h file for this module is referenced as follows: */
#include <ti/uia/events/UIABenchmark.h>

/* The following .h files are not required by the UIA code - they are
 * included to allow the use of the printf and sprintf APIs */
#include <stdio.h>
#include <string.h>

void tutorial_1B();

void tutorial_1B(){
        char myStr[32];
        /* The following code demonstrates the use of UIABenchmark events to measure the 
         * overhead associated with logging an event in various ways:
         * 1: loggin an event to the console.  (Note: this uses breakpoints to upload the 
         *    string to CCS, and so is not well suited for use in real-time applications
         */
        Log_write3(UIABenchmark_startInstanceWithStr, (IArg)"Benchmark printf",1,(IArg)"printf");
        printf("Output this event to console\n");
        Log_write3(UIABenchmark_stopInstanceWithStr,(IArg)"Benchmark printf",1,(IArg)"printf");

        /* 2: logging an event to a string in memory */
        Log_write3(UIABenchmark_startInstanceWithStr,(IArg)"Benchmark sprintf",2,(IArg)"sprintf");
        sprintf(myStr,"Output this event to a string\n");
        Log_write3(UIABenchmark_stopInstanceWithStr,(IArg)"Benchmark sprintf",2,(IArg)"sprintf");

        /* 3: measure the overhead of the Log_write3 APIs used to log the benchmark events themselves. */
        Log_write3(UIABenchmark_startInstanceWithStr,(IArg)"Benchmark Log_write3",3,(IArg)"Log_write3");
        Log_write3(UIABenchmark_stopInstanceWithStr,(IArg)"Benchmark Log_write3",3,(IArg)"Log_write3");

        /* Finished! */
        Log_info0("Finished Tutorial 1B!");
}
/*
 *  @(#) ti.uia.examples.tutorial1; 1, 0, 0, 0,1; 7-13-2012 11:16:57; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

