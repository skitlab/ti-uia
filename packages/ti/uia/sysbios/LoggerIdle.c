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
 *  ======== LoggerIdle.c ========
 */
#include <xdc/std.h>

#include <xdc/runtime/Log.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/uia/runtime/EventHdr.h>

#include <package/internal/LoggerIdle.xdc.h>

/* Number of words written to buffer for each event */
#define WRITE0_IN_BITS32 2
#define WRITE1_IN_BITS32 3
#define WRITE2_IN_BITS32 4
#define WRITE4_IN_BITS32 6
#define WRITE8_IN_BITS32 10

#define BITS32_TO_BITS8(bits32) ((bits32) * 4)

/*
 *  ======== isThereSpace =========
 *  Returns true if there is enough space to write to the buffer.
 */
static inline Bool isThereSpace(UInt32 *writePtr, SizeT numBits32ToWrite)
{
    if (LoggerIdle_module->empty) {
        return TRUE;
    }
    else if (writePtr > LoggerIdle_module->bufferRead) {
        return TRUE;
    }
    else if (LoggerIdle_module->bufferRead - writePtr >= numBits32ToWrite &&
                LoggerIdle_module->bufferRead < LoggerIdle_module->bufferEnd) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/*
 *  ======== writeStart =========
 *  Writes the event header, timestamp and event and module ID for all events.
 *
 *  Checks if the event should be written and writes the event header.
 *  If timestamps are enabled it writes timestamp, and for all types
 *  write the event and module ID. Returns false if the event is not written.
 */
static inline UInt32 *writeStart(UInt32 *writePtr, SizeT numBits32ToWrite, Log_Event evt, Types_ModuleId mid)
{    
    Types_Timestamp64 tstamp;
    
    /* Logger is disabled. */
    if (!LoggerIdle_module->enabled) {
        return NULL;
    }
    
    if (LoggerIdle_isTimestampEnabled) {
        /* Check if there's enough space for event with timestamp */
        if (isThereSpace(writePtr, numBits32ToWrite + 2)) {
            /* Write timestamp event header */
            *writePtr++ = EventHdr_genEventHdrWord1(BITS32_TO_BITS8(numBits32ToWrite + 2), 
                                          LoggerIdle_module->idleSequence, 
                                          EventHdr_HdrType_EventWithTimestamp);
            /* Get and write the timestamp */
            Timestamp_get64(&tstamp);
            *writePtr++ = tstamp.lo;
            *writePtr++ = tstamp.hi;
        }
        else {
            /* Not enough space */
            return NULL;
        }
    }
    else {
        /* Check if there's enough space for event without timestamp */
        if (isThereSpace(writePtr, numBits32ToWrite)) {
            /* Write event header */
            *writePtr++ = EventHdr_genEventHdrWord1(BITS32_TO_BITS8(numBits32ToWrite), 
                                            LoggerIdle_module->idleSequence, 
                                            EventHdr_HdrType_Event);
        }
        else {
            /* Not enough space */
            return NULL;
        }
    }
    
    /* Write event ID and module ID */
    *writePtr++ = Types_makeEvent(Log_getEventId(evt), mid);
    return writePtr;
}

/*
 *  ======== writeFinish =========
 *  Incrememnt write pointer and mark buffer not empty.
 */
static inline Void writeFinish(UInt32 *writePtr)
{
    /* 
     *  If write pointer is inside the pad, set the pad pointer to its 
     *  location and set the write pointer to the begining of the buffer.
     *  Else increment the pointer normally.
     */
    if (writePtr > LoggerIdle_module->bufferEnd ) {
        LoggerIdle_module->bufferPad = (writePtr - 1);
        LoggerIdle_module->bufferWrite = LoggerIdle_module->idleBuffer;
    }
    else {
        LoggerIdle_module->bufferWrite = writePtr;
    }
    LoggerIdle_module->empty = FALSE;      /* Buffer now has data in it */
}

/*
 *  ======== LoggerIdle_idleWrite =========
 *  Idle function that sends log data to the users transport function.
 *
 *  This function is plugged into idle and will run when no other threads have
 *  priority. Each time through it will send part of the buffer to the
 *  transport function.  The transport function is of type LoggerFxn and
 *  passes in a UChar pointer to the begining of the buffer and a length to
 *  write.  The number of MAU written is returned.  This function runs in
 *  idle so the transport function should not be waiting to write characters.
 */
Void LoggerIdle_idleWrite()
{
    UInt key;
    Int lengthInMAU, MAUWritten;
    
    /* Send the buffer if there is data */
    if (!LoggerIdle_module->empty) {
        /* Get length of buffer to send */
        if (LoggerIdle_module->bufferRead < LoggerIdle_module->bufferWrite) {
            /* Send all the data in the buffer */
            lengthInMAU = (Bits32)LoggerIdle_module->bufferWrite -
                                                                        (Bits32)LoggerIdle_module->bufferRead;
        }
        else {
            /* Buffer has wrapped, send everything from read to the pad pointer */
            lengthInMAU = ((Bits32)LoggerIdle_module->bufferPad - 
                                                                    (Bits32)LoggerIdle_module->bufferRead) + sizeof(UInt32);
        }
        
        /* Send the buffer to the configured transport function */
        MAUWritten = LoggerIdle_module->loggerFxn((UChar *)LoggerIdle_module->bufferRead, lengthInMAU);
        
        
        /* Read is at the end of the data in the pad, wrap to begining */
        if ((Bits32)LoggerIdle_module->bufferRead + MAUWritten > (Bits32)LoggerIdle_module->bufferPad) {
            LoggerIdle_module->bufferRead = LoggerIdle_module->idleBuffer;
        }
        else {
            /* Increment read pointer to end of sent characters */
            LoggerIdle_module->bufferRead = (UInt32 *)((Bits32)LoggerIdle_module->bufferRead + MAUWritten);
        }
        
        key = Hwi_disable();
        
        /* If buffer is empty, set flag to true */
        if ((LoggerIdle_module->bufferRead == LoggerIdle_module->bufferWrite) && MAUWritten > 0) {
            LoggerIdle_module->empty = TRUE;
        }
        Hwi_restore(key);
    }
}

/*
 *  ======== LoggerIdle_Instance_init =========
 */
Void LoggerIdle_Instance_init(LoggerIdle_Object *obj,
    const LoggerIdle_Params *prms)
{
}

/*
 *  ======== LoggerIdle_disable ========
 */
Bool LoggerIdle_disable(LoggerIdle_Object *obj)
{
    UInt key = Hwi_disable();
    Bool prev = LoggerIdle_module->enabled;
    LoggerIdle_module->enabled = FALSE;
    Hwi_restore(key);
    return (prev);
}

/*
 *  ======== LoggerIdle_enable ========
 */
Bool LoggerIdle_enable(LoggerIdle_Object *obj)
{
    UInt key = Hwi_disable();
    Bool prev = LoggerIdle_module->enabled;
    LoggerIdle_module->enabled = TRUE;
    Hwi_restore(key);
    return (prev);
}

/*
 *  ======== write0 =========
 */
Void LoggerIdle_write0(LoggerIdle_Object *obj, Log_Event evt,
                      Types_ModuleId mid)
{
    UInt32 *writePtr;
    UInt key = Hwi_disable();
    
    LoggerIdle_module->idleSequence++;
    writePtr = writeStart(LoggerIdle_module->bufferWrite, WRITE0_IN_BITS32, evt, mid);  /* Write event header */
    
    if (writePtr == NULL) {
        /* Event was not written, exit */
        Hwi_restore(key);
        return;
    }
    
    writeFinish(writePtr);                             /* Set the pad and empty flag */
    Hwi_restore(key);
}

/*
 *  ======== write1 =========
 */
Void LoggerIdle_write1(LoggerIdle_Object *obj, Log_Event evt,
                      Types_ModuleId mid, IArg a1)
{
    UInt32 *writePtr;
    UInt key = Hwi_disable();
    
    LoggerIdle_module->idleSequence++;
    writePtr = writeStart(LoggerIdle_module->bufferWrite, WRITE1_IN_BITS32, evt, mid);  /* Write event header */
    
    if (writePtr == NULL) {
        /* Event was not written, exit */
        Hwi_restore(key);
        return;
    }
        
    /* Write the event data */
    *writePtr++ = a1;
    
    writeFinish(writePtr);                             /* Set the pad and empty flag */
    Hwi_restore(key);
}

/*
 *  ======== write2 =========
 */
Void LoggerIdle_write2(LoggerIdle_Object *obj, Log_Event evt,
                      Types_ModuleId mid, IArg a1, IArg a2)
{
    UInt32 *writePtr;
    UInt key = Hwi_disable();
    
    LoggerIdle_module->idleSequence++;
    writePtr = writeStart(LoggerIdle_module->bufferWrite, WRITE2_IN_BITS32, evt, mid);  /* Write event header */
    
    if (writePtr == NULL) {
        /* Event was not written, exit */
        Hwi_restore(key);
        return;
    }
        
    /* Write the event data */
    *writePtr++ = a1;
    *writePtr++ = a2;
    
    writeFinish(writePtr);                             /* Set the pad and empty flag */
    Hwi_restore(key);
}

/*
 *  ======== write4 =========
 */
Void LoggerIdle_write4(LoggerIdle_Object *obj, Log_Event evt,
                      Types_ModuleId mid, IArg a1, IArg a2, IArg a3, IArg a4)
{
    UInt32 *writePtr;
    UInt key = Hwi_disable();
    
    LoggerIdle_module->idleSequence++;
    writePtr = writeStart(LoggerIdle_module->bufferWrite, WRITE4_IN_BITS32, evt, mid);  /* Write event header */
    
    if (writePtr == NULL) {
        /* Event was not written, exit */
        Hwi_restore(key);
        return;
    }
        
    /* Write the event data */
    *writePtr++ = a1;
    *writePtr++ = a2;
    *writePtr++ = a3;
    *writePtr++ = a4;
    
    writeFinish(writePtr);                             /* Set the pad and empty flag */
    Hwi_restore(key);
}

/*
 *  ======== write8 =========
 */
Void LoggerIdle_write8(LoggerIdle_Object *obj, Log_Event evt,
                      Types_ModuleId mid, IArg a1, IArg a2, IArg a3, IArg a4,
                      IArg a5, IArg a6, IArg a7, IArg a8)
{
    UInt32 *writePtr;
    UInt key = Hwi_disable();
    
    LoggerIdle_module->idleSequence++;
    writePtr = writeStart(LoggerIdle_module->bufferWrite, WRITE8_IN_BITS32, evt, mid);  /* Write event header */
    
    if (writePtr == NULL) {
        /* Event was not written, exit */
        Hwi_restore(key);
        return;
    }
        
    /* Write the event data */
    *writePtr++ = a1;
    *writePtr++ = a2;
    *writePtr++ = a3;
    *writePtr++ = a4;
    *writePtr++ = a5;
    *writePtr++ = a6;
    *writePtr++ = a7;
    *writePtr++ = a8;
    
    writeFinish(writePtr);                             /* Set the pad and empty flag */
    Hwi_restore(key);
}
/*
 *  @(#) ti.uia.sysbios; 1, 0, 0, 0,1; 7-13-2012 11:12:38; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

