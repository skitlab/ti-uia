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
 *  ======== LoggingSetup.xdc ========
 */

package ti.uia.sysbios;

/*!
 *  ======== LoggingSetup ========
 *  Module to aid in configuring SYSBIOS logging using UIA and System Analyzer
 * @p
 * The LoggingSetup module automates the process of configuring an application
 * to use UIA events, and configures SYS/BIOS modules to capture user-specified
 * information such as CPU Load, Task Load and Task Execution so that it can
 * be displayed by System Analyzer.  It also automates the creation of 
 * infrastructure modules such as loggers, the ServiceManager and RTA modules
 * to enable the capture and upload of the events over a user-specified transport.
 * Both JTAG and Non-JTAG transports are supported.
 * @p
 *  The following configuration script demonstrates the use of the LoggingSetup
 *  module in the XDC configuration file for the application:
 *
 * @a(Example)
 * Example 1: Configuring an application to use the default settings provided
 * by LoggingSetup.  The following default settings are automatically applied:
 * @p(blist)
 *    - Logging UIA events from user-provided C code.  User provided C code is
 *    treated as part of the xdc.runtime.Main module.  A circular buffer with
 *    a buffer size of 32 KBytes is enabled by default to support this.
 *   - Event logging is enabled for the SYS/BIOS Load and Task modules in order to 
 *   allow System Analyzer to display CPU Load, Task Load, and Task Execution 
 *   information.  Logging of SWI and HWI events is disabled by default.
 *   In order to optimize event capture and minimize event loss, two loggers 
 *   are created: one to store events from the SYS/BIOS Load module
 *   and the other to store events from other SYS/BIOS modules.
 *   - Multicore event correlation is enabled by default.  This enables the
 *    LogSync module and creation of a dedicated logger for sync point events
 *    with a circular buffer size of 8 KBytes.
 *   - The Event Upload Mode is configured for NONJTAG_AND_JTAGSTOPMODE.  This
 *    allows events to be uploaded in real-time via the Non-JTAG transport
 *    specified by the ti.uia.runtime.ServiceManager module, and also be uploaded
 *    when the target halts via JTAG.  If the ServiceManager module is not
 *    used in the application, the transport falls back to JTAGSTOPMODE.
 *   - An Overflow logger will be automatically created to capture events that 
 *    occurred while the transport was waiting to upload older events to the host.
 *    The logger's circular buffer size is set to 2K Bytes.
 *  @p 
 *  @p(code)
 *  // the Log module provides logging APIs for use by the user's software
 *  var Log = xdc.useModule('xdc.runtime.Log');
 *  // the LoggingSetup module's default settings configure much of the UIA infrastructure.
 *  var LoggingSetup = xdc.useModule('ti.uia.sysbios.LoggingSetup');
 *  @p
 *  @p(html)
 *  <hr />
 *  @p
 * @a(Example)
 * Example 2: A number of 'template' applications are available that 
 * provide predefined XDC configuration scripts and C code for use in new
 * projects.  These templates provide good examples of how to configure all 
 * of the various modules that are involved in setting up the UIA infrastructure,
 * including the LoggingSetup module.  The templates can be downloaded from
 * the System Analyzer Wiki site at 
 *  @p(html)
 *  <a href="http://processors.wiki.ti.com/index.php/System_Analyzer">
 * http://processors.wiki.ti.com/index.php/System_Analyzer</a>
 * @p
 * They can also be generated directly by CCS, using the CCS New Project 
 * Wizard.  The following steps show how to use CCSv5.0.x to generate a new project
 * that configure the NDK to provide an Ethernet transport for uploading events 
 * from the target to the host, please perform the following steps in CCS. :
 * @p(blist)
 *   - File / New / CCS Project : opens the 'New CCS Project' dialog
 *   - <enter a name for the project>
 *   - <select the type of project>
 *   - <accept defaults for Additional Project Settings>
 *   - <configure the project settings for compiler options, etc.>
 *   - For Project Templates, expand the UIA and System Analyzer Examples section
 *   - select evm6472: Stairstep for a single core with UIA to see how
 *   to configure the NDK to use Ethernet as a transport for UIA events and
 *   commands.  
 *  - select evm6472: MessageQ (single image for all cores) with UIA
 *   to see how to create a multicore application that uses the same application
 *   software for all cores, and uses IPC to move event data from CPU cores 1-5
 *   to CPU core 0, with CPU core 0 using the NDK for Ethernet communications
 *   with the host.
 *  @p
 * 
 *  @p(html)
 *  <hr />
 */ 
metaonly module LoggingSetup 
{

    /*!
     *  ======== UploadMode ========
     */
    enum UploadMode {
        UploadMode_SIMULATOR = 1, /* note that simulators use probe points */
        UploadMode_PROBEPOINT = 2,
        UploadMode_JTAGSTOPMODE = 3,
        UploadMode_JTAGRUNMODE = 4,
        UploadMode_NONJTAGTRANSPORT = 5,
        UploadMode_NONJTAG_AND_JTAGSTOPMODE = 6,
        UploadMode_STREAMER = 7,
        UploadMode_IDLE = 8
    }
        
    /*!
     *  ======== loadLogger ========
     *  Logger used for the Load module Log events
     */
    config xdc.runtime.ILogger.Handle loadLogger = null;
    
    /*!
     *  ======== loadLoggerSize ========
     *  Size (in MAUs) of logger used for the Load module Log events.
     */
    metaonly config SizeT loadLoggerSize = 512;
    
    /*!
     *  ======== loadLogging ========
     *  Enable the Load module event logging.
     *
     *  If this is false, the events will be disabled. Otherwise the events 
     *  will be enabled.
     *  Use the {@link #loadLoggingRuntimeControl} parameter 
     *  to determine whether the state can be modified during runtime.
     */
    metaonly config Bool loadLogging = true;
    
    /*!
     *  ======== loadLoggingRuntimeControl ========
     *  Specify whether load logging can be enabled / disabled at runtime.
     *
     *  This determines what diags settings are applied to the module's diags
     *  mask. If 'false', the diags bits will be configured as 
     *  ALWAYS_ON, meaning they can't be changed at runtime. If 'true', the 
     *  bits will be configured as 'RUNTIME_ON'.
     *
     *  Use the {@link #loadLogging} parameter 
     *  to determine whether the event is ON or OFF. For example, the
     *  following two lines set the Load modules events to 
     *  initially be 'ALWAYS_ON'.
     *
     *  @p(code)
     *  LoggingSetup.loadLogging = true;   
     *  LoggingSetup.loadLoggingRuntimeControl = false;
     *  @p
     */
    metaonly config Bool loadLoggingRuntimeControl = true;
    
    /*!
     *  ======== mainLogger ========
     *  Logger used for main and non-XDC modules Log events
     */
    config xdc.runtime.ILogger.Handle mainLogger = null;
    
    /*!
     *  ======== mainLoggerSize ========
     *  Size (in MAUs) of logger used for the main and non-XDC modules Log events
     */
    metaonly config SizeT mainLoggerSize = 1024;
    
    /*!
     *  ======== mainLogging ========
     *  Enable main and non-XDC modules event logging
     *
     *  If this is false, the events will be disabled. Otherwise the events 
     *  will be enabled.
     *  Use the {@link #mainLoggingRuntimeControl} parameter 
     *  to determine whether the state can be modified during runtime.
     */
    metaonly config Bool mainLogging = true;
    
    /*!
     *  ======== mainLoggingRuntimeControl ========
     *  Specify whether main logging can be enabled / disabled at runtime.
     *
     *  This determines what diags settings are applied to the module's diags
     *  mask. If 'false', the diags bits will be configured as 
     *  ALWAYS_ON, meaning they can't be changed at runtime. If 'true', the 
     *  bits will be configured as 'RUNTIME_ON'.
     *
     *  Use the {@link #mainLogging} parameter 
     *  to determine whether the event is ON or OFF. For example, the
     *  following two lines set the Load modules events to 
     *  initially be 'ALWAYS_ON'.
     *
     *  @p(code)
     *  LoggingSetup.mainLogging = true;   
     *  LoggingSetup.mainLoggingRuntimeControl = false;
     *  @p
     */
    metaonly config Bool mainLoggingRuntimeControl = true;
    
    /*!
     *  ======== sysbiosLogger ========
     *  Logger used for SYSBIOS modules Log events
     */
    config xdc.runtime.ILogger.Handle sysbiosLogger = null;
    
    /*!
     *  ======== sysbiosLoggerSize ========
     *  Size (in MAUs) of the logger used for the SYS/BIOS modules' Log events
     */
    metaonly config SizeT sysbiosLoggerSize = 1024;
    
    /*!
     *  ======== sysbiosHwiLogging ========
     *  Enable SYSBIOS Hwi and Clock modules' event logging
     *
     *  If this is false, the events will be disabled. Otherwise the events 
     *  will be enabled.
     *  Use the {@link #sysbiosHwiLoggingRuntimeControl} parameter 
     *  to determine whether the state can be modified during runtime.
     */
    metaonly config Bool sysbiosHwiLogging = false;
    
    /*!
     *  ======== sysbiosHwiLoggingRuntimeControl ========
     *  Specify whether Hwi and Clock logging can be enabled / disabled at runtime
     *
     *  This determines what diags settings are applied to the module's diags
     *  mask. If 'false', the diags bits will be configured as 
     *  ALWAYS_ON, meaning they can't be changed at runtime. If 'true', the 
     *  bits will be configured as 'RUNTIME_ON'.
     *
     *  Use the {@link #sysbiosHwiLogging} parameter 
     *  to determine whether the event is ON or OFF. For example, the
     *  following two lines set the Load modules events to 
     *  initially be 'ALWAYS_ON'.
     *
     *  @p(code)
     *  LoggingSetup.sysbiosHwiLogging = true;   
     *  LoggingSetup.sysbiosHwiLoggingRuntimeControl = false;
     *  @p
     */
    metaonly config Bool sysbiosHwiLoggingRuntimeControl = false;
    
    /*!
     *  ======== sysbiosSwiLogging ========
     *  Enable SYSBIOS Swi module's event logging
     *
     *  If this is false, the events will be disabled. Otherwise the events 
     *  will be enabled.
     *  Use the {@link #sysbiosSwiLoggingRuntimeControl} parameter 
     *  to determine whether the state can be modified during runtime.
     */
    metaonly config Bool sysbiosSwiLogging = false;
    
    /*!
     *  ======== sysbiosSwiLoggingRuntimeControl ========
     *  Specify whether Swi logging can be enabled / disabled at runtime.
     *
     *  This determines what diags settings are applied to the module's diags
     *  mask. If 'false', the diags bits will be configured as 
     *  ALWAYS_ON, meaning they can't be changed at runtime. If 'true', the 
     *  bits will be configured as 'RUNTIME_ON'.
     *
     *  Use the {@link #sysbiosSwiLogging} parameter 
     *  to determine whether the event is ON or OFF. For example, the
     *  following two lines set the Load modules events to 
     *  initially be 'ALWAYS_ON'.
     *
     *  @p(code)
     *  LoggingSetup.sysbiosSwiLogging = true;   
     *  LoggingSetup.sysbiosSwiLoggingRuntimeControl = false;
     *  @p
     */
    metaonly config Bool sysbiosSwiLoggingRuntimeControl = false;
    
    /*!
     *  ======== sysbiosTaskLogging ========
     *  Enable SYSBIOS Task module's event logging
     *
     *  If this is false, the events will be disabled. Otherwise the events 
     *  will be enabled.
     *  Use the {@link #sysbiosTaskLoggingRuntimeControl} parameter 
     *  to determine whether the state can be modified during runtime.
     */
    metaonly config Bool sysbiosTaskLogging = true;
    
    /*!
     *  ======== sysbiosTaskLoggingRuntimeControl ========
     *  Specify whether Task logging can be enabled / disabled at runtime.
     *
     *  This determines what diags settings are applied to the module's diags
     *  mask. If 'false', the diags bits will be configured as 
     *  ALWAYS_ON, meaning they can't be changed at runtime. If 'true', the 
     *  bits will be configured as 'RUNTIME_ON'.
     *
     *  Use the {@link #sysbiosTaskLogging} parameter 
     *  to determine whether the event is ON or OFF. For example, the
     *  following two lines set the Load modules events to 
     *  initially be 'ALWAYS_ON'.
     *
     *  @p(code)
     *  LoggingSetup.sysbiosTaskLogging = true;   
     *  LoggingSetup.sysbiosTaskLoggingRuntimeControl = false;
     *  @p
     */
    metaonly config Bool sysbiosTaskLoggingRuntimeControl = true;

    /*!
     *  ======== overflowLoggerSize ========
     *  Size of logger used for overflow events when
     *  uploadMode is either JTAGRUNMODE or NONJTAG_AND_JTAGSTOPMODE
     */
    metaonly config SizeT overflowLoggerSize = 1024;
    
    /*!
     *  ========= eventUploadMode ========
     *  Event upload mode
     *  @p
     *  Upload_SIMULATOR: events are uploaded from the simulator 
     *  at the time the event is logged.  
     *  @p(blist)
     *   - Upload_PROBEPOINT: events are uploaded at the time the event 
     *  is logged. The target is briefly halted while the event is uploaded.
     *   - Upload_JTAGSTOPMODE: events are uploaded over JTAG when the target halts
     *   - Upload_JTAGRUNMODE: events are uploaded via JTAG while the target is running.
     *   - Upload_NONJTAGTRANSPORT: events are uploaded over a non-JTAG transport such
     *  as Ethernet.  @see RTA for info on how to use the NDK as a transport.
     *   - Upload_NONJTAG_AND_JTAGSTOPMODE: events are uploaded over a non-JTAG transport.
     *  When the target halts (e.g. due to a breakpoint), any events that have not
     *  been uploaded yet are uploaded via JTAG.
     *  @p 
     *  
     *  @a(Example)
     *  The following is an example of the configuration script used
     *  to configure the system to use LoggerCircBuf loggers in order to
     *  stream events from the target to the host while the target is running
     *  over JTAG.  (Note that this mode is only supported for CPUs that 
     *  support real-time JTAG accesses such as those in the C6X family, 
     *  e.g. C64X+ and C66 CPUs)
     *   
     *  @p(code)
     *  var LoggingSetup = xdc.useModule('ti.uia.sysbios.LoggingSetup');
     *  LoggingSetup.eventUploadMode = LoggingSetup.UploadMode_JTAGRUNMODE;
     *   
     */
    metaonly config UploadMode eventUploadMode = UploadMode_JTAGSTOPMODE; 

    /*!
     * ======== disableMulticoreEventCorrelation ========
     * Set to true for single core applications.
     * 
     * When true the LoggingSetup module will not automatically
     * include the the LogSync module.  The LogSync module is
     * required in order to enable events from multiple CPU cores
     * to be correlated with each other.
     * @see ti.uia.runtime.LogSync  
     * 
     */
    metaonly config Bool disableMulticoreEventCorrelation = false;
   
    /*! @_nodoc
     * ======== createLogger =========
     * Internal helper function that creates the type of logger
     * appropriate for the LoggingSetup.uploadMode that has been configured.
     * 
     * @param(loggerSize): the size of the logger in MAUs
     * @param(loggerInstanceName): the name to assign to the logger instance
     * @param (loggerPriority): the IUIATransfer.Priority to assign to the logger instance
     * @a(return) returns the logger instance that was created
     */
     metaonly function createLogger(loggerSize,loggerInstanceName,loggerPriority);
}

/*
 */

/*
 *  @(#) ti.uia.sysbios; 1, 0, 0, 0,1; 7-13-2012 11:12:39; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

