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
 *  ======== LoggerStopMode.c ========
 */
#include <xdc/std.h>
#include "LoggerStopMode_defines.h"
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/Log.h>
#include <ti/uia/runtime/LoggerTypes.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/IFilterLogger.h>
#include <ti/uia/runtime/QueueDescriptor.h>
#include <ti/uia/runtime/EventHdr.h>
#include <ti/uia/runtime/IUIATransfer.h>

#ifdef xdc_target__isaCompatible_64P
#include <c6x.h>
#endif

#include <stdlib.h>
#include <string.h>

#include "package/internal/LoggerStopMode.xdc.h"

#define TIMESTAMP                   LoggerStopMode_isTimestampEnabled
#define BITS8_IN_EVENTHDR           8
#define BITS8_IN_TIMESTAMP          ((TIMESTAMP & 1) << 3)
#define BITS8_IN_WRITEMEMORY        24
#define BITS8_IN_NUM_ARGS_0         0
#define BITS8_IN_NUM_ARGS_1         4
#define BITS8_IN_NUM_ARGS_2         8
#define BITS8_IN_NUM_ARGS_4         16
#define BITS8_IN_NUM_ARGS_8         32

#define BITS8_TO_BITS32(bits8)      ((bits8) / 4)
#define BITS32_TO_BITS8(bits32)     ((bits32) * 4)
#define MAU_TO_BITS32(mau)          ((mau) / sizeof(Bits32))
#define MAU_TO_BITS32_ROUND_UP(mau) (MAU_TO_BITS32((mau) + sizeof(Bits32) - 1))
#define BITS32_TO_MAU(bits32)       ((bits32) * sizeof(Bits32))
#define BITS8_TO_MAU(bits8)         (BITS32_TO_MAU(BITS8_TO_BITS32(bits8)))
#define MAU_TO_BITS8(mau)           (BITS32_TO_BITS8(MAU_TO_BITS32(mau)))

/*
 *  ======== fillInTimestamp =========
 */
static inline Bits32 *fillInTimestamp(Bits32 *writePtr)
{
#ifndef xdc_target__isaCompatible_64P
    Types_Timestamp64 tstamp;

    Timestamp_get64(&tstamp);
    *(writePtr++) = tstamp.lo;
    *(writePtr++) = tstamp.hi;
#else
    *(writePtr++) = TSCL;
    *(writePtr++) = TSCH;

#endif
    return (writePtr);
}

/*
 *  ======== fillInEventHdrSnapshot =========
 */
static inline Bits32 *fillInEventHdrSnapshot(Bits32 *writePtr,
                                        SizeT numBits8ToWrite, Bits32 serial)
{
    if (TIMESTAMP) {
        *(writePtr++) = EventHdr_genEventHdrWord1(numBits8ToWrite, serial,
                           EventHdr_HdrType_EventWithSnapshotIdAndTimestamp);
        writePtr = fillInTimestamp(writePtr);
    }
    else {
        *(writePtr++) = EventHdr_genEventHdrWord1(numBits8ToWrite, serial,
                           EventHdr_HdrType_EventWithSnapshotId);
    }
    return (writePtr);
}

/*
 *  ======== fillInEventHdr =========
 */
static inline Bits32 *fillInEventHdr(Bits32 *writePtr, SizeT numBits8ToWrite,
                                        Bits32 serial)
{
    if (TIMESTAMP) {
        *(writePtr++) = EventHdr_genEventHdrWord1(numBits8ToWrite, serial,
                           EventHdr_HdrType_EventWithTimestamp);
        writePtr = fillInTimestamp(writePtr);
    }
    else {
        *(writePtr++) = EventHdr_genEventHdrWord1(numBits8ToWrite, serial,
                           EventHdr_HdrType_Event);
    }
    return (writePtr);
}

/*
 *  ======== LoggerStopMode_getFreeSize =========
 */
SizeT LoggerStopMode_getFreeSize(LoggerStopMode_Object *obj)
{
    /*
     *  The readPtr can be modified externally (e.g. by the Debug Server)
     *  so store a snapshot of its value locally to prevent race conditions.
     *  The numBytesFree will only get larger, not smaller due to host
     *  reading the data
     */
    register Bits32 reader = (Bits32)obj->hdr.readPtr;
    register Bits32 writer = (Bits32)obj->hdr.writePtr;

    if (reader > writer) {
        return (reader - writer);
    }

    return (obj->queueSizeInMAUs - (writer - reader));
}

/*
 * ======== CircBuf_getUnreadSize =========
 * compares the RdPtr and WrPtr for the buffer and returns num. Bits32 unread
 *
 * TODO: convert from MAUs to Bytes for ISAs that do not support byte
 * addressability
 */
SizeT LoggerStopMode_getUnreadSize(LoggerStopMode_Object *obj)
{
    /*
     *  The writePtr can be modified by the callers of Log_xxx,
     *  so store a snapshot of its value locally to prevent race conditions.
     */
    register Bits32 writer = (Bits32)obj->hdr.writePtr;
    register Bits32 reader = (Bits32)obj->hdr.readPtr;

    if (reader <= writer){
        return (writer - reader);
    }

    return (obj->queueSizeInMAUs - (reader - writer));
}

/*
 *  ======== LoggerStopMode_updateWritePtrByValue ========
 *  updates the current write pointer, wrapping if necessary
 */
static inline Void LoggerStopMode_updateWritePtrByValue(
                       LoggerStopMode_Object *obj, Ptr newWrPtr)
{
    Bits32 temp;

    /* Did not write in the padded area. Just set the new writePtr and return */
    if (newWrPtr < obj->endOfBufferAdrsPlus1) {
        obj->hdr.writePtr = newWrPtr;
        return;
    }

    /*
     *  Determine how much is in the padded region. Move that data
     *  back to the start.
     */
    temp = (Bits32)newWrPtr - (Bits32)obj->endOfBufferAdrsPlus1;
    if (temp > 0) {
        memcpy(obj->queueStartAdrs,obj->endOfBufferAdrsPlus1, temp);
    }

    /*
     *  NOTE: Must only update obj->writePtr after it is safe for the reader to
     *  read the data for the message from the buffer and update the readPtr.
     *  Must do this atomically - must not allow compiler to use
     *  obj->hdr.writePtr as scratchpad.
     */
    obj->hdr.writePtr = (Bits32 *)((Bits32)obj->queueStartAdrs + temp);
    return;
}

/*
 *  ======== LoggerStopMode_multicoreAdjust ========
 */
Void LoggerStopMode_multicoreAdjust(LoggerStopMode_Object *obj)
{
#ifdef xdc_target__isaCompatible_64P
    extern cregister volatile UInt DNUM;
    Bits32 base = (Bits32)obj->queueStartAdrs;

    obj->bufferArray = (Char *)(base + DNUM *
           (obj->queueSizeInMAUs  + BITS32_TO_MAU(obj->maxEventSizeInBits32)));
    LoggerStopMode_reset(obj);
#endif
}

/*
 *  ======== LoggerStopMode_Module_startup ========
 */
Int LoggerStopMode_Module_startup(Int phase)
{
    Int i;
    LoggerStopMode_Object *obj;

    /*
     *  Loop over all "permanent" instances and add them onto the
     *  QueueDescriptor list.
     */
    for (i = 0; i < LoggerStopMode_Object_count(); i++) {
        obj = LoggerStopMode_Object_get(NULL, i);
        QueueDescriptor_addToList(&(obj->hdr));
        if (obj->numCores > 1) {
            LoggerStopMode_multicoreAdjust(obj);
        }
    }

#ifdef xdc_target__isaCompatible_64P
    /* Start the timestamp */
    TSCL = 0;
#endif
    return (Startup_DONE);

}

/*
 *  ======== Instance_init =========
 *  TODO not completely tested.
 */
Int LoggerStopMode_Instance_init(LoggerStopMode_Object *obj,
                             const LoggerStopMode_Params *prms, Error_Block *eb)
{
    int numMAUsToAllocate;

    if (prms->transferBufSize > 0){

        obj->flush = prms->exitFlush;
        obj->bufHeap = NULL;

        /* register this Logger as the owner of the queue descriptor */
        obj->queueSizeInMAUs = prms->transferBufSize;

        obj->numCores = prms->numCores;

        // maxEventSizeInBits32 determines the length of the wraparound copy
        // area that follows the circular buffer
        obj->maxEventSizeInBits32 = MAU_TO_BITS32(prms->maxEventSize);
        numMAUsToAllocate = prms->transferBufSize + prms->maxEventSize;

        obj->bufferArray = Memory_alloc(prms->bufHeap, numMAUsToAllocate, 0, eb);

        if (obj->bufferArray != NULL){
            obj->bufHeap = prms->bufHeap;
            LoggerStopMode_reset(obj);
            obj->enabled = TRUE;
        }
    }
    obj->hdr.numDroppedCtrAdrs = (Ptr)&obj->droppedEvents;

    return (0); /* status passed to finalize on error */
}

/*
 *  ======== LoggerStopMode_Instance_finalize ========
 *  TODO not completely tested.
 */
Void LoggerStopMode_Instance_finalize(LoggerStopMode_Object *obj, Int status)
{
    obj->hdr.queueSizeInMAUs = 0;
    obj->hdr.queueStartAdrs = NULL;
    obj->queueStartAdrs = NULL;
    obj->hdr.ownerModuleId = 0;
    obj->hdr.numDroppedCtrAdrs = NULL;
    obj->hdr.queueType = QueueDescriptor_QueueType_NONE;
    QueueDescriptor_removeFromList(&obj->hdr);
    Memory_free(obj->bufHeap,obj->bufferArray,obj->queueSizeInMAUs);
}

/*
 *  ======== LoggerStopMode_enable ========
 */
Bool LoggerStopMode_enable(LoggerStopMode_Object *obj)
{
    Bool prev;
    IArg key;

    key = Gate_enterSystem();

    prev = obj->enabled;
    obj->enabled = TRUE;


    if (LoggerStopMode_overflowLogger != NULL) {
        xdc_runtime_ILogger_enable(LoggerStopMode_overflowLogger);
    }

    Gate_leaveSystem(key);

    return (prev);
}

/*
 *  ======== LoggerStopMode_disable ========
 */
Bool LoggerStopMode_disable(LoggerStopMode_Object *obj)
{
    Bool prev;
    IArg key;

    key = Gate_enterSystem();

    prev = obj->enabled;
    obj->enabled = FALSE;

    if (LoggerStopMode_overflowLogger != NULL) {
        xdc_runtime_ILogger_disable(LoggerStopMode_overflowLogger);
    }

    Gate_leaveSystem(key);

    return (prev);
}

/*
 *  ======== LoggerStopMode_setFilterLevel ========
 *  Sets the filter level for the given diags level.
 *
 *  LoggerStopMode maintains a separate filter level for every diags category.
 *  This is accomplished by maintaining three masks, one for each of the levels
 *  1 - 3, wich store the diags categories which are currently at that level.
 *  There is no mask for level4; if the diags category is not found in levels
 *  1-3, it is  assumed that the filtering level is level4.
 *
 *  This API is an instance function per the IFilterLogger interface, but
 *  LoggerStopMode only maintains module-wide filter levels.
 *
 *  TODO - Should this be conditional on the 'filterByLevel' config?
 */
Void LoggerStopMode_setFilterLevel(LoggerStopMode_Object *obj,
                                  xdc_runtime_Diags_Mask mask,
                                  xdc_runtime_Diags_EventLevel filterLevel)
{
    /*
     * First, remove the bits in 'mask' from all of the current 'level' masks.
     * Use level = (~(mask & level) & level) to remove 'mask' bits from all
     * 'level's.
     *    1. AND mask and level to get set of bits that appear in both
     *    2. Take the inverse of this set and AND it with 'level' to disable
     *       any bits which appear in 'mask'.
     */
    LoggerStopMode_module->level1 = ~(LoggerStopMode_module->level1 & mask) &
                               LoggerStopMode_module->level1;
    LoggerStopMode_module->level2 = ~(LoggerStopMode_module->level2 & mask) &
                               LoggerStopMode_module->level2;
    LoggerStopMode_module->level3 = ~(LoggerStopMode_module->level3 & mask) &
                               LoggerStopMode_module->level3;

    /* Enable the bits specified in 'mask' in the appropriate level. */
    switch (filterLevel) {
        case Diags_LEVEL1:
            LoggerStopMode_module->level1 |= mask;
            break;
        case Diags_LEVEL2:
            LoggerStopMode_module->level2 |= mask;
            break;
        case Diags_LEVEL3:
            LoggerStopMode_module->level3 |= mask;
            break;
        case Diags_LEVEL4:
            break;
        default: {
            /* Raise an error that a bad filter level was received. */
            Error_Block eb;
            Error_init(&eb);
            Error_raise(&eb, LoggerStopMode_E_badLevel, filterLevel, 0);
            break;
        }
    }
}

/*
 *  ======== LoggerStopMode_getFilterLevel ========
 *  Returns the mask of diags categories which are set to the specified filter
 *  level.
 *
 *  This API is an instance function per the IFilterLogger interface, but
 *  LoggerStopMode only maintains module-wide filter levels.
 */
Diags_Mask LoggerStopMode_getFilterLevel(LoggerStopMode_Object *obj,
                                    xdc_runtime_Diags_EventLevel level)
{
    /* Return the mask of diags categories associated with 'level'. */
    switch (level) {
        case Diags_LEVEL1:
            return (LoggerStopMode_module->level1);
        case Diags_LEVEL2:
            return (LoggerStopMode_module->level2);
        case Diags_LEVEL3:
            return (LoggerStopMode_module->level3);
        case Diags_LEVEL4:
            /*
             * Return the inverse of all the bits set in levels 1 - 3,
             * and only return those bits which belong to the set of
             * logging categories (excludes asserts and the two level bits).
             */
            return (~(LoggerStopMode_module->level1 |
                      LoggerStopMode_module->level2 |
                      LoggerStopMode_module->level3) &
                     xdc_runtime_Diags_ALL_LOGGING);
        default: {
            /* Raise an error to report the bad filter level. */
            Error_Block eb;
            Error_init(&eb);
            Error_raise(&eb, LoggerStopMode_E_badLevel, level, 0);
            return (0);
        }
    }
}

/*
 *  ======== LoggerStopMode_filterOutEvent ========
 *  Returns TRUE if the event should be filtered out.
 *  TODO - Might be more clearly written as 'passesFilter'?
 */
Bool LoggerStopMode_filterOutEvent(xdc_runtime_Diags_Mask mask)
{
    /*
     * If filtering for the event's diags category is currently
     * set to level1...
     */
    if (LoggerStopMode_module->level1 & mask) {
        /* If the event is lower than level1, filter it out. */
        return(Diags_compareLevels(Diags_getLevel(mask), Diags_LEVEL1));
    }
    /*
     * If filtering for the event's diags category is currently
     * set to level2...
     */
    else if (LoggerStopMode_module->level2 & mask) {
        /* If the event is lower than level2, filter it out. */
        return(Diags_compareLevels(Diags_getLevel(mask), Diags_LEVEL2));
    }
    /*
     * If filtering for the event's diags category is currently
     * set to level3...
     */
    else if (LoggerStopMode_module->level3 & mask) {
        /* If the event is lower than level3, filter it out. */
        return(xdc_runtime_Diags_compareLevels(xdc_runtime_Diags_getLevel(mask),
                                               xdc_runtime_Diags_LEVEL3));
    }
    /*
     * Otherwise, the filter level must be level4, which means that events of
     * all levels should be logged.
     */
    else {
        return (FALSE);
    }
}

/*
 * ======== getNumDropped =========
 * returns the number of dropped events for this logger instance
 * TODO getStats instead? Add to IUIATransfer?
 */
Int LoggerStopMode_getNumDropped(LoggerStopMode_Object *obj)
{
    return (obj->droppedEvents);
}

/*
 *  ======== LoggerStopMode_getInstanceId ========
 */
UInt16 LoggerStopMode_getInstanceId(LoggerStopMode_Object *obj)
{
    return ((UInt16)obj->hdr.instanceId);
}

/*
 *  ======== LoggerStopMode_getPriority ========
 */
IUIATransfer_Priority LoggerStopMode_getPriority(LoggerStopMode_Object *obj)
{
    return ((IUIATransfer_Priority)obj->hdr.priority);
}

/*
 *  ======== LoggerStopMode_setPriority ========
 */
Void LoggerStopMode_setPriority(LoggerStopMode_Object *obj, IUIATransfer_Priority priority)
{
    obj->hdr.priority = (UInt)priority;
}
/*
 *  ======== LoggerStopMode_getMaxLength ========
 */
SizeT LoggerStopMode_getMaxLength(LoggerStopMode_Object *obj)
{
    return (obj->queueSizeInMAUs);
}

/*
 *  ======== LoggerStopMode_reset ========
 */
Void LoggerStopMode_reset(LoggerStopMode_Object *obj)
{
    IArg key;

    key = Gate_enterSystem();
    obj->queueStartAdrs       = obj->bufferArray;
    obj->endOfBufferAdrsPlus1 = (Ptr)((Bits32)obj->queueStartAdrs +
                                                        obj->queueSizeInMAUs);
    obj->serial        = 1;
    obj->droppedEvents = 0;

#ifndef ISSTOPMODELOGGER
    QueueDescriptor_initHeader(&(obj->hdr), obj->queueStartAdrs,
         obj->queueSizeInMAUs, obj->hdr.ownerModuleId, obj->hdr.instanceId,
         obj->hdr.priority, QueueDescriptor_QueueType_TOHOST_EVENT_CIRCULAR_BUFFER,
         &obj->droppedEvents);
#else
    QueueDescriptor_initHeader(&(obj->hdr), obj->queueStartAdrs,
         obj->queueSizeInMAUs, obj->hdr.ownerModuleId, obj->hdr.instanceId,
         obj->hdr.priority, QueueDescriptor_QueueType_TOHOST_EVENT_OVERFLOW_BUFFER,
         &obj->droppedEvents);
#endif
    Gate_leaveSystem(key);
}

/*
 * ======== LoggerStopMode_getTransferType ========
 *  Returns whether the logger events can be sent over lossy transports or
 *  requires reliable transport
 // TODO need to see if this makes sense...
 */
IUIATransfer_TransferType LoggerStopMode_getTransferType(
    LoggerStopMode_Object *obj)
{
    return(obj->transferType);
}

/*
 *  ======== LoggerStopMode_setModuleIdToRouteToStatusLogger ========
 *  Specifies a module ID to route events to the statusLogger for.
 *  Set mid to -1 for 'none', since a mid of 0 is used for Log_print events.
 */
Void LoggerStopMode_setModuleIdToRouteToStatusLogger(Types_ModuleId mid)
{
    LoggerStopMode_module->moduleIdToRouteToStatusLogger = mid;
}
/*
 * ======== LoggerStopMode_isEmpty ========
 * Returns true if the transfer buffer has no unread data
 */
Bool LoggerStopMode_isEmpty(LoggerStopMode_Object *obj)
{
    Bool result;

    if (obj->hdr.readPtr == obj->hdr.writePtr) {
        result = TRUE;
    }
    else {
        result = FALSE;
    }

    return (result);
}

/*
 *  ======== LoggerStopMode_readBlockOfMemory ========
 *  Reads a specified number of MAU into a caller-provided block of memory,
 *  wrapping around if necessary
 */
Bool LoggerStopMode_readBlockOfMemory(LoggerStopMode_Object *obj, Ptr pMemBlock,
        SizeT sizeToRead)
{
    Bool result = TRUE;
    Ptr myRdPtr = obj->hdr.readPtr;
    SizeT numMAUToEndOfBuffer;
    SizeT numMAUUnread = LoggerStopMode_getUnreadSize(obj);

    if (numMAUUnread >= sizeToRead){

        numMAUToEndOfBuffer =  (SizeT)((Bits32)obj->endOfBufferAdrsPlus1 -
                (Bits32)obj->hdr.readPtr);

        /*
         *  Determine whether there is
         *   -  no wrap so only one memcpy is needed.
         *   -  wrap so two memcpys are needed.
         */
        if (sizeToRead > numMAUToEndOfBuffer) {
            /* Copy from readPtr to the end */
            memcpy(pMemBlock, obj->hdr.readPtr, numMAUToEndOfBuffer);

            /* Copy from start now */
            memcpy((Ptr)((Bits32)pMemBlock + numMAUToEndOfBuffer),
                   obj->queueStartAdrs, sizeToRead - numMAUToEndOfBuffer);

            myRdPtr = (Ptr)((Bits32)obj->queueStartAdrs + (sizeToRead -
                    numMAUToEndOfBuffer));
        } else {
            memcpy(pMemBlock, obj->hdr.readPtr, sizeToRead);

            /* Handle the wrap case for setting the readPtr */
            if (sizeToRead == numMAUToEndOfBuffer) {
                myRdPtr = obj->queueStartAdrs;
            }
            else {
                myRdPtr = (Ptr)((Bits32)myRdPtr + sizeToRead);
            }
        }
        obj->hdr.readPtr = myRdPtr;
    } else {
        result = FALSE;
    }
    return (result);
}

/*
 *  ======== LoggerStopMode_writeBlockOfMemory ========
 *  Writes a block of memory into the buffer following some already written but
 *  not committed data values
 */
Bool LoggerStopMode_writeBlockOfMemory(LoggerStopMode_Object *obj, Ptr newWrPtr, Ptr pMemBlock, SizeT size)
{
    Bool result = TRUE;
    SizeT numMAUWrappedAround;
    SizeT numMAUWritten;

    /* How many MAU have already been written? */
    numMAUWritten = (SizeT)((Bits32)newWrPtr - (Bits32)obj->hdr.writePtr);

    if (LoggerStopMode_getFreeSize(obj) > (size + numMAUWritten)) {
        /*
         * copy any data that has extended past the end of the
         * buffer and spilled over into the reserved area
         * back to the start of the buffer to make the buffer circular
         */
        if (newWrPtr >= obj->endOfBufferAdrsPlus1) {
            numMAUWrappedAround =  (SizeT)((Bits32)newWrPtr -
                    (Bits32)obj->endOfBufferAdrsPlus1);

            memcpy(obj->queueStartAdrs, obj->endOfBufferAdrsPlus1,
                    numMAUWrappedAround);
            newWrPtr = (Ptr)((Bits32)obj->queueStartAdrs + numMAUWrappedAround);
        }

        /* circularize the buffer if necessary */
        if (((Bits32)newWrPtr + size) >= (Bits32)obj->endOfBufferAdrsPlus1) {
            numMAUWrappedAround = (SizeT)(((Bits32)newWrPtr + size) -
                    (Bits32)obj->endOfBufferAdrsPlus1);
            memcpy((Ptr)newWrPtr, pMemBlock, (size - numMAUWrappedAround));
            memcpy((Ptr)obj->queueStartAdrs, obj->endOfBufferAdrsPlus1,
                    numMAUWrappedAround);
            newWrPtr = (Ptr)((Bits32)obj->queueStartAdrs + numMAUWrappedAround);
        } else {
            memcpy(newWrPtr, pMemBlock, size);
            newWrPtr = (Ptr)((Bits32)newWrPtr + size);
        }

        /*
         * NOTE: Must only update obj->writePtr after it is safe for the reader
         * to read the data for the message from the buffer and update the
         * readPtr.
         */
        obj->hdr.writePtr = newWrPtr;
    } else {
        result = FALSE;
    }

    return(result);
}


/*
 * ======== LoggerStopMode_getContents =========
 * Fills buffer that is passed in with unread data, up to size MAU's in length.
 */
Bool LoggerStopMode_getContents(LoggerStopMode_Object *obj, Ptr hdrBuf,
        SizeT maxSize, SizeT *cpSize)
{
    Bool result;
    Bool moreRecords = FALSE;
    Int numEventsChecked = 0;
    SizeT numMAUInEvent = 0;
    SizeT numMAULeft = LoggerStopMode_getUnreadSize(obj);
    SizeT numMAUToRead = 0;
    Ptr tempRdPtr = (Ptr)obj->hdr.readPtr;
    Bits32 endOfBufferAdrs = (Bits32)obj->endOfBufferAdrsPlus1;

#ifdef ISSTOPMODELOGGER
    /* In order to prevent race conditions from occurring between code that is logging
     * events and code that is uploading events, only allow events to be uploaded
     * if the stop-mode logger has been disabled. */
    if (!obj->enabled){
#endif
        if (numMAULeft > maxSize) {

            /* find out the number of bytes in an integer number of
             * events <= maxSize */
            while (numMAUToRead <= maxSize) {
                /*
                 *  - Get the size of the event record
                 *  - Update the running count
                 *  - adjust the temp read pointer
                 */
                numMAUInEvent = BITS8_TO_MAU(EventHdr_getLength(*(Int32 *)tempRdPtr));
                numMAUToRead += numMAUInEvent;
                tempRdPtr = (Ptr)((Bits32)tempRdPtr + numMAUInEvent);

                /* check for wrap condition */
                if ((Bits32)tempRdPtr >= endOfBufferAdrs){
                    tempRdPtr = (Ptr)((Bits32)obj->queueStartAdrs +
                                      ((Bits32)tempRdPtr - endOfBufferAdrs));
                }

                /*
                 * Bulletproofing to handle corrupted events. Break out of loop
                 * if number of events checked is too high and reset logger.
                 */
                numEventsChecked++;
                if (numEventsChecked > numMAULeft){
                    numMAUToRead = 0;
                    LoggerStopMode_reset(obj);
                    QueueDescriptor_addToList(&obj->hdr);
                    break;
                }
            }

            /* Remove the last one since it did not fit */
            numMAUToRead -= numMAUInEvent;
            moreRecords = TRUE;
        } else {
            numMAUToRead = numMAULeft;
        }

        if (numMAUToRead > 0){

            /* read data into the buffer */
            result = LoggerStopMode_readBlockOfMemory(obj, hdrBuf, numMAUToRead);
            if (result == FALSE) {
                // TODO assert? or corruptFlag?
            }
            *cpSize = numMAUToRead;
        } else {
            *cpSize = 0;
        }
#ifdef ISSTOPMODELOGGER
    }
#endif
    return(moreRecords);
}

/*
 *  ======== write0 =========
 *  Log an event with 0 parameters and the calling address
 */
Void LoggerStopMode_write0(LoggerStopMode_Object *obj, xdc_runtime_Log_Event evt,
        Types_ModuleId mid)
{
#ifndef ISSTOPMODELOGGER
    IArg key;
    Bits32 *myWrPtr;
    SizeT numBits8ToWrite;

    /* Do nothing if the instance is disabled. */
    if (obj->enabled) {
        /*
         * If event level filtering is enabled, and the event isn't a high
         * enough level, drop the record and return.
         */
        if (LoggerStopMode_filterByLevel){
            if (LoggerStopMode_filterOutEvent(Log_getMask(evt))) {
               return;
            }
            /*
             *  If all of the following are true:
             *   - A logger has been specified to route status events to
             *   - This is a status event OR is an event logged by a
             *       module that has been configured to have its events
             *       passed through to the status logger
             *   - This logger is NOT the status logger
             * Pass the event to the status logger also.
             *
             * Otherwise, continue to log the event.
             */
            if ((LoggerStopMode_statusLogger != NULL) &&
                ((Log_getMask(evt) & Diags_STATUS) ||
                 (LoggerStopMode_module->moduleIdToRouteToStatusLogger == mid)) &&
                ((Ptr)LoggerStopMode_statusLogger != (Ptr)obj)) {
                IFilterLogger_write0(LoggerStopMode_statusLogger, evt, mid);
            }
        }

        /* Figure out big the write will be */
        numBits8ToWrite = BITS8_IN_EVENTHDR + BITS8_IN_NUM_ARGS_0 +
                                                            BITS8_IN_TIMESTAMP;

        key = Gate_enterSystem();
        if (MAU_TO_BITS8(LoggerStopMode_getFreeSize(obj)) <= numBits8ToWrite) {
            /*
             * Update serial number even if the buffer is full or disabled.
             * We do this because a reader (decoder) of the buffer needs to
             * know if events have been missed, and the buffer might become
             * un-FULL at some later time.
             */
            obj->serial++;
            Gate_leaveSystem(key);

            if (LoggerStopMode_overflowLogger != NULL) {
                xdc_runtime_ILogger_write4(LoggerStopMode_overflowLogger,evt,mid,
                        0,0,0,0);
            } else {
                /*
                 * Update serial number even if the buffer is full or disabled.
                 * We do this because a reader (decoder) of the buffer needs to
                 * know if events have been missed, and the buffer might become
                 * un-FULL at some later time.
                 */
                obj->droppedEvents++;
            }
        }
        else {
            myWrPtr = fillInEventHdr((Bits32 *)obj->hdr.writePtr, numBits8ToWrite,
                    obj->serial++);
            *(myWrPtr++) = ((evt) & 0xffff0000) | mid;
            LoggerStopMode_updateWritePtrByValue(obj, myWrPtr);

#ifdef UIAPROBEPOINTSENABLED
asm(" .global UIAPROBE_WRITE0");
asm("UIAPROBE_WRITE0:");
#endif
        }
        Gate_leaveSystem(key);
    }
#else
    LoggerStopMode_write4(obj,evt,mid,0,0,0,0);
#endif
}
/*
 *  ======== write1 =========
 *  Log an event with 1 parameter and the calling address
 */
Void LoggerStopMode_write1(LoggerStopMode_Object *obj, xdc_runtime_Log_Event evt,
        Types_ModuleId mid, IArg a1)
{
#ifndef ISSTOPMODELOGGER
    IArg key;
    Bits32 *myWrPtr;
    Int numBits8ToWrite;

    /* Do nothing if the instance is disabled. */
    if (obj->enabled) {
        /*
         * If event level filtering is enabled, and the event isn't a high
         * enough level, drop the record and return.
         */
        if (LoggerStopMode_filterByLevel){
            if (LoggerStopMode_filterOutEvent(Log_getMask(evt))) {
               return;
            }
            /*
             *  If all of the following are true:
             *   - A logger has been specified to route status events to
             *   - This is a status event
             *   - This logger is NOT the status logger
             * Pass the event to the status logger also.
             *
             * Otherwise, continue to log the event.
             */
            if ((LoggerStopMode_statusLogger != NULL) &&
                ((Log_getMask(evt) & Diags_STATUS) ||
                 (LoggerStopMode_module->moduleIdToRouteToStatusLogger == mid)) &&
                ((Ptr)LoggerStopMode_statusLogger != (Ptr)obj)) {
                IFilterLogger_write1(LoggerStopMode_statusLogger, evt, mid, a1);
            }
        }

        /* Figure out big the write will be */
        numBits8ToWrite = BITS8_IN_EVENTHDR + BITS8_IN_NUM_ARGS_1 +
                                                            BITS8_IN_TIMESTAMP;

        key = Gate_enterSystem();
        if (MAU_TO_BITS8(LoggerStopMode_getFreeSize(obj)) <= numBits8ToWrite){
            /*
             * Update serial number even if the buffer is full or disabled.
             * We do this because a reader (decoder) of the buffer needs to
             * know if events have been missed, and the buffer might become
             * un-FULL at some later time.
             */
            obj->serial++;
            Gate_leaveSystem(key);

            if (LoggerStopMode_overflowLogger != NULL) {
                xdc_runtime_ILogger_write4(LoggerStopMode_overflowLogger,evt,mid,a1,0,0,0);
            } else {

                obj->droppedEvents++;
            }
        } else {
            myWrPtr = fillInEventHdr((Bits32 *)obj->hdr.writePtr, numBits8ToWrite,
                    obj->serial++);
            *(myWrPtr++) = ((evt) & 0xffff0000) | mid;
            *(myWrPtr++) = a1;
            LoggerStopMode_updateWritePtrByValue(obj, myWrPtr);

#ifdef UIAPROBEPOINTSENABLED
asm(" .global UIAPROBE_WRITE1");
asm("UIAPROBE_WRITE1:");
#endif
            Gate_leaveSystem(key);
        }
    }
#else
    LoggerStopMode_write4(obj,evt,mid,a1,0,0,0);
#endif
}
/*
 *  ======== write2 =========
 *  Log an event with 1 parameter and the calling address
 */
Void LoggerStopMode_write2(LoggerStopMode_Object *obj, xdc_runtime_Log_Event evt,
        Types_ModuleId mid, IArg a1, IArg a2)
{
#ifndef ISSTOPMODELOGGER
    IArg key;
    Bits32 *myWrPtr;
    Int numBits8ToWrite;

    /* Do nothing if the instance is disabled. */
    if (obj->enabled) {
        /*
         * If event level filtering is enabled, and the event isn't a high enough
         * level, drop the record and return.
         */
        if (LoggerStopMode_filterByLevel){
            if (LoggerStopMode_filterOutEvent(Log_getMask(evt))) {
               return;
            }

            /*
             *  If all of the following are true:
             *   - A logger has been specified to route status events to
             *   - This is a status event
             *   - This logger is NOT the status logger
             * Pass the event to the status logger also.
             *
             * Otherwise, continue to log the event.
             */
            if ((LoggerStopMode_statusLogger != NULL) &&
                ((Log_getMask(evt) & Diags_STATUS) ||
                 (LoggerStopMode_module->moduleIdToRouteToStatusLogger == mid)) &&
                ((Ptr)LoggerStopMode_statusLogger != (Ptr)obj)) {
                IFilterLogger_write2(LoggerStopMode_statusLogger, evt, mid,
                        a1, a2);
            }
        }

        /* Figure out big the write will be */
        numBits8ToWrite = BITS8_IN_EVENTHDR + BITS8_IN_NUM_ARGS_2 +
                                                            BITS8_IN_TIMESTAMP;

        key = Gate_enterSystem();
        if (MAU_TO_BITS8(LoggerStopMode_getFreeSize(obj)) <= numBits8ToWrite){
            /*
             * Update serial number even if the buffer is full or disabled.
             * We do this because a reader (decoder) of the buffer needs to
             * know if events have been missed, and the buffer might become
             * un-FULL at some later time.
             */
            obj->serial++;
            Gate_leaveSystem(key);

            if (LoggerStopMode_overflowLogger != NULL) {
                xdc_runtime_ILogger_write4(LoggerStopMode_overflowLogger,evt,mid,
                        a1,a2,0,0);
            } else {

                obj->droppedEvents++;
            }
        }
        else {
            myWrPtr = fillInEventHdr((Bits32 *)obj->hdr.writePtr, numBits8ToWrite, obj->serial++);
            *(myWrPtr++) = ((evt) & 0xffff0000) | mid;
            *(myWrPtr++) = a1;
            *(myWrPtr++) = a2;
            LoggerStopMode_updateWritePtrByValue(obj, myWrPtr);
#ifdef UIAPROBEPOINTSENABLED
asm(" .global UIAPROBE_WRITE2");
asm("UIAPROBE_WRITE2:");
#endif
            Gate_leaveSystem(key);
        }
    }
#else
    LoggerStopMode_write4(obj,evt,mid,a1,a2,0,0);
#endif
}

/*
 *  ======== write4 =========
 *  Log an event with 4 parameters and the calling address
 */
Void LoggerStopMode_write4(LoggerStopMode_Object *obj, xdc_runtime_Log_Event evt,
        Types_ModuleId mid, IArg a1, IArg a2, IArg a3, IArg a4)
{
    IArg key;
    Bits32 *myWrPtr;
    Int numBits8ToWrite;
#ifdef ISSTOPMODELOGGER
    UInt newRdAdrs;
#endif

    /* Do nothing if the instance is disabled. */
    if (obj->enabled) {
        /*
         * If event level filtering is enabled, and the event isn't a high enough
         * level, drop the record and return.
         */
        if (LoggerStopMode_filterByLevel){
            if (LoggerStopMode_filterOutEvent(Log_getMask(evt))) {
               return;
            }
            /*
             *  If all of the following are true:
             *   - A logger has been specified to route status events to
             *   - This is a status event
             *   - This logger is NOT the status logger
             * Pass the event to the status logger also.
             *
             * Otherwise, continue to log the event.
             */
            if ((LoggerStopMode_statusLogger != NULL) &&
                ((Log_getMask(evt) & Diags_STATUS) ||
                 (LoggerStopMode_module->moduleIdToRouteToStatusLogger == mid)) &&
                ((Ptr)LoggerStopMode_statusLogger != (Ptr)obj)) {
                IFilterLogger_write4(LoggerStopMode_statusLogger, evt, mid,
                        a1, a2, a3, a4);
            }
        }

        /* Figure out big the write will be */
        numBits8ToWrite = BITS8_IN_EVENTHDR + BITS8_IN_NUM_ARGS_4 +
                                                            BITS8_IN_TIMESTAMP;

        key = Gate_enterSystem();
        if (MAU_TO_BITS8(LoggerStopMode_getFreeSize(obj)) <= numBits8ToWrite) {
#ifndef ISSTOPMODELOGGER

            /*
             * Update serial number even if the buffer is full or disabled.
             * We do this because a reader (decoder) of the buffer needs to
             * know if events have been missed, and the buffer might become
             * un-FULL at some later time.
             */
            obj->serial++;
            Gate_leaveSystem(key);

            if (LoggerStopMode_overflowLogger != NULL) {
                xdc_runtime_ILogger_write4(LoggerStopMode_overflowLogger,evt,mid,
                        a1,a2,a3,a4);
            } else {

                obj->droppedEvents++;
            }
        } else {
#else
            /* discardNextUnreadEvent updates the circular buffer read pointer -
             * do the read pointer update in a critical section to avoid
             * conflict over the read pointer with the transfer agent.*/

                newRdAdrs = (Bits32)obj->hdr.readPtr + EventHdr_getLength(*(Bits32 *)obj->hdr.readPtr);

                if (newRdAdrs >= (Bits32)obj->endOfBufferAdrsPlus1) {
                    newRdAdrs = (Bits32)obj->queueStartAdrs + (newRdAdrs - (Bits32)obj->endOfBufferAdrsPlus1);
                }
                obj->droppedEvents++;
                obj->hdr.readPtr = (Bits32 *)newRdAdrs;

        }
        {
#endif

            myWrPtr = fillInEventHdr((Bits32 *)obj->hdr.writePtr, numBits8ToWrite,
                    obj->serial++);
            *(myWrPtr++) = ((evt) & 0xffff0000) | mid;
            *(myWrPtr++) = a1;
            *(myWrPtr++) = a2;
            *(myWrPtr++) = a3;
            *(myWrPtr++) = a4;
            LoggerStopMode_updateWritePtrByValue(obj, myWrPtr);
#ifdef UIAPROBEPOINTSENABLED
asm(" .global UIAPROBE_WRITE4");
asm("UIAPROBE_WRITE4:");
#endif
            Gate_leaveSystem(key);
        }
    }
}

/*
 *  ======== write8 =========
 *  Log an event with 8 parameters and the calling address
 */
Void LoggerStopMode_write8(LoggerStopMode_Object *obj, xdc_runtime_Log_Event evt,
        Types_ModuleId mid, IArg a1, IArg a2, IArg a3, IArg a4, IArg a5,
        IArg a6, IArg a7, IArg a8)
{
    IArg key;
    Bits32 *myWrPtr;
    Int numBits8ToWrite;
#ifdef ISSTOPMODELOGGER
    UInt newRdAdrs;
    UInt numBits8Free;
    Int numBits8Discarded;
#endif

    /* Do nothing if the instance is disabled. */
    if (obj->enabled) {
        /*
         * If event level filtering is enabled, and the event isn't a high enough
         * level, drop the record and return.
         */
        if (LoggerStopMode_filterByLevel) {
            if (LoggerStopMode_filterOutEvent(Log_getMask(evt))) {
               return;
            }
            /*
             *  If all of the following are true:
             *   - A logger has been specified to route status events to
             *   - This is a status event
             *   - This logger is NOT the status logger
             * Pass the event to the status logger also.
             *
             * Otherwise, continue to log the event.
             */
            if ((LoggerStopMode_statusLogger != NULL) &&
                ((Log_getMask(evt) & Diags_STATUS) ||
                 (LoggerStopMode_module->moduleIdToRouteToStatusLogger == mid)) &&
                ((Ptr)LoggerStopMode_statusLogger != (Ptr)obj)) {
                IFilterLogger_write8(LoggerStopMode_statusLogger, evt, mid,
                        a1, a2, a3, a4, a5, a6, a7, a8);
            }
        }

        /* Figure out big the write will be */
        numBits8ToWrite = BITS8_IN_EVENTHDR + BITS8_IN_NUM_ARGS_8 +
                                                            BITS8_IN_TIMESTAMP;

        key = Gate_enterSystem();
#ifndef ISSTOPMODELOGGER
        if (MAU_TO_BITS8(LoggerStopMode_getFreeSize(obj)) <= numBits8ToWrite) {

            /*
             * Update serial number even if the buffer is full or disabled.
             * We do this because a reader (decoder) of the buffer needs to
             * know if events have been missed, and the buffer might become
             * un-FULL at some later time.
             */
            obj->serial++;
            Gate_leaveSystem(key);

            if (LoggerStopMode_overflowLogger != NULL) {
                xdc_runtime_ILogger_write8(LoggerStopMode_overflowLogger,evt,mid,
                        a1,a2,a3,a4,a5,a6,a7,a8);
            } else {

                obj->droppedEvents++;

            }
        } else {

#else
        numBits8Free = MAU_TO_BITS8(LoggerStopMode_getFreeSize(obj));
        if (numBits8Free < numBits8ToWrite) {
            /* discardNextUnreadItem updates the circular buffer read pointer -
             * do the read pointer update in a critical section to avoid
             * conflict over the read pointer with the transfer agent.
             * This should take at most 1 call operations since we
             * either write 4 or 8 argument events. */

            numBits8Discarded = EventHdr_getLength(*(Bits32 *)obj->hdr.readPtr);

            newRdAdrs = (Bits32)obj->hdr.readPtr + (BITS8_TO_MAU(numBits8Discarded));

            if (newRdAdrs >= (Bits32)obj->endOfBufferAdrsPlus1) {
                newRdAdrs = (Bits32)obj->queueStartAdrs + (newRdAdrs - (Bits32)obj->endOfBufferAdrsPlus1);
            }
            obj->droppedEvents++;
            numBits8Free += numBits8Discarded;
            if (numBits8Free < numBits8ToWrite) {
                newRdAdrs = (Bits32)obj->hdr.readPtr + EventHdr_getLength(*(Bits32 *)obj->hdr.readPtr);

                if (newRdAdrs >= (Bits32)obj->endOfBufferAdrsPlus1) {
                    newRdAdrs = (Bits32)obj->queueStartAdrs + (newRdAdrs - (Bits32)obj->endOfBufferAdrsPlus1);
                }
                obj->droppedEvents++;
            }
            obj->hdr.readPtr = (Bits32 *)newRdAdrs;

        }
        {
#endif

            myWrPtr = fillInEventHdr((Bits32 *)obj->hdr.writePtr, numBits8ToWrite,
                    obj->serial++);
            *(myWrPtr++) = ((evt) & 0xffff0000) | mid;
            *(myWrPtr++) = a1;
            *(myWrPtr++) = a2;
            *(myWrPtr++) = a3;
            *(myWrPtr++) = a4;
            *(myWrPtr++) = a5;
            *(myWrPtr++) = a6;
            *(myWrPtr++) = a7;
            *(myWrPtr++) = a8;
            LoggerStopMode_updateWritePtrByValue(obj, myWrPtr);
#ifdef UIAPROBEPOINTSENABLED
asm(" .global UIAPROBE_WRITE8");
asm("UIAPROBE_WRITE8:");
#endif
            Gate_leaveSystem(key);
        }
    }
}

/*  ======== writeMemoryRange =========
 *  logs a range of consecutive memory values.
 *
 *  Breaks up large blocks into a series of smaller blocks in order to limit the
 *  maximum amount of time that interrupts are disabled.
 */
Void LoggerStopMode_writeMemoryRange(LoggerStopMode_Object *obj, Log_Event evt,
                                    Types_ModuleId mid, UInt32 snapshotId,
                                    IArg fileName, IArg lineNum, IArg fmt,
                                    IArg startAdrs, UInt32 lengthInMAUs)
{
    Int i;
    IArg key;
    Int32 eventSizeBits32;
    Int32 dataSizeBits32;
    Ptr pAdrs = (Ptr)startAdrs;
    Bits32 *myWrPtr;
    Int32 headerSizeBits32;
    Int32 lenAdjustedBits32;
    Int numRecords;
#ifdef ISSTOPMODELOGGER
    Bits32 newRdAdrs;
    UInt numBits32Free;
    Int numBits32Discarded;
#endif
    /* Do nothing if the instance is disabled. */
    if (obj->enabled) {
        /*
         * If event level filtering is enabled, and the event isn't a high enough
         * level, drop the record and return.
         */
        if (LoggerStopMode_filterByLevel) {
            if (LoggerStopMode_filterOutEvent(Log_getMask(evt))) {
               return;
            }
        }

        headerSizeBits32 = BITS8_TO_BITS32(BITS8_IN_EVENTHDR +
                                    BITS8_IN_WRITEMEMORY + BITS8_IN_TIMESTAMP);
        lenAdjustedBits32 = MAU_TO_BITS32_ROUND_UP(lengthInMAUs);
        numRecords = (lenAdjustedBits32 / (obj->maxEventSizeInBits32 - headerSizeBits32)) + 1;

        for (i = 0; i < numRecords; i++) {

            if ((headerSizeBits32 + lenAdjustedBits32) > obj->maxEventSizeInBits32) {
                dataSizeBits32 = obj->maxEventSizeInBits32 - headerSizeBits32;
                lenAdjustedBits32 -= dataSizeBits32;
            }
            else {
                dataSizeBits32 = lenAdjustedBits32;
            }
            eventSizeBits32 = dataSizeBits32 + headerSizeBits32;

            key = Gate_enterSystem();
#ifndef ISSTOPMODELOGGER
            if (MAU_TO_BITS32(LoggerStopMode_getFreeSize(obj)) <= eventSizeBits32) {

                /*
                 * Update serial number even if the buffer is full or disabled.
                 * We do this because a reader (decoder) of the buffer needs to
                 * know if events have been missed, and the buffer might become
                 * un-FULL at some later time.
                 */
                obj->serial++;
                Gate_leaveSystem(key);

                //TODO: log the first 8 bytes of the event to the overflow buffer
                obj->droppedEvents++;
            }
            else {

#else
        numBits32Free = MAU_TO_BITS32(LoggerStopMode_getFreeSize(obj));

        while (numBits32Free < eventSizeBits32) {
            /* discardNextUnreadItem updates the circular buffer read pointer -
             * do the read pointer update in a critical section to avoid
             * conflict over the read pointer with the transfer agent.
             * This should take at most 1 call operations since we
             * either write 4 or 8 argument events. */

            numBits32Discarded = BITS8_TO_BITS32(EventHdr_getLength(*(Bits32 *)obj->hdr.readPtr));

            newRdAdrs = (Bits32)obj->hdr.readPtr + BITS32_TO_MAU(numBits32Discarded);

            if (newRdAdrs >= (Bits32)obj->endOfBufferAdrsPlus1) {
                newRdAdrs = (Bits32)obj->queueStartAdrs + (newRdAdrs - (Bits32)obj->endOfBufferAdrsPlus1);
            }
            obj->droppedEvents++;
            numBits32Free += numBits32Discarded;
            obj->hdr.readPtr = (Bits32 *)newRdAdrs;
        }
        {
#endif

                myWrPtr = fillInEventHdrSnapshot((Bits32 *)obj->hdr.writePtr, BITS32_TO_BITS8(eventSizeBits32),
                                                 obj->serial++);
                *(myWrPtr++) = ((evt) & 0xffff0000) | mid;
                *(myWrPtr++) = fileName;
                *(myWrPtr++) = lineNum;
                *(myWrPtr++) = snapshotId;
                *(myWrPtr++) = (Bits32)pAdrs;
                *(myWrPtr++) = (((BITS32_TO_MAU(dataSizeBits32) & 0x0FFFF)<<16) |
                                (lengthInMAUs & 0x0FFFF));
                *(myWrPtr++) = fmt;

                LoggerStopMode_writeBlockOfMemory(obj, myWrPtr, (Bits32 *)pAdrs,
                        BITS32_TO_MAU(dataSizeBits32));
#ifdef UIAPROBEPOINTSENABLED
asm(" .global UIAPROBE_WRITEMEMORYRANGE");
asm("UIAPROBE_WRITEMEMORYRANGE:");
#endif
                pAdrs = (Ptr)((Bits32)pAdrs + BITS32_TO_MAU(dataSizeBits32));
                Gate_leaveSystem(key);
            }
        }
    }
}

/*
 *  ======== LoggerStopMode_flushAll ========
 */
Void LoggerStopMode_flushAll()
{
    Int i;
    LoggerStopMode_Object *obj;

    /* flush static instances */
    for (i = 0; i < LoggerStopMode_Object_count(); i++) {
         obj = LoggerStopMode_Object_get(NULL, i);

        if (obj->flush) {
            LoggerStopMode_flush(obj);
        }
    }

    /* flush dynamic instances */
    for (obj = LoggerStopMode_Object_first(); obj != NULL;
         obj = LoggerStopMode_Object_next(obj)) {

        if (obj->flush) {
            LoggerStopMode_flush(obj);
        }
    }
}

/*
 *  ======== LoggerStopMode_flushAllInternal ========
 */
Void LoggerStopMode_flushAllInternal(Int stat)
{
     LoggerStopMode_flushAll();
}

/*
 *  ======== LoggerStopMode_postIncrementPtr ========
 *  Inefficient way to handle this, but simply.
 */
Bits32 *LoggerStopMode_postIncrementPtr(LoggerStopMode_Object *obj, Bits32 *myRdPtr)
{
    myRdPtr++;

    if (myRdPtr == obj->endOfBufferAdrsPlus1) {
        myRdPtr = obj->queueStartAdrs;
    }

    return (myRdPtr);
}

/*
 *  ======== LoggerStopMode_flush ========
 */
Void LoggerStopMode_flush(LoggerStopMode_Object *obj)
{
    Int i;
    IArg key;
    Ptr myWrPtr;
    Bits32 *myRdPtr;
    SizeT numBits8InEvent;
    SizeT totalBits8 = 0;
    Int offset;
    Log_EventRec evtRec;

    if (TIMESTAMP) {
        offset = 2;
    }
    else {
        offset = 0;
    }

    // TODO Gate needed?
    key = Gate_enterSystem();

    myWrPtr = obj->hdr.writePtr;
    myRdPtr = obj->hdr.readPtr;

    while (myRdPtr != myWrPtr) {

        /* Initialize the evtRec */
        memset(&evtRec, 0, sizeof(Log_EventRec));

        /* Determine the length of the event */
        numBits8InEvent = EventHdr_getLength(*myRdPtr);

        /* Grab the serial number */
        evtRec.serial = EventHdr_getSeqCount(*myRdPtr);
        myRdPtr = LoggerStopMode_postIncrementPtr(obj, myRdPtr);

        /* If timestamps are enabled, get them */
        if (TIMESTAMP) {
            evtRec.tstamp.lo = *myRdPtr;
            myRdPtr = LoggerStopMode_postIncrementPtr(obj, myRdPtr);
            evtRec.tstamp.hi = *myRdPtr;
            myRdPtr = LoggerStopMode_postIncrementPtr(obj, myRdPtr);
        }

        /* Get the event id */
        evtRec.evt = *myRdPtr;
        myRdPtr = LoggerStopMode_postIncrementPtr(obj, myRdPtr);

        /* Grab the args */
        for (i = 0; i < BITS8_TO_BITS32(numBits8InEvent) - (2 + offset) && i < 8; i++) {
            evtRec.arg[i] = *myRdPtr;
            myRdPtr = LoggerStopMode_postIncrementPtr(obj, myRdPtr);
        }

        Log_doPrint(&evtRec);

        totalBits8 += numBits8InEvent;
        if (BITS8_TO_MAU(totalBits8) > obj->queueSizeInMAUs) {
                /* Somethings wrong...*/
                //TODO reset?
                break;
        }
    }
    // TODO update readPtr?
    Gate_leaveSystem(key);
}

/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:26; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

