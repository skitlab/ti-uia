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
 
/***************************************************************************/
/*                                                                         */
/*                      System Analyzer and the                            */
/*              Unified Instrumentation Architecture (UIA)                 */
/*                                                                         */
/*             Tutorial 2: Graphing events, JTAG Run-Mode                  */
/*                                                                         */
/*                          M A I N . C                                    */
/*                                                                         */
/***************************************************************************/

/* We need to use the XDC standard types defined.
 * The .h file for this module is referenced as follows: */
#include <xdc/std.h>

/* Reference the xdc.runtime.Log module in order to use the Log_write4 and Log_write5 APIs.*/
#include <xdc/runtime/Log.h>

/* Reference the ti.uia.events.UIAEvt module in order to use the UIAEvt_intWithKey event */
#include <ti/uia/events/UIAEvt.h>

volatile int slider1Value = 0;
volatile int slider2Value = 1024;

void startup();

/*
 * ======== main ========
 * This tutorial demonstrates the steps needed to capture and graph data from
 * a running application, using LoggerCircBuf for JTAG Run mode event upload.
 *
 * NOTE: this tutorial requires a C6000 target device, and does not
 * run on simulators.
 *
 * See http://processors.wiki.ti.com/index.php/McsaTutorial2 for more info.
 */
void main(){

   volatile int lastSlider1Value = slider1Value;
   volatile int lastSlider2Value = slider2Value;
   int slider1InstanceId = 1;


   startup();

   /* Log an event whenever the GEL sliders change values. */
   while (TRUE){

           /* The UIAEvt_intWithKey event is used to log an integer value along with a key string that is used
            * by System Analyzer to determine which set of events the event belongs with.  All events that have the
            * same key string will be plotted on the same line in the Count Analysis graph and will be used
            * to calculate min / max / average statistics for that set of events.
            *
            * The key string consists of a 'rendered' format string that can contain format specifiers for up
            * to 4 values.  The two Log_writeX statements in the code below show two different ways of
            * specifying a key string - logging a parameter that will be included in the rendered string, or
            * using a constant string.
            *
            * See http://processors.wiki.ti.com/index.php/McsaTutorial2 for more details.
            */
           if (lastSlider1Value != slider1Value){
                   lastSlider1Value = slider1Value;


                   Log_write5(UIAEvt_intWithKey, lastSlider1Value,0,0,(IArg)"Slider 1 Values.  InstanceId=0x%x.",slider1InstanceId);
           }
           if (lastSlider2Value != slider2Value){
                   lastSlider2Value = slider2Value;
                   Log_write4(UIAEvt_intWithKey, lastSlider2Value,0,0,(IArg)"Slider 2 Values.  InstanceId=2");
           }
   }
}

/* ======== startup ==========
 * Configure the target's cache to enable L2 cache
 * and make a region of external memory cacheable.
 */
void startup(){
        int *MAR128 = (int *)0x1848200;
        int *L2CFG = (int *)0x1840000;
        *L2CFG = ((*L2CFG)& 0xFFFFFFF0) | 1;  /* set L2 cache size to 32K */

        /* Make 0x80000000 to 0x80FFFFFF : external memory block cacheable */
        *MAR128 = 1;
}
/*
 *  @(#) ti.uia.examples.tutorial2; 1, 0, 0, 0,1; 7-13-2012 11:16:57; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

