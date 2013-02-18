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
 *  ======== EventHdr__epilogue.h ========
 */
#define EventHdr_HDRTYPE_BIT_SHIFT 27
#define EventHdr_HDRTYPE_MASK 0xF8000000
#define EventHdr_HDRTYPE_SHIFTED_MASK 0x1F

#define EventHdr_LENGTH_BIT_SHIFT 16
#define EventHdr_LENGTH_MASK 0x07FF0000
#define EventHdr_LENGTH_SHIFTED_MASK 0x07FF

#define EventHdr_SEQCOUNT_BIT_SHIFT 0
#define EventHdr_SEQCOUNT_MASK 0xFFFFL
#define EventHdr_SEQCOUNT_SHIFTED_MASK 0xFFFF

/*
 *  ======== EventHdr_getHdrType ========
 *  gets the message header type from the message header
 */
#define ti_uia_runtime_EventHdr_getHdrType(eventWord1)                        \
    ((EventHdr_HdrType)(((UInt32)eventWord1 >> EventHdr_HDRTYPE_BIT_SHIFT) &  \
     EventHdr_HDRTYPE_SHIFTED_MASK))

/*
 *  ======== EventHdr_setHdrType ========
 *  sets the message header type in the message header
 */
#define ti_uia_runtime_EventHdr_setHdrType(eventWord1, hdrType)               \
    (eventWord1 =  (eventWord1 & ~EventHdr_HDRTYPE_MASK) |                    \
                   ((hdrType & EventHdr_HDRTYPE_SHIFTED_MASK) <<              \
                    EventHdr_HDRTYPE_BIT_SHIFT))
/*
 *  ======== EventHdr_getLength ========
 *  gets the event length (in bytes) from the first word of the event header
 */

#define ti_uia_runtime_EventHdr_getLength(eventWord1)                         \
    ((UInt32)((eventWord1 & EventHdr_LENGTH_MASK) >> EventHdr_LENGTH_BIT_SHIFT))

/*
 *  ======== EventHdr_setLength ========
 *  sets the event length (in bytes) in the first word of the event header
 */
#define ti_uia_runtime_EventHdr_setLength(eventWord1, lengthInBytes)          \
    (eventWord1 =  (eventWord1 & ~EventHdr_LENGTH_MASK) |                     \
                   ((lengthInBytes & EventHdr_LENGTH_SHIFTED_MASK) <<         \
                    EventHdr_LENGTH_BIT_SHIFT))

/*
 *  ======== EventHdr_getSeqCount ========
 *  gets the sequence count from the message header
 */
#define ti_uia_runtime_EventHdr_getSeqCount(eventWord1)                       \
    ((UInt16)((eventWord1 & EventHdr_SEQCOUNT_MASK) >>                        \
     EventHdr_SEQCOUNT_BIT_SHIFT))

/*
 *  ======== EventHdr_setSeqCount ========
 *  sets the sequence count in the message header
 */
#define ti_uia_runtime_EventHdr_setSeqCount(eventWord1, seqCount)             \
    (eventWord1 =  (eventWord1 & ~EventHdr_SEQCOUNT_MASK) |                   \
                   ((seqCount & EventHdr_SEQCOUNT_SHIFTED_MASK) <<            \
                    EventHdr_SEQCOUNT_BIT_SHIFT))
/*
 *  ======== EventHdr_genEventHdrWord1 ========
 *  generates the first word to use in an Event header
 */
#define ti_uia_runtime_EventHdr_genEventHdrWord1(numBytesInEventMsg,          \
                                                 seqCount, eventHdrType)      \
    ((((UInt32)eventHdrType & EventHdr_HDRTYPE_SHIFTED_MASK) <<               \
      EventHdr_HDRTYPE_BIT_SHIFT) |                                           \
     (((UInt32)numBytesInEventMsg & EventHdr_LENGTH_SHIFTED_MASK) <<          \
      EventHdr_LENGTH_BIT_SHIFT) |                                            \
     (((UInt32)seqCount & EventHdr_SEQCOUNT_SHIFTED_MASK) <<                  \
      EventHdr_SEQCOUNT_BIT_SHIFT))

/*
 */
/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:23; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

