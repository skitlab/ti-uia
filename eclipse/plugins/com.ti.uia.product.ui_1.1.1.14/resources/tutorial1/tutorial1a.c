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
 * ======== System Analyzer Tutorial 1A : Logging Events ========
 * This tutorial demonstrates the use of the Log module to
 * log a number of different types of events, and how
 * to run and use System Analyzer to display the events.
 *
 * See http://processors.wiki.ti.com/index.php/McsaTutorial1 for more info.
 */

/* We need to use the XDC standard types defined.
 * The .h file for this module is referenced as follows: */
#include <xdc/std.h>

/* We also need to use APIs defined in the xdc.runtime.Log module,
 * and events defined in the UIAEvt, UIAErr and UIAStatistic modules.
 * The .h files for these module are referenced below: */
#include <xdc/runtime/Log.h>
#include <ti/uia/events/UIAEvt.h>
#include <ti/uia/events/UIAErr.h>
#include <ti/uia/events/UIAStatistic.h>

/* The following constants used as event and error constants
 * for use with the UIAErr and UIAEvt events.
 */
#define DETAIL_EVENT_CODE (0x1111)
#define CRITICAL_EVENT_CODE (0xCCCC)
#define FATAL_EVENT_CODE (0xFFFF)

void tutorial_1A();

void tutorial_1A(){
        int param1 = 1234;
        int param2 = 0x12345678;
        int data = 0x7654321;
        int instanceId = 1;
        int numWordsProcessed = 0xABCDEF;

        /*  The Log_info APIs (Log_info0..Log_info5) allow you to logging generic
         *  "informational" events that report what line of code logged the event.
         *  They allow you to log a printf-style string along with 0 to 5 values
         *  containing information such as event codes, details about what occurred
         *  application state information, etc.
         */
        Log_info0("Hello World!");

        /* Use Log_warning[0..6] to log an event that reports a warning-level event. */
        Log_warning1("This is a warning with one parameter: %d",param1);
        /* Use Log_error[0..6] to log an event to report that a recoverable error has occurred */
        Log_error2("This is an error with two parameters: %d,0x%x",param1,param2);

        /* The Log_write[0]..[7] APIs provide a lower-level API that allows you to
         * specify a specific event to log.  Unlike the Log_info, Log_warning and Log_error
         * APIs, they do not by default log information about the line of code that
         * the event was logged from.  Each event has a predefined set of parameters that
         * should be logged with the event.  Please read the CDOC documentation for 
         * the event to see what parameters should be logged and for examples that demonstrate
         * the use of the event.
         *
         * For example, the UIAErr module provides a number of predefined events that you can
         * use to log error conditions such as exceptions, critical errors,
         * and fatal errors.  The CDOC documentation for the ti.uia.events.UIAErr module
         * provides a list of all of the error events defined in this module.
         */
        Log_write4(UIAErr_criticalWithStr,CRITICAL_EVENT_CODE,
                        (IArg)"This is what a critical event looks like. It was logged from %$F",
                        (IArg)__FILE__,(IArg)__LINE__);
        Log_write4(UIAErr_fatalWithStr,FATAL_EVENT_CODE,
                        (IArg)"This is what a critical event looks like. It was logged from %$F",
                        (IArg)__FILE__,(IArg)__LINE__);
                        
        /* The UIAEvt module provides a number of predefined events that you can
         * use to log informational events.  The 'detail' level events are lower
         * in priority than info events.
         */
        Log_write5(UIAEvt_detailWithStr,DETAIL_EVENT_CODE,
                        (IArg)"We\'ve just logged a detailed event! data=%d logged from file %s at line %d",
                        data,(IArg)__FILE__,(IArg)__LINE__);

        /* The UIAStatistic module provides predefined events for logging statistical
         * information that can be viewed using System Analyzer's graphs, charts, etc.
         * Each predefined event has a predefined format string so you don't have
         * to specify one as a parameter for the Log_write event.  You will need to
         * check the documentation for the event to see what parameters the
         * format string expects.   If you hover the mouse over the UIAStatistic
         * event in the following line of code, you should see a tooltip that contains
         * a brief description of the event.
         */
        Log_write4(UIAStatistic_wordsProcessedByInstance,
                        (IArg)__FILE__,(IArg)__LINE__,instanceId,numWordsProcessed);

}
/*
 *  @(#) ti.uia.examples.tutorial1; 1, 0, 0, 0,1; 7-13-2012 11:16:57; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

