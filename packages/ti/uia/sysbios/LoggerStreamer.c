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
 *  ======== LoggerStreamer.c ========
 */
#include <xdc/std.h>

#include <xdc/runtime/System.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Startup.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/uia/runtime/EventHdr.h>
#include <ti/uia/runtime/UIAPacket.h>
#include <ti/uia/runtime/IUIATransfer.h>
#include <xdc/runtime/Log.h>


#ifdef xdc_target__isaCompatible_64P
#include <c6x.h>
#endif

#include <package/internal/LoggerStreamer.xdc.h>

#define HDR_OFFSET_IN_WORDS 4        /* Size of the UIA header */
#define BYTES_IN_WORD 4
#define MAU_TO_BITS32(mau)          ((mau) / sizeof(Bits32))

static Int WRITE8_SIZE_IN_WORDS = 12;     /* write8  event size.  Set by prime function at runtime to 10 if timestamps disabled.  */
static Bool primeStatus = FALSE;

extern UInt16 ti_uia_sysbios_LoggerStreamer_uiaPacketSequence;

/*
 *  ======== LoggerStreamer_flush =========
 *  If there is data in the buffer, call the exchange function.
 */
Void LoggerStreamer_flush2(Void)
{
        /* If there is data in the buffer */
        if (LoggerStreamer_module->write
                        > LoggerStreamer_module->buffer + HDR_OFFSET_IN_WORDS) {
                /* Set UIA packet length and sequence number */
                UIAPacket_setEventLength((UIAPacket_Hdr*)LoggerStreamer_module->buffer,
                                (Bits32)((LoggerStreamer_module->write
                                                - LoggerStreamer_module->buffer) * BYTES_IN_WORD));
                UIAPacket_setSequenceCount((UIAPacket_Hdr*)LoggerStreamer_module->buffer,
                                ti_uia_sysbios_LoggerStreamer_uiaPacketSequence);


                /*
                 *  When the application calls flush there will always be empty space
                 *  at the end of the buffer. To let UIA know it should ignore this we
                 *  add a 32 bit Invalid UIA header with the length of the empty space.
                 */
                UIAPacket_setInvalidHdr(LoggerStreamer_module->write,
                                ((UInt32)LoggerStreamer_module->end + WRITE8_SIZE_IN_WORDS* BYTES_IN_WORD
                                                - (UInt32)LoggerStreamer_module->write) );

                /* Set the module write ptr to NULL to prevent log calls in exchange */
                if (LoggerStreamer_testForNullWrPtr) {
                        LoggerStreamer_module->write = NULL;
                }

                if (LoggerStreamer_isBadPacketDetectionEnabled) {
                        LoggerStreamer_validatePacket(LoggerStreamer_module->buffer, LoggerStreamer_bufSize);
                }
                /* Send filled buffer to exchange function */
                LoggerStreamer_module->buffer =
                                (UInt32*)LoggerStreamer_exchangeFxn((Ptr)LoggerStreamer_module->buffer);

                /* Update ptrs to new buffer */
                LoggerStreamer_module->write =
                                LoggerStreamer_module->buffer + HDR_OFFSET_IN_WORDS;
                LoggerStreamer_module->end =
                                LoggerStreamer_module->buffer
                                + (LoggerStreamer_bufSize/sizeof(UInt32)) - WRITE8_SIZE_IN_WORDS;
                ti_uia_sysbios_LoggerStreamer_uiaPacketSequence++;
        }
}
/*
 *  ======== LoggerStreamer_flush =========
 *  If there is data in the buffer, call the exchange function.
 */
Void LoggerStreamer_flush(Void)
{
        /* If there is data in the buffer */
        if (LoggerStreamer_module->write
                        > LoggerStreamer_module->buffer + HDR_OFFSET_IN_WORDS) {
                /* Set UIA packet length and sequence number */
                UIAPacket_setEventLength((UIAPacket_Hdr*)LoggerStreamer_module->buffer,
                                (Bits32)((LoggerStreamer_module->write
                                                - LoggerStreamer_module->buffer) * BYTES_IN_WORD));
                UIAPacket_setSequenceCount((UIAPacket_Hdr*)LoggerStreamer_module->buffer,
                                ti_uia_sysbios_LoggerStreamer_uiaPacketSequence);

                /*
                 *  Whe the application calls flush there will always be empty space
                 *  at the end of the buffer. To let UIA know it should ignore this we
                 *  add a 32 bit Invalid UIA header with the length of the empty space.
                 */
                UIAPacket_setInvalidHdr(LoggerStreamer_module->write,
                                (LoggerStreamer_module->end + WRITE8_SIZE_IN_WORDS
                                                - LoggerStreamer_module->write) * BYTES_IN_WORD);

                /* Set the module write ptr to NULL to prevent log calls in exchange */
                if (LoggerStreamer_testForNullWrPtr) {
                        LoggerStreamer_module->write = NULL;
                }

                /* Send filled buffer to exchange function */
                LoggerStreamer_module->buffer =
                                (UInt32*)LoggerStreamer_exchangeFxn((Ptr)LoggerStreamer_module->buffer);

                /* Update ptrs to new buffer */
                LoggerStreamer_module->write =
                                LoggerStreamer_module->buffer + HDR_OFFSET_IN_WORDS;
                LoggerStreamer_module->end =
                                LoggerStreamer_module->buffer
                                + (LoggerStreamer_bufSize/sizeof(UInt32)) - WRITE8_SIZE_IN_WORDS;
                ti_uia_sysbios_LoggerStreamer_uiaPacketSequence++;
        }
}

/*
 *  ======== LoggerStreamer_Prime =========
 */
Bool LoggerStreamer_prime(Ptr buffer)
{
        if (primeStatus == FALSE) {
                LoggerStreamer_module->buffer = (UInt32*)buffer;
                if (LoggerStreamer_isTimestampEnabled) {
                        WRITE8_SIZE_IN_WORDS = 12;
                }
                else {
                        WRITE8_SIZE_IN_WORDS = 10;
                }
                LoggerStreamer_module->write = (UInt32*)buffer + HDR_OFFSET_IN_WORDS;
                LoggerStreamer_module->end = (UInt32*)buffer
                                + (LoggerStreamer_bufSize/sizeof(UInt32)) - WRITE8_SIZE_IN_WORDS;
                primeStatus = TRUE;
                return (TRUE);
        }
        return (FALSE);
}

/*
 *  ======== LoggerStreamer_Module_startup ========
 */
Int LoggerStreamer_Module_startup(Int phase)
{
        LoggerStreamer_module->maxEventSizeInBits32 = MAU_TO_BITS32(LoggerStreamer_maxEventSize);
        LoggerStreamer_module->droppedEvents = 0;

        if (LoggerStreamer_primeFxn == NULL) {
                return (Startup_DONE);
        }
        LoggerStreamer_module->buffer = (UInt32*)LoggerStreamer_primeFxn();
        if (LoggerStreamer_module->buffer == NULL) {
                return (Startup_NOTDONE);
        }
        else {
                /* Set the maximum event size used to set the end pointer */
                if (LoggerStreamer_isTimestampEnabled) {
                        WRITE8_SIZE_IN_WORDS = 12;
                }
                else {
                        WRITE8_SIZE_IN_WORDS = 10;
                }
                LoggerStreamer_module->write = LoggerStreamer_module->buffer + HDR_OFFSET_IN_WORDS;
                LoggerStreamer_module->end = LoggerStreamer_module->buffer
                                + (LoggerStreamer_bufSize/sizeof(UInt32)) - WRITE8_SIZE_IN_WORDS;
                return (Startup_DONE);
        }
}

/*
 *  ======== LoggerStreamer_Instance_init =========
 *  Currently not implemented since we cannot dynamically 
 *  plug in loggers.
 */
Void LoggerStreamer_Instance_init(LoggerStreamer_Object *obj,
                const LoggerStreamer_Params *prms)
{
}

/*
 *  ======== LoggerStreamer_disable ========
 */
Bool LoggerStreamer_disable(LoggerStreamer_Object *obj)
{
        UInt key;
        Bool prev;

        key = Hwi_disable();
        prev = LoggerStreamer_module->enabled;
        LoggerStreamer_module->enabled = FALSE;
        Hwi_restore(key);

        return (prev);
}

/*
 *  ======== LoggerStreamer_enable ========
 */
Bool LoggerStreamer_enable(LoggerStreamer_Object *obj)
{
        UInt key;
        Bool prev;

        key = Hwi_disable();
        prev = LoggerStreamer_module->enabled;
        LoggerStreamer_module->enabled = TRUE;
        Hwi_restore(key);

        return (prev);
}

/*
 * ======== getNumDropped =========
 * returns the number of dropped events for this logger instance
 * TODO getStats instead? Add to IUIATransfer?
 */
Int LoggerStreamer_getNumDropped(LoggerStreamer_Object *obj)
{
        return (LoggerStreamer_module->droppedEvents);
}

/*
 *  ======== LoggerStreamer_getInstanceId ========
 *  NOT IMPLEMENTED.  Included in order to satisfy Interface requirements 
 */
UInt16 LoggerStreamer_getInstanceId(LoggerStreamer_Object *obj)
{
        return (0);
}

/*
 *  ======== LoggerStreamer_getPriority ========
 *  NOT IMPLEMENTED.  Included in order to satisfy Interface requirements 
 */
IUIATransfer_Priority LoggerStreamer_getPriority(LoggerStreamer_Object *obj)
{
        return (IUIATransfer_Priority_STANDARD);
}

/*
 *  ======== LoggerStreamer_setPriority ========
 *  NOT IMPLEMENTED.  Included in order to satisfy Interface requirements 
 */
Void LoggerStreamer_setPriority(LoggerStreamer_Object *obj, IUIATransfer_Priority priority)
{
}
/*
 *  ======== LoggerStreamer_getMaxLength ========
 */
SizeT LoggerStreamer_getMaxLength(LoggerStreamer_Object *obj)
{
        return (LoggerStreamer_maxEventSize);
}

/*
 *  ======== LoggerStreamer_reset ========
 *  NOT IMPLEMENTED.  Included in order to satisfy Interface requirements
 */
Void LoggerStreamer_reset(LoggerStreamer_Object *obj)
{
}

/*
 * ======== LoggerStreamer_getTransferType ========
 *  Returns whether the logger events can be sent over lossy transports or
 *  requires reliable transport
 */
IUIATransfer_TransferType LoggerStreamer_getTransferType(
                LoggerStreamer_Object *obj)
{
        return(IUIATransfer_TransferType_LOSSY);
}

/*
 * ======== LoggerStreamer_getContents =========
 * Fills buffer that is passed in with unread data, up to size MAU's in length.
 * NOT IMPLEMENTED.  Included in order to satisfy Interface requirements
 */
Bool LoggerStreamer_getContents(LoggerStreamer_Object *obj, Ptr hdrBuf,
                SizeT maxSize, SizeT *cpSize)
{
        return(FALSE);
}

/*
 * ======== LoggerStreamer_isEmpty ========
 * Returns true if the transfer buffer has no unread data
 */
Bool LoggerStreamer_isEmpty(LoggerStreamer_Object *obj)
{
        Bool result;
        if (LoggerStreamer_module->write == (LoggerStreamer_module->buffer+ HDR_OFFSET_IN_WORDS)) {
                result = TRUE;
        }
        else {
                result = FALSE;
        }
        return (result);
}
#if 0
#include <stdio.h>
static  Char badPacketReason[128] = "";
static UInt32 numPacketsChecked = 0;
static UInt32 numBadPacketsFound = 0;


Char* LoggerStreamer_validatePacket(UInt32* pPacketBuffer, UInt32 numBytesInPacket){
        Bool result = TRUE;
        UInt32 packetLength = 0;
        UInt32 eventLength = 0;
        UInt32 invalidLength = 0;
        UInt32 destAdrs = 0;
        UInt32 senderAdrs = 0;
        UInt32* pEvent = 0;
        UInt32 eventWord1 = 0;
        numPacketsChecked++;
        if (numBytesInPacket != LoggerStreamer_bufSize){
                result = FALSE;
                sprintf(badPacketReason,"LoggerStreamer_bufSize(%d) != numBytesInPacket(%d)",LoggerStreamer_bufSize,numBytesInPacket);
        }
        if (result){
                ti_uia_runtime_UIAPacket_Hdr* hdr = (ti_uia_runtime_UIAPacket_Hdr*)pPacketBuffer;
                /* 1. Check packet header */
                if (ti_uia_runtime_UIAPacket_getHdrType(hdr) == ti_uia_runtime_UIAPacket_HdrType_EventPkt){
                        destAdrs = ti_uia_runtime_UIAPacket_getDestAdrs(hdr);
                        senderAdrs = ti_uia_runtime_UIAPacket_getSenderAdrs(hdr);

                        packetLength = ti_uia_runtime_UIAPacket_getEventLength(hdr);
                        if (packetLength < numBytesInPacket){

                                /* Verify that the rest of the packet is represented by an invalid packet of the correct length */
                                hdr = (ti_uia_runtime_UIAPacket_Hdr*)((UInt32)pPacketBuffer + (UInt32)packetLength);
                                if (ti_uia_runtime_UIAPacket_getHdrType(hdr) == ti_uia_runtime_UIAPacket_HdrType_InvalidData){
                                        invalidLength = ti_uia_runtime_UIAPacket_getEventLength(hdr);
                                        if (invalidLength != numBytesInPacket - packetLength){
                                                result = FALSE;
                                                sprintf(badPacketReason,"invalid length: numBytesInPacket=%d,packetLength=%d",numBytesInPacket,packetLength);
                                        }
                                }
                        } else if (packetLength > numBytesInPacket){
                                result = FALSE;
                                sprintf(badPacketReason,"packetLength(%d) > numBytesInPacket(%d)",packetLength,numBytesInPacket);
                        }
                        if (result){
                                /* packet header is ok - check the event headers */
                                pEvent = (UInt32* )((UInt32)pPacketBuffer + sizeof(ti_uia_runtime_UIAPacket_Hdr));
                                packetLength -= sizeof(ti_uia_runtime_UIAPacket_Hdr);
                                while ((result == TRUE) && (packetLength > 0)){
                                        eventWord1 = *pEvent;
                                        if (ti_uia_runtime_EventHdr_getHdrType(eventWord1) == ti_uia_runtime_EventHdr_HdrType_EventWithTimestamp){
                                                eventLength = ti_uia_runtime_EventHdr_getLength(eventWord1);
                                                if (eventLength > (WRITE8_SIZE_IN_WORDS*BYTES_IN_WORD)){
                                                        result = FALSE;
                                                        sprintf(badPacketReason,"eventLength(%d) > WRITE8_SIZE_IN_BYTES(%d)",eventLength,WRITE8_SIZE_IN_WORDS*BYTES_IN_WORD);
                                                } else {
                                                        packetLength -= eventLength;
                                                }
                                        } else {
                                                if (ti_uia_runtime_EventHdr_getHdrType(eventWord1) == ti_uia_runtime_EventHdr_HdrType_EventWithSnapshotIdAndTimestamp){
                                                        eventLength = ti_uia_runtime_EventHdr_getLength(eventWord1);

                                                        if (eventLength > LoggerStreamer_maxEventSize){
                                                                result = FALSE;
                                                                sprintf(badPacketReason,"eventLength(%d) > LoggerStreamer_maxEventSize(%d).  eventWord1=0x%x",eventLength,LoggerStreamer_maxEventSize,eventWord1);
                                                        } else {
                                                                packetLength -= eventLength;
                                                        }
                                                } else {
                                                        result = FALSE;
                                                        sprintf(badPacketReason,"bad event hdr type(%d)",ti_uia_runtime_EventHdr_getHdrType(eventWord1));
                                                }
                                        }
                                        if (result){
                                                pEvent = (UInt32*)((UInt32)pEvent + eventLength);
                                        }
                                }
                        }
                }
        }
        if (result != NULL){
                printf("Bad packet detected: %s\n",badPacketReason);
                numBadPacketsFound++;
        }
        if ((numPacketsChecked & 0xfff)==0){
                printf("Core %d: Num packets checked = %d. Num bad = %d\n",senderAdrs,numPacketsChecked, numBadPacketsFound);
        }

        if (result){
                return(NULL);
        }

        /* set a breakpoint here to catch failures */
        return (badPacketReason);
}
#endif


/*
 *  @(#) ti.uia.sysbios; 1, 0, 0, 0,1; 7-13-2012 11:12:38; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

