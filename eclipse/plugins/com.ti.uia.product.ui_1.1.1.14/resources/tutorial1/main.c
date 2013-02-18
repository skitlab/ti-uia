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
/*                    System Analyzer and the                              */
/*              Unified Instrumentation Architecture (UIA)                 */
/*                                                                         */
/*     Tutorial 1: Logging events, benchmarking, controlling events        */
/*                                                                         */
/*                          M A I N . C                                    */
/*                                                                         */
/***************************************************************************/

/* We need to use the XDC standard types defined.
 * The .h file for this module is referenced as follows: */
#include <xdc/std.h>

extern void tutorial_1A();
extern void tutorial_1B();
extern void tutorial_1C();
extern void tutorial_1D();

volatile int tutorialPhase = 0;

void startup();


/*
 * ======== main ========
 * This program demonstrates a number of features of the
 * System Analyzer and the associated
 * Unified Instrumentation Architecture (UIA) target content
 * package.  The System Analyzer Tutorial 1 is available online at
 * http://processors.wiki.ti.com/index.php/Multicore_System_Analyzer_Tutorials
 *
 * The accompanying MSCA_Tutorial.gel GEL script provides a
 * simple way to select which part of the tutorial to run.
 *
 * To load the GEL script, open the Control Panel:
 * (in CCSv5.0.x: Winkdow / Show View / Other... / Debug / Control Panel).
 * In the left hand pane, select GEL Files.  In the
 * right hand pane, right click, select Load Gel..., and
 * browse to the location of your project in the workspace
 * and open systemAnalyzerTutorial1.gel.
 * (You can find out where the project is located by
 * right clicking on the name of the project in the C/C++ Projects
 * view and selecting Properties from the context menu.
 *
 * To run the GEL script, select Scripts from the main CCS menu
 * click on System Analyzer Tutorial 1 and then select which tutorial you
 * would like to run.  The GEL script assumes that the
 * project has been loaded on a C6X target (either simulator
 * or silicon target) and that the target is halted.  It also
 * assumes that you have already started the System Analyzer.
 *
 * To run System Analyzer, in CCS select Tools / System Analyzer / Live.
 * In the dialog box that opens, select the "Until Stop is Requested"
 * radio button and click OK.
 *
 * See http://processors.wiki.ti.com/index.php/McsaTutorial1 for more info.
 */
void main()
{
        /* Configure the target's cache */
        startup();

        /* Run the tutorial selected by the tutorialPhase value.*/
        while (tutorialPhase < 5){
                switch(tutorialPhase){
                case 1: tutorial_1A(); break;
                case 2: tutorial_1B(); break;
                case 3: tutorial_1C(); break;
                case 4: tutorial_1D(); break;
                }
                tutorialPhase = 0;

                /* The following label provides an address that the systemAnalyzerTutorial1.gel
                 * script uses to set a breakpoint.
                 */
                asm(" .global BKPT_TUTORIAL1");
                asm("BKPT_TUTORIAL1:");
        }
}

/* ======== startup ==========
 * Configure the target's cache to enable L2 cache
 * and make a region of external memory cacheable.
 */
void startup(){
#ifdef xdc_target__isaCompatible_64P
        int *MAR128 = (int *)0x1848200;
        int *L2CFG = (int *)0x1840000;
        *L2CFG = ((*L2CFG)& 0xFFFFFFF0) | 1;  /* set L2 cache size to 32K */

        /* Make 0x80000000 to 0x80FFFFFF : external memory block cacheable */
        *MAR128 = 1;
#endif
}
/*
 *  @(#) ti.uia.examples.tutorial1; 1, 0, 0, 0,1; 7-13-2012 11:16:56; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

