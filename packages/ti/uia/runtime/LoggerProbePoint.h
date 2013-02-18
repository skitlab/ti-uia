/*
 *  Copyright 2012 by Texas Instruments Incorporated.
 *
 */

/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y23
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     FUNCTION SELECTORS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_uia_runtime_LoggerProbePoint__include
#define ti_uia_runtime_LoggerProbePoint__include

#ifndef __nested__
#define __nested__
#define ti_uia_runtime_LoggerProbePoint__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_uia_runtime_LoggerProbePoint___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/uia/runtime/package/package.defs.h>

#include <ti/uia/runtime/QueueDescriptor.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/IFilterLogger.h>
#include <ti/uia/runtime/IUIATransfer.h>
#include <xdc/runtime/Log.h>
#include <ti/uia/runtime/ILoggerSnapshot.h>
#include <xdc/runtime/ILogger.h>
#include <xdc/runtime/ITimestampClient.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Diags.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* TransferType */
typedef ti_uia_runtime_IUIATransfer_TransferType ti_uia_runtime_LoggerProbePoint_TransferType;

/* Priority */
typedef ti_uia_runtime_IUIATransfer_Priority ti_uia_runtime_LoggerProbePoint_Priority;

/* TransferType_RELIABLE */
#define ti_uia_runtime_LoggerProbePoint_TransferType_RELIABLE ti_uia_runtime_IUIATransfer_TransferType_RELIABLE

/* TransferType_LOSSY */
#define ti_uia_runtime_LoggerProbePoint_TransferType_LOSSY ti_uia_runtime_IUIATransfer_TransferType_LOSSY

/* Priority_LOW */
#define ti_uia_runtime_LoggerProbePoint_Priority_LOW ti_uia_runtime_IUIATransfer_Priority_LOW

/* Priority_STANDARD */
#define ti_uia_runtime_LoggerProbePoint_Priority_STANDARD ti_uia_runtime_IUIATransfer_Priority_STANDARD

/* Priority_HIGH */
#define ti_uia_runtime_LoggerProbePoint_Priority_HIGH ti_uia_runtime_IUIATransfer_Priority_HIGH

/* Priority_SYNC */
#define ti_uia_runtime_LoggerProbePoint_Priority_SYNC ti_uia_runtime_IUIATransfer_Priority_SYNC


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Instance_State */
typedef xdc_Char __T1_ti_uia_runtime_LoggerProbePoint_Instance_State__bufferArray;
typedef xdc_Char *__ARRAY1_ti_uia_runtime_LoggerProbePoint_Instance_State__bufferArray;
typedef __ARRAY1_ti_uia_runtime_LoggerProbePoint_Instance_State__bufferArray __TA_ti_uia_runtime_LoggerProbePoint_Instance_State__bufferArray;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_uia_runtime_LoggerProbePoint_Module__diagsEnabled;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__diagsEnabled ti_uia_runtime_LoggerProbePoint_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_uia_runtime_LoggerProbePoint_Module__diagsIncluded;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__diagsIncluded ti_uia_runtime_LoggerProbePoint_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_uia_runtime_LoggerProbePoint_Module__diagsMask;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__diagsMask ti_uia_runtime_LoggerProbePoint_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_uia_runtime_LoggerProbePoint_Module__gateObj;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__gateObj ti_uia_runtime_LoggerProbePoint_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_uia_runtime_LoggerProbePoint_Module__gatePrms;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__gatePrms ti_uia_runtime_LoggerProbePoint_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_uia_runtime_LoggerProbePoint_Module__id;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__id ti_uia_runtime_LoggerProbePoint_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_uia_runtime_LoggerProbePoint_Module__loggerDefined;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__loggerDefined ti_uia_runtime_LoggerProbePoint_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_uia_runtime_LoggerProbePoint_Module__loggerObj;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__loggerObj ti_uia_runtime_LoggerProbePoint_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn0;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn0 ti_uia_runtime_LoggerProbePoint_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn1;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn1 ti_uia_runtime_LoggerProbePoint_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn2;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn2 ti_uia_runtime_LoggerProbePoint_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn4;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn4 ti_uia_runtime_LoggerProbePoint_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn8;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__loggerFxn8 ti_uia_runtime_LoggerProbePoint_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_uia_runtime_LoggerProbePoint_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Module__startupDoneFxn ti_uia_runtime_LoggerProbePoint_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_uia_runtime_LoggerProbePoint_Object__count;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Object__count ti_uia_runtime_LoggerProbePoint_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_uia_runtime_LoggerProbePoint_Object__heap;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Object__heap ti_uia_runtime_LoggerProbePoint_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_uia_runtime_LoggerProbePoint_Object__sizeof;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Object__sizeof ti_uia_runtime_LoggerProbePoint_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_uia_runtime_LoggerProbePoint_Object__table;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_Object__table ti_uia_runtime_LoggerProbePoint_Object__table__C;

/* filterByLevel */
#ifdef ti_uia_runtime_LoggerProbePoint_filterByLevel__D
#define ti_uia_runtime_LoggerProbePoint_filterByLevel (ti_uia_runtime_LoggerProbePoint_filterByLevel__D)
#else
#define ti_uia_runtime_LoggerProbePoint_filterByLevel (ti_uia_runtime_LoggerProbePoint_filterByLevel__C)
typedef xdc_Bool CT__ti_uia_runtime_LoggerProbePoint_filterByLevel;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_filterByLevel ti_uia_runtime_LoggerProbePoint_filterByLevel__C;
#endif

/* E_badLevel */
#define ti_uia_runtime_LoggerProbePoint_E_badLevel (ti_uia_runtime_LoggerProbePoint_E_badLevel__C)
typedef xdc_runtime_Error_Id CT__ti_uia_runtime_LoggerProbePoint_E_badLevel;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_E_badLevel ti_uia_runtime_LoggerProbePoint_E_badLevel__C;

/* isTimestampEnabled */
#ifdef ti_uia_runtime_LoggerProbePoint_isTimestampEnabled__D
#define ti_uia_runtime_LoggerProbePoint_isTimestampEnabled (ti_uia_runtime_LoggerProbePoint_isTimestampEnabled__D)
#else
#define ti_uia_runtime_LoggerProbePoint_isTimestampEnabled (ti_uia_runtime_LoggerProbePoint_isTimestampEnabled__C)
typedef xdc_Bool CT__ti_uia_runtime_LoggerProbePoint_isTimestampEnabled;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_isTimestampEnabled ti_uia_runtime_LoggerProbePoint_isTimestampEnabled__C;
#endif

/* enableFlush */
#ifdef ti_uia_runtime_LoggerProbePoint_enableFlush__D
#define ti_uia_runtime_LoggerProbePoint_enableFlush (ti_uia_runtime_LoggerProbePoint_enableFlush__D)
#else
#define ti_uia_runtime_LoggerProbePoint_enableFlush (ti_uia_runtime_LoggerProbePoint_enableFlush__C)
typedef xdc_Bool CT__ti_uia_runtime_LoggerProbePoint_enableFlush;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_enableFlush ti_uia_runtime_LoggerProbePoint_enableFlush__C;
#endif

/* statusLogger */
#define ti_uia_runtime_LoggerProbePoint_statusLogger (ti_uia_runtime_LoggerProbePoint_statusLogger__C)
typedef xdc_runtime_IFilterLogger_Handle CT__ti_uia_runtime_LoggerProbePoint_statusLogger;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_statusLogger ti_uia_runtime_LoggerProbePoint_statusLogger__C;

/* overflowLogger */
#define ti_uia_runtime_LoggerProbePoint_overflowLogger (ti_uia_runtime_LoggerProbePoint_overflowLogger__C)
typedef xdc_runtime_ILogger_Handle CT__ti_uia_runtime_LoggerProbePoint_overflowLogger;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_overflowLogger ti_uia_runtime_LoggerProbePoint_overflowLogger__C;

/* level1Mask */
#ifdef ti_uia_runtime_LoggerProbePoint_level1Mask__D
#define ti_uia_runtime_LoggerProbePoint_level1Mask (ti_uia_runtime_LoggerProbePoint_level1Mask__D)
#else
#define ti_uia_runtime_LoggerProbePoint_level1Mask (ti_uia_runtime_LoggerProbePoint_level1Mask__C)
typedef xdc_runtime_Diags_Mask CT__ti_uia_runtime_LoggerProbePoint_level1Mask;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_level1Mask ti_uia_runtime_LoggerProbePoint_level1Mask__C;
#endif

/* level2Mask */
#ifdef ti_uia_runtime_LoggerProbePoint_level2Mask__D
#define ti_uia_runtime_LoggerProbePoint_level2Mask (ti_uia_runtime_LoggerProbePoint_level2Mask__D)
#else
#define ti_uia_runtime_LoggerProbePoint_level2Mask (ti_uia_runtime_LoggerProbePoint_level2Mask__C)
typedef xdc_runtime_Diags_Mask CT__ti_uia_runtime_LoggerProbePoint_level2Mask;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_level2Mask ti_uia_runtime_LoggerProbePoint_level2Mask__C;
#endif

/* level3Mask */
#ifdef ti_uia_runtime_LoggerProbePoint_level3Mask__D
#define ti_uia_runtime_LoggerProbePoint_level3Mask (ti_uia_runtime_LoggerProbePoint_level3Mask__D)
#else
#define ti_uia_runtime_LoggerProbePoint_level3Mask (ti_uia_runtime_LoggerProbePoint_level3Mask__C)
typedef xdc_runtime_Diags_Mask CT__ti_uia_runtime_LoggerProbePoint_level3Mask;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_level3Mask ti_uia_runtime_LoggerProbePoint_level3Mask__C;
#endif

/* level4Mask */
#ifdef ti_uia_runtime_LoggerProbePoint_level4Mask__D
#define ti_uia_runtime_LoggerProbePoint_level4Mask (ti_uia_runtime_LoggerProbePoint_level4Mask__D)
#else
#define ti_uia_runtime_LoggerProbePoint_level4Mask (ti_uia_runtime_LoggerProbePoint_level4Mask__C)
typedef xdc_runtime_Diags_Mask CT__ti_uia_runtime_LoggerProbePoint_level4Mask;
__extern __FAR__ const CT__ti_uia_runtime_LoggerProbePoint_level4Mask ti_uia_runtime_LoggerProbePoint_level4Mask__C;
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_uia_runtime_LoggerProbePoint_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
    ti_uia_runtime_IUIATransfer_TransferType transferType;
    ti_uia_runtime_IUIATransfer_Priority priority;
    xdc_SizeT transferBufSize;
    xdc_SizeT maxEventSize;
    xdc_Bool exitFlush;
    xdc_runtime_IHeap_Handle bufHeap;
    xdc_Int numCores;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_uia_runtime_LoggerProbePoint_Struct {
    const ti_uia_runtime_LoggerProbePoint_Fxns__* __fxns;
    ti_uia_runtime_QueueDescriptor_Header __f0;
    xdc_runtime_IHeap_Handle __f1;
    xdc_SizeT __f2;
    xdc_Bits16 __f3;
    ti_uia_runtime_IUIATransfer_TransferType __f4;
    xdc_Bool __f5;
    xdc_Bool __f6;
    xdc_Int __f7;
    xdc_Ptr __f8;
    xdc_SizeT __f9;
    xdc_Ptr __f10;
    __TA_ti_uia_runtime_LoggerProbePoint_Instance_State__bufferArray __f11;
    xdc_Int __f12;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_uia_runtime_LoggerProbePoint_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Bool (*enable)(ti_uia_runtime_LoggerProbePoint_Handle);
    xdc_Bool (*disable)(ti_uia_runtime_LoggerProbePoint_Handle);
    xdc_Void (*write0)(ti_uia_runtime_LoggerProbePoint_Handle, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId);
    xdc_Void (*write1)(ti_uia_runtime_LoggerProbePoint_Handle, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_IArg);
    xdc_Void (*write2)(ti_uia_runtime_LoggerProbePoint_Handle, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_IArg, xdc_IArg);
    xdc_Void (*write4)(ti_uia_runtime_LoggerProbePoint_Handle, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);
    xdc_Void (*write8)(ti_uia_runtime_LoggerProbePoint_Handle, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);
    xdc_Void (*setFilterLevel)(ti_uia_runtime_LoggerProbePoint_Handle, xdc_runtime_Diags_Mask, xdc_runtime_Diags_EventLevel);
    xdc_runtime_Diags_Mask (*getFilterLevel)(ti_uia_runtime_LoggerProbePoint_Handle, xdc_runtime_Diags_EventLevel);
    ti_uia_runtime_IUIATransfer_TransferType (*getTransferType)(ti_uia_runtime_LoggerProbePoint_Handle);
    xdc_Bool (*getContents)(ti_uia_runtime_LoggerProbePoint_Handle, xdc_Ptr, xdc_SizeT, xdc_SizeT*);
    xdc_Bool (*isEmpty)(ti_uia_runtime_LoggerProbePoint_Handle);
    xdc_SizeT (*getMaxLength)(ti_uia_runtime_LoggerProbePoint_Handle);
    xdc_UInt16 (*getInstanceId)(ti_uia_runtime_LoggerProbePoint_Handle);
    ti_uia_runtime_IUIATransfer_Priority (*getPriority)(ti_uia_runtime_LoggerProbePoint_Handle);
    xdc_Void (*setPriority)(ti_uia_runtime_LoggerProbePoint_Handle, ti_uia_runtime_IUIATransfer_Priority);
    xdc_Void (*reset)(ti_uia_runtime_LoggerProbePoint_Handle);
    xdc_Void (*writeMemoryRange)(ti_uia_runtime_LoggerProbePoint_Handle, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_UInt32, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_UInt32);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Module__FXNS__C */
__extern const ti_uia_runtime_LoggerProbePoint_Fxns__ ti_uia_runtime_LoggerProbePoint_Module__FXNS__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_uia_runtime_LoggerProbePoint_Module_startup ti_uia_runtime_LoggerProbePoint_Module_startup__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Module_startup__E, "ti_uia_runtime_LoggerProbePoint_Module_startup")
__extern xdc_Int ti_uia_runtime_LoggerProbePoint_Module_startup__E( xdc_Int state );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Module_startup__F, "ti_uia_runtime_LoggerProbePoint_Module_startup")
__extern xdc_Int ti_uia_runtime_LoggerProbePoint_Module_startup__F( xdc_Int state );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Module_startup__R, "ti_uia_runtime_LoggerProbePoint_Module_startup")
__extern xdc_Int ti_uia_runtime_LoggerProbePoint_Module_startup__R( xdc_Int state );

/* Instance_init__F */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Instance_init__F, "ti_uia_runtime_LoggerProbePoint_Instance_init")
__extern int ti_uia_runtime_LoggerProbePoint_Instance_init__F( ti_uia_runtime_LoggerProbePoint_Object*, const ti_uia_runtime_LoggerProbePoint_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__F */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Instance_finalize__F, "ti_uia_runtime_LoggerProbePoint_Instance_finalize")
__extern void ti_uia_runtime_LoggerProbePoint_Instance_finalize__F( ti_uia_runtime_LoggerProbePoint_Object* , int );

/* Instance_init__R */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Instance_init__R, "ti_uia_runtime_LoggerProbePoint_Instance_init")
__extern int ti_uia_runtime_LoggerProbePoint_Instance_init__R( ti_uia_runtime_LoggerProbePoint_Object*, const ti_uia_runtime_LoggerProbePoint_Params*, xdc_runtime_Error_Block* );

/* Instance_finalize__R */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Instance_finalize__R, "ti_uia_runtime_LoggerProbePoint_Instance_finalize")
__extern void ti_uia_runtime_LoggerProbePoint_Instance_finalize__R( ti_uia_runtime_LoggerProbePoint_Object* , int );

/* Handle__label__S */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Handle__label__S, "ti_uia_runtime_LoggerProbePoint_Handle__label")
__extern xdc_runtime_Types_Label* ti_uia_runtime_LoggerProbePoint_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Module__startupDone__S, "ti_uia_runtime_LoggerProbePoint_Module__startupDone")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Object__create__S, "ti_uia_runtime_LoggerProbePoint_Object__create")
__extern xdc_Ptr ti_uia_runtime_LoggerProbePoint_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Object__delete__S, "ti_uia_runtime_LoggerProbePoint_Object__delete")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Object__destruct__S, "ti_uia_runtime_LoggerProbePoint_Object__destruct")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Object__get__S, "ti_uia_runtime_LoggerProbePoint_Object__get")
__extern xdc_Ptr ti_uia_runtime_LoggerProbePoint_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Object__first__S, "ti_uia_runtime_LoggerProbePoint_Object__first")
__extern xdc_Ptr ti_uia_runtime_LoggerProbePoint_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Object__next__S, "ti_uia_runtime_LoggerProbePoint_Object__next")
__extern xdc_Ptr ti_uia_runtime_LoggerProbePoint_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_Params__init__S, "ti_uia_runtime_LoggerProbePoint_Params__init")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* getTransferType__E */
#define ti_uia_runtime_LoggerProbePoint_getTransferType ti_uia_runtime_LoggerProbePoint_getTransferType__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getTransferType__E, "ti_uia_runtime_LoggerProbePoint_getTransferType")
__extern ti_uia_runtime_IUIATransfer_TransferType ti_uia_runtime_LoggerProbePoint_getTransferType__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getTransferType__F, "ti_uia_runtime_LoggerProbePoint_getTransferType")
__extern ti_uia_runtime_IUIATransfer_TransferType ti_uia_runtime_LoggerProbePoint_getTransferType__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern ti_uia_runtime_IUIATransfer_TransferType ti_uia_runtime_LoggerProbePoint_getTransferType__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* getContents__E */
#define ti_uia_runtime_LoggerProbePoint_getContents ti_uia_runtime_LoggerProbePoint_getContents__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getContents__E, "ti_uia_runtime_LoggerProbePoint_getContents")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_getContents__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_Ptr hdrBuf, xdc_SizeT size, xdc_SizeT* cpSize );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getContents__F, "ti_uia_runtime_LoggerProbePoint_getContents")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_getContents__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, xdc_Ptr hdrBuf, xdc_SizeT size, xdc_SizeT* cpSize );
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_getContents__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_Ptr hdrBuf, xdc_SizeT size, xdc_SizeT* cpSize );

/* isEmpty__E */
#define ti_uia_runtime_LoggerProbePoint_isEmpty ti_uia_runtime_LoggerProbePoint_isEmpty__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_isEmpty__E, "ti_uia_runtime_LoggerProbePoint_isEmpty")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_isEmpty__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_isEmpty__F, "ti_uia_runtime_LoggerProbePoint_isEmpty")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_isEmpty__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_isEmpty__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* getMaxLength__E */
#define ti_uia_runtime_LoggerProbePoint_getMaxLength ti_uia_runtime_LoggerProbePoint_getMaxLength__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getMaxLength__E, "ti_uia_runtime_LoggerProbePoint_getMaxLength")
__extern xdc_SizeT ti_uia_runtime_LoggerProbePoint_getMaxLength__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getMaxLength__F, "ti_uia_runtime_LoggerProbePoint_getMaxLength")
__extern xdc_SizeT ti_uia_runtime_LoggerProbePoint_getMaxLength__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_SizeT ti_uia_runtime_LoggerProbePoint_getMaxLength__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* getInstanceId__E */
#define ti_uia_runtime_LoggerProbePoint_getInstanceId ti_uia_runtime_LoggerProbePoint_getInstanceId__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getInstanceId__E, "ti_uia_runtime_LoggerProbePoint_getInstanceId")
__extern xdc_UInt16 ti_uia_runtime_LoggerProbePoint_getInstanceId__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getInstanceId__F, "ti_uia_runtime_LoggerProbePoint_getInstanceId")
__extern xdc_UInt16 ti_uia_runtime_LoggerProbePoint_getInstanceId__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_UInt16 ti_uia_runtime_LoggerProbePoint_getInstanceId__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* getPriority__E */
#define ti_uia_runtime_LoggerProbePoint_getPriority ti_uia_runtime_LoggerProbePoint_getPriority__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getPriority__E, "ti_uia_runtime_LoggerProbePoint_getPriority")
__extern ti_uia_runtime_IUIATransfer_Priority ti_uia_runtime_LoggerProbePoint_getPriority__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getPriority__F, "ti_uia_runtime_LoggerProbePoint_getPriority")
__extern ti_uia_runtime_IUIATransfer_Priority ti_uia_runtime_LoggerProbePoint_getPriority__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern ti_uia_runtime_IUIATransfer_Priority ti_uia_runtime_LoggerProbePoint_getPriority__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* setPriority__E */
#define ti_uia_runtime_LoggerProbePoint_setPriority ti_uia_runtime_LoggerProbePoint_setPriority__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_setPriority__E, "ti_uia_runtime_LoggerProbePoint_setPriority")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_setPriority__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, ti_uia_runtime_IUIATransfer_Priority priority );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_setPriority__F, "ti_uia_runtime_LoggerProbePoint_setPriority")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_setPriority__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, ti_uia_runtime_IUIATransfer_Priority priority );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_setPriority__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, ti_uia_runtime_IUIATransfer_Priority priority );

/* reset__E */
#define ti_uia_runtime_LoggerProbePoint_reset ti_uia_runtime_LoggerProbePoint_reset__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_reset__E, "ti_uia_runtime_LoggerProbePoint_reset")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_reset__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_reset__F, "ti_uia_runtime_LoggerProbePoint_reset")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_reset__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_reset__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* writeMemoryRange__E */
#define ti_uia_runtime_LoggerProbePoint_writeMemoryRange ti_uia_runtime_LoggerProbePoint_writeMemoryRange__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_writeMemoryRange__E, "ti_uia_runtime_LoggerProbePoint_writeMemoryRange")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_writeMemoryRange__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_UInt32 snapshotId, xdc_IArg fileName, xdc_IArg LineNum, xdc_IArg fmt, xdc_IArg startAdrs, xdc_UInt32 lengthInMAUs );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_writeMemoryRange__F, "ti_uia_runtime_LoggerProbePoint_writeMemoryRange")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_writeMemoryRange__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_UInt32 snapshotId, xdc_IArg fileName, xdc_IArg LineNum, xdc_IArg fmt, xdc_IArg startAdrs, xdc_UInt32 lengthInMAUs );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_writeMemoryRange__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_UInt32 snapshotId, xdc_IArg fileName, xdc_IArg LineNum, xdc_IArg fmt, xdc_IArg startAdrs, xdc_UInt32 lengthInMAUs );

/* setModuleIdToRouteToStatusLogger__E */
#define ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger__E, "ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger__E( xdc_runtime_Types_ModuleId mid );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger__F, "ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger__F( xdc_runtime_Types_ModuleId mid );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger__R( xdc_runtime_Types_ModuleId mid );

/* flushAll__E */
#define ti_uia_runtime_LoggerProbePoint_flushAll ti_uia_runtime_LoggerProbePoint_flushAll__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_flushAll__E, "ti_uia_runtime_LoggerProbePoint_flushAll")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_flushAll__E( void );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_flushAll__F, "ti_uia_runtime_LoggerProbePoint_flushAll")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_flushAll__F( void );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_flushAll__R( void );

/* flushAllInternal__E */
#define ti_uia_runtime_LoggerProbePoint_flushAllInternal ti_uia_runtime_LoggerProbePoint_flushAllInternal__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_flushAllInternal__E, "ti_uia_runtime_LoggerProbePoint_flushAllInternal")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_flushAllInternal__E( xdc_Int stat );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_flushAllInternal__F, "ti_uia_runtime_LoggerProbePoint_flushAllInternal")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_flushAllInternal__F( xdc_Int stat );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_flushAllInternal__R( xdc_Int stat );

/* flush__E */
#define ti_uia_runtime_LoggerProbePoint_flush ti_uia_runtime_LoggerProbePoint_flush__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_flush__E, "ti_uia_runtime_LoggerProbePoint_flush")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_flush__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_flush__F, "ti_uia_runtime_LoggerProbePoint_flush")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_flush__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_flush__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* getNumDropped__E */
#define ti_uia_runtime_LoggerProbePoint_getNumDropped ti_uia_runtime_LoggerProbePoint_getNumDropped__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getNumDropped__E, "ti_uia_runtime_LoggerProbePoint_getNumDropped")
__extern xdc_Int ti_uia_runtime_LoggerProbePoint_getNumDropped__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getNumDropped__F, "ti_uia_runtime_LoggerProbePoint_getNumDropped")
__extern xdc_Int ti_uia_runtime_LoggerProbePoint_getNumDropped__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_Int ti_uia_runtime_LoggerProbePoint_getNumDropped__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* enable__E */
#define ti_uia_runtime_LoggerProbePoint_enable ti_uia_runtime_LoggerProbePoint_enable__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_enable__E, "ti_uia_runtime_LoggerProbePoint_enable")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_enable__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_enable__F, "ti_uia_runtime_LoggerProbePoint_enable")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_enable__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_enable__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* disable__E */
#define ti_uia_runtime_LoggerProbePoint_disable ti_uia_runtime_LoggerProbePoint_disable__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_disable__E, "ti_uia_runtime_LoggerProbePoint_disable")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_disable__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_disable__F, "ti_uia_runtime_LoggerProbePoint_disable")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_disable__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_disable__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* write0__E */
#define ti_uia_runtime_LoggerProbePoint_write0 ti_uia_runtime_LoggerProbePoint_write0__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write0__E, "ti_uia_runtime_LoggerProbePoint_write0")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write0__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write0__F, "ti_uia_runtime_LoggerProbePoint_write0")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write0__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write0__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid );

/* write1__E */
#define ti_uia_runtime_LoggerProbePoint_write1 ti_uia_runtime_LoggerProbePoint_write1__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write1__E, "ti_uia_runtime_LoggerProbePoint_write1")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write1__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write1__F, "ti_uia_runtime_LoggerProbePoint_write1")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write1__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write1__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 );

/* write2__E */
#define ti_uia_runtime_LoggerProbePoint_write2 ti_uia_runtime_LoggerProbePoint_write2__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write2__E, "ti_uia_runtime_LoggerProbePoint_write2")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write2__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write2__F, "ti_uia_runtime_LoggerProbePoint_write2")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write2__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write2__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 );

/* write4__E */
#define ti_uia_runtime_LoggerProbePoint_write4 ti_uia_runtime_LoggerProbePoint_write4__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write4__E, "ti_uia_runtime_LoggerProbePoint_write4")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write4__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write4__F, "ti_uia_runtime_LoggerProbePoint_write4")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write4__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write4__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 );

/* write8__E */
#define ti_uia_runtime_LoggerProbePoint_write8 ti_uia_runtime_LoggerProbePoint_write8__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write8__E, "ti_uia_runtime_LoggerProbePoint_write8")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write8__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_write8__F, "ti_uia_runtime_LoggerProbePoint_write8")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write8__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_write8__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 );

/* setFilterLevel__E */
#define ti_uia_runtime_LoggerProbePoint_setFilterLevel ti_uia_runtime_LoggerProbePoint_setFilterLevel__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_setFilterLevel__E, "ti_uia_runtime_LoggerProbePoint_setFilterLevel")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_setFilterLevel__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Diags_Mask mask, xdc_runtime_Diags_EventLevel filterLevel );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_setFilterLevel__F, "ti_uia_runtime_LoggerProbePoint_setFilterLevel")
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_setFilterLevel__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, xdc_runtime_Diags_Mask mask, xdc_runtime_Diags_EventLevel filterLevel );
__extern xdc_Void ti_uia_runtime_LoggerProbePoint_setFilterLevel__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Diags_Mask mask, xdc_runtime_Diags_EventLevel filterLevel );

/* getFilterLevel__E */
#define ti_uia_runtime_LoggerProbePoint_getFilterLevel ti_uia_runtime_LoggerProbePoint_getFilterLevel__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getFilterLevel__E, "ti_uia_runtime_LoggerProbePoint_getFilterLevel")
__extern xdc_runtime_Diags_Mask ti_uia_runtime_LoggerProbePoint_getFilterLevel__E( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Diags_EventLevel level );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getFilterLevel__F, "ti_uia_runtime_LoggerProbePoint_getFilterLevel")
__extern xdc_runtime_Diags_Mask ti_uia_runtime_LoggerProbePoint_getFilterLevel__F( ti_uia_runtime_LoggerProbePoint_Object* __inst, xdc_runtime_Diags_EventLevel level );
__extern xdc_runtime_Diags_Mask ti_uia_runtime_LoggerProbePoint_getFilterLevel__R( ti_uia_runtime_LoggerProbePoint_Handle __inst, xdc_runtime_Diags_EventLevel level );

/* getFreeSize__E */
#define ti_uia_runtime_LoggerProbePoint_getFreeSize ti_uia_runtime_LoggerProbePoint_getFreeSize__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getFreeSize__E, "ti_uia_runtime_LoggerProbePoint_getFreeSize")
__extern xdc_SizeT ti_uia_runtime_LoggerProbePoint_getFreeSize__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getFreeSize__F, "ti_uia_runtime_LoggerProbePoint_getFreeSize")
__extern xdc_SizeT ti_uia_runtime_LoggerProbePoint_getFreeSize__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_SizeT ti_uia_runtime_LoggerProbePoint_getFreeSize__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* getUnreadSize__E */
#define ti_uia_runtime_LoggerProbePoint_getUnreadSize ti_uia_runtime_LoggerProbePoint_getUnreadSize__E
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getUnreadSize__E, "ti_uia_runtime_LoggerProbePoint_getUnreadSize")
__extern xdc_SizeT ti_uia_runtime_LoggerProbePoint_getUnreadSize__E( ti_uia_runtime_LoggerProbePoint_Handle __inst );
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_getUnreadSize__F, "ti_uia_runtime_LoggerProbePoint_getUnreadSize")
__extern xdc_SizeT ti_uia_runtime_LoggerProbePoint_getUnreadSize__F( ti_uia_runtime_LoggerProbePoint_Object* __inst );
__extern xdc_SizeT ti_uia_runtime_LoggerProbePoint_getUnreadSize__R( ti_uia_runtime_LoggerProbePoint_Handle __inst );

/* readBlockOfMemory__I */
#define ti_uia_runtime_LoggerProbePoint_readBlockOfMemory ti_uia_runtime_LoggerProbePoint_readBlockOfMemory__I
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_readBlockOfMemory__I, "ti_uia_runtime_LoggerProbePoint_readBlockOfMemory")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_readBlockOfMemory__I( ti_uia_runtime_LoggerProbePoint_Handle obj, xdc_Ptr pMemBlock, xdc_SizeT sizeToRead );

/* writeBlockOfMemory__I */
#define ti_uia_runtime_LoggerProbePoint_writeBlockOfMemory ti_uia_runtime_LoggerProbePoint_writeBlockOfMemory__I
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_writeBlockOfMemory__I, "ti_uia_runtime_LoggerProbePoint_writeBlockOfMemory")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_writeBlockOfMemory__I( ti_uia_runtime_LoggerProbePoint_Handle obj, xdc_Ptr newWrPtr, xdc_Ptr pMemBlock, xdc_SizeT size );

/* filterOutEvent__I */
#define ti_uia_runtime_LoggerProbePoint_filterOutEvent ti_uia_runtime_LoggerProbePoint_filterOutEvent__I
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_filterOutEvent__I, "ti_uia_runtime_LoggerProbePoint_filterOutEvent")
__extern xdc_Bool ti_uia_runtime_LoggerProbePoint_filterOutEvent__I( xdc_runtime_Diags_Mask mask );

/* postIncrementPtr__I */
#define ti_uia_runtime_LoggerProbePoint_postIncrementPtr ti_uia_runtime_LoggerProbePoint_postIncrementPtr__I
xdc__CODESECT(ti_uia_runtime_LoggerProbePoint_postIncrementPtr__I, "ti_uia_runtime_LoggerProbePoint_postIncrementPtr")
__extern xdc_UArg* ti_uia_runtime_LoggerProbePoint_postIncrementPtr__I( ti_uia_runtime_LoggerProbePoint_Object* obj, xdc_UArg* myRdPtr );


/*
 * ======== FUNCTION SELECTORS ========
 */

/* getTransferType_{FxnT,fxnP} */
typedef ti_uia_runtime_IUIATransfer_TransferType (*ti_uia_runtime_LoggerProbePoint_getTransferType_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_getTransferType_FxnT ti_uia_runtime_LoggerProbePoint_getTransferType_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_getTransferType_FxnT)ti_uia_runtime_LoggerProbePoint_getTransferType; 
}

/* getContents_{FxnT,fxnP} */
typedef xdc_Bool (*ti_uia_runtime_LoggerProbePoint_getContents_FxnT)(void*, xdc_Ptr, xdc_SizeT, xdc_SizeT*);
static inline ti_uia_runtime_LoggerProbePoint_getContents_FxnT ti_uia_runtime_LoggerProbePoint_getContents_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_getContents_FxnT)ti_uia_runtime_LoggerProbePoint_getContents; 
}

/* isEmpty_{FxnT,fxnP} */
typedef xdc_Bool (*ti_uia_runtime_LoggerProbePoint_isEmpty_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_isEmpty_FxnT ti_uia_runtime_LoggerProbePoint_isEmpty_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_isEmpty_FxnT)ti_uia_runtime_LoggerProbePoint_isEmpty; 
}

/* getMaxLength_{FxnT,fxnP} */
typedef xdc_SizeT (*ti_uia_runtime_LoggerProbePoint_getMaxLength_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_getMaxLength_FxnT ti_uia_runtime_LoggerProbePoint_getMaxLength_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_getMaxLength_FxnT)ti_uia_runtime_LoggerProbePoint_getMaxLength; 
}

/* getInstanceId_{FxnT,fxnP} */
typedef xdc_UInt16 (*ti_uia_runtime_LoggerProbePoint_getInstanceId_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_getInstanceId_FxnT ti_uia_runtime_LoggerProbePoint_getInstanceId_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_getInstanceId_FxnT)ti_uia_runtime_LoggerProbePoint_getInstanceId; 
}

/* getPriority_{FxnT,fxnP} */
typedef ti_uia_runtime_IUIATransfer_Priority (*ti_uia_runtime_LoggerProbePoint_getPriority_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_getPriority_FxnT ti_uia_runtime_LoggerProbePoint_getPriority_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_getPriority_FxnT)ti_uia_runtime_LoggerProbePoint_getPriority; 
}

/* setPriority_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_setPriority_FxnT)(void*, ti_uia_runtime_IUIATransfer_Priority);
static inline ti_uia_runtime_LoggerProbePoint_setPriority_FxnT ti_uia_runtime_LoggerProbePoint_setPriority_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_setPriority_FxnT)ti_uia_runtime_LoggerProbePoint_setPriority; 
}

/* reset_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_reset_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_reset_FxnT ti_uia_runtime_LoggerProbePoint_reset_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_reset_FxnT)ti_uia_runtime_LoggerProbePoint_reset; 
}

/* writeMemoryRange_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_writeMemoryRange_FxnT)(void*, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_UInt32, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_UInt32);
static inline ti_uia_runtime_LoggerProbePoint_writeMemoryRange_FxnT ti_uia_runtime_LoggerProbePoint_writeMemoryRange_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_writeMemoryRange_FxnT)ti_uia_runtime_LoggerProbePoint_writeMemoryRange; 
}

/* flush_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_flush_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_flush_FxnT ti_uia_runtime_LoggerProbePoint_flush_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_flush_FxnT)ti_uia_runtime_LoggerProbePoint_flush; 
}

/* getNumDropped_{FxnT,fxnP} */
typedef xdc_Int (*ti_uia_runtime_LoggerProbePoint_getNumDropped_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_getNumDropped_FxnT ti_uia_runtime_LoggerProbePoint_getNumDropped_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_getNumDropped_FxnT)ti_uia_runtime_LoggerProbePoint_getNumDropped; 
}

/* enable_{FxnT,fxnP} */
typedef xdc_Bool (*ti_uia_runtime_LoggerProbePoint_enable_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_enable_FxnT ti_uia_runtime_LoggerProbePoint_enable_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_enable_FxnT)ti_uia_runtime_LoggerProbePoint_enable; 
}

/* disable_{FxnT,fxnP} */
typedef xdc_Bool (*ti_uia_runtime_LoggerProbePoint_disable_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_disable_FxnT ti_uia_runtime_LoggerProbePoint_disable_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_disable_FxnT)ti_uia_runtime_LoggerProbePoint_disable; 
}

/* write0_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_write0_FxnT)(void*, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId);
static inline ti_uia_runtime_LoggerProbePoint_write0_FxnT ti_uia_runtime_LoggerProbePoint_write0_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_write0_FxnT)ti_uia_runtime_LoggerProbePoint_write0; 
}

/* write1_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_write1_FxnT)(void*, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_IArg);
static inline ti_uia_runtime_LoggerProbePoint_write1_FxnT ti_uia_runtime_LoggerProbePoint_write1_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_write1_FxnT)ti_uia_runtime_LoggerProbePoint_write1; 
}

/* write2_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_write2_FxnT)(void*, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_IArg, xdc_IArg);
static inline ti_uia_runtime_LoggerProbePoint_write2_FxnT ti_uia_runtime_LoggerProbePoint_write2_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_write2_FxnT)ti_uia_runtime_LoggerProbePoint_write2; 
}

/* write4_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_write4_FxnT)(void*, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);
static inline ti_uia_runtime_LoggerProbePoint_write4_FxnT ti_uia_runtime_LoggerProbePoint_write4_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_write4_FxnT)ti_uia_runtime_LoggerProbePoint_write4; 
}

/* write8_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_write8_FxnT)(void*, xdc_runtime_Log_Event, xdc_runtime_Types_ModuleId, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg, xdc_IArg);
static inline ti_uia_runtime_LoggerProbePoint_write8_FxnT ti_uia_runtime_LoggerProbePoint_write8_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_write8_FxnT)ti_uia_runtime_LoggerProbePoint_write8; 
}

/* setFilterLevel_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_LoggerProbePoint_setFilterLevel_FxnT)(void*, xdc_runtime_Diags_Mask, xdc_runtime_Diags_EventLevel);
static inline ti_uia_runtime_LoggerProbePoint_setFilterLevel_FxnT ti_uia_runtime_LoggerProbePoint_setFilterLevel_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_setFilterLevel_FxnT)ti_uia_runtime_LoggerProbePoint_setFilterLevel; 
}

/* getFilterLevel_{FxnT,fxnP} */
typedef xdc_runtime_Diags_Mask (*ti_uia_runtime_LoggerProbePoint_getFilterLevel_FxnT)(void*, xdc_runtime_Diags_EventLevel);
static inline ti_uia_runtime_LoggerProbePoint_getFilterLevel_FxnT ti_uia_runtime_LoggerProbePoint_getFilterLevel_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_getFilterLevel_FxnT)ti_uia_runtime_LoggerProbePoint_getFilterLevel; 
}

/* getFreeSize_{FxnT,fxnP} */
typedef xdc_SizeT (*ti_uia_runtime_LoggerProbePoint_getFreeSize_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_getFreeSize_FxnT ti_uia_runtime_LoggerProbePoint_getFreeSize_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_getFreeSize_FxnT)ti_uia_runtime_LoggerProbePoint_getFreeSize; 
}

/* getUnreadSize_{FxnT,fxnP} */
typedef xdc_SizeT (*ti_uia_runtime_LoggerProbePoint_getUnreadSize_FxnT)(void*);
static inline ti_uia_runtime_LoggerProbePoint_getUnreadSize_FxnT ti_uia_runtime_LoggerProbePoint_getUnreadSize_fxnP( void )
{
    return (ti_uia_runtime_LoggerProbePoint_getUnreadSize_FxnT)ti_uia_runtime_LoggerProbePoint_getUnreadSize; 
}


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_uia_runtime_ILoggerSnapshot_Module ti_uia_runtime_LoggerProbePoint_Module_upCast( void )
{
    return (ti_uia_runtime_ILoggerSnapshot_Module)&ti_uia_runtime_LoggerProbePoint_Module__FXNS__C;
}

/* Module_to_ti_uia_runtime_ILoggerSnapshot */
#define ti_uia_runtime_LoggerProbePoint_Module_to_ti_uia_runtime_ILoggerSnapshot ti_uia_runtime_LoggerProbePoint_Module_upCast

/* Handle_upCast */
static inline ti_uia_runtime_ILoggerSnapshot_Handle ti_uia_runtime_LoggerProbePoint_Handle_upCast( ti_uia_runtime_LoggerProbePoint_Handle i )
{
    return (ti_uia_runtime_ILoggerSnapshot_Handle)i;
}

/* Handle_to_ti_uia_runtime_ILoggerSnapshot */
#define ti_uia_runtime_LoggerProbePoint_Handle_to_ti_uia_runtime_ILoggerSnapshot ti_uia_runtime_LoggerProbePoint_Handle_upCast

/* Handle_downCast */
static inline ti_uia_runtime_LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_Handle_downCast( ti_uia_runtime_ILoggerSnapshot_Handle i )
{
    ti_uia_runtime_ILoggerSnapshot_Handle i2 = (ti_uia_runtime_ILoggerSnapshot_Handle)i;
    return (void*)i2->__fxns == (void*)&ti_uia_runtime_LoggerProbePoint_Module__FXNS__C ? (ti_uia_runtime_LoggerProbePoint_Handle)i : 0;
}

/* Handle_from_ti_uia_runtime_ILoggerSnapshot */
#define ti_uia_runtime_LoggerProbePoint_Handle_from_ti_uia_runtime_ILoggerSnapshot ti_uia_runtime_LoggerProbePoint_Handle_downCast

/* Module_upCast2 */
static inline ti_uia_runtime_IUIATransfer_Module ti_uia_runtime_LoggerProbePoint_Module_upCast2( void )
{
    return (ti_uia_runtime_IUIATransfer_Module)&ti_uia_runtime_LoggerProbePoint_Module__FXNS__C;
}

/* Module_to_ti_uia_runtime_IUIATransfer */
#define ti_uia_runtime_LoggerProbePoint_Module_to_ti_uia_runtime_IUIATransfer ti_uia_runtime_LoggerProbePoint_Module_upCast2

/* Handle_upCast2 */
static inline ti_uia_runtime_IUIATransfer_Handle ti_uia_runtime_LoggerProbePoint_Handle_upCast2( ti_uia_runtime_LoggerProbePoint_Handle i )
{
    return (ti_uia_runtime_IUIATransfer_Handle)i;
}

/* Handle_to_ti_uia_runtime_IUIATransfer */
#define ti_uia_runtime_LoggerProbePoint_Handle_to_ti_uia_runtime_IUIATransfer ti_uia_runtime_LoggerProbePoint_Handle_upCast2

/* Handle_downCast2 */
static inline ti_uia_runtime_LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_Handle_downCast2( ti_uia_runtime_IUIATransfer_Handle i )
{
    ti_uia_runtime_IUIATransfer_Handle i2 = (ti_uia_runtime_IUIATransfer_Handle)i;
    return (void*)i2->__fxns == (void*)&ti_uia_runtime_LoggerProbePoint_Module__FXNS__C ? (ti_uia_runtime_LoggerProbePoint_Handle)i : 0;
}

/* Handle_from_ti_uia_runtime_IUIATransfer */
#define ti_uia_runtime_LoggerProbePoint_Handle_from_ti_uia_runtime_IUIATransfer ti_uia_runtime_LoggerProbePoint_Handle_downCast2

/* Module_upCast3 */
static inline xdc_runtime_IFilterLogger_Module ti_uia_runtime_LoggerProbePoint_Module_upCast3( void )
{
    return (xdc_runtime_IFilterLogger_Module)&ti_uia_runtime_LoggerProbePoint_Module__FXNS__C;
}

/* Module_to_xdc_runtime_IFilterLogger */
#define ti_uia_runtime_LoggerProbePoint_Module_to_xdc_runtime_IFilterLogger ti_uia_runtime_LoggerProbePoint_Module_upCast3

/* Handle_upCast3 */
static inline xdc_runtime_IFilterLogger_Handle ti_uia_runtime_LoggerProbePoint_Handle_upCast3( ti_uia_runtime_LoggerProbePoint_Handle i )
{
    return (xdc_runtime_IFilterLogger_Handle)i;
}

/* Handle_to_xdc_runtime_IFilterLogger */
#define ti_uia_runtime_LoggerProbePoint_Handle_to_xdc_runtime_IFilterLogger ti_uia_runtime_LoggerProbePoint_Handle_upCast3

/* Handle_downCast3 */
static inline ti_uia_runtime_LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_Handle_downCast3( xdc_runtime_IFilterLogger_Handle i )
{
    xdc_runtime_IFilterLogger_Handle i2 = (xdc_runtime_IFilterLogger_Handle)i;
    return (void*)i2->__fxns == (void*)&ti_uia_runtime_LoggerProbePoint_Module__FXNS__C ? (ti_uia_runtime_LoggerProbePoint_Handle)i : 0;
}

/* Handle_from_xdc_runtime_IFilterLogger */
#define ti_uia_runtime_LoggerProbePoint_Handle_from_xdc_runtime_IFilterLogger ti_uia_runtime_LoggerProbePoint_Handle_downCast3

/* Module_upCast4 */
static inline xdc_runtime_ILogger_Module ti_uia_runtime_LoggerProbePoint_Module_upCast4( void )
{
    return (xdc_runtime_ILogger_Module)&ti_uia_runtime_LoggerProbePoint_Module__FXNS__C;
}

/* Module_to_xdc_runtime_ILogger */
#define ti_uia_runtime_LoggerProbePoint_Module_to_xdc_runtime_ILogger ti_uia_runtime_LoggerProbePoint_Module_upCast4

/* Handle_upCast4 */
static inline xdc_runtime_ILogger_Handle ti_uia_runtime_LoggerProbePoint_Handle_upCast4( ti_uia_runtime_LoggerProbePoint_Handle i )
{
    return (xdc_runtime_ILogger_Handle)i;
}

/* Handle_to_xdc_runtime_ILogger */
#define ti_uia_runtime_LoggerProbePoint_Handle_to_xdc_runtime_ILogger ti_uia_runtime_LoggerProbePoint_Handle_upCast4

/* Handle_downCast4 */
static inline ti_uia_runtime_LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_Handle_downCast4( xdc_runtime_ILogger_Handle i )
{
    xdc_runtime_ILogger_Handle i2 = (xdc_runtime_ILogger_Handle)i;
    return (void*)i2->__fxns == (void*)&ti_uia_runtime_LoggerProbePoint_Module__FXNS__C ? (ti_uia_runtime_LoggerProbePoint_Handle)i : 0;
}

/* Handle_from_xdc_runtime_ILogger */
#define ti_uia_runtime_LoggerProbePoint_Handle_from_xdc_runtime_ILogger ti_uia_runtime_LoggerProbePoint_Handle_downCast4


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_uia_runtime_LoggerProbePoint_Module_startupDone() ti_uia_runtime_LoggerProbePoint_Module__startupDone__S()

/* Object_heap */
#define ti_uia_runtime_LoggerProbePoint_Object_heap() ti_uia_runtime_LoggerProbePoint_Object__heap__C

/* Module_heap */
#define ti_uia_runtime_LoggerProbePoint_Module_heap() ti_uia_runtime_LoggerProbePoint_Object__heap__C

/* Module_id */
static inline CT__ti_uia_runtime_LoggerProbePoint_Module__id ti_uia_runtime_LoggerProbePoint_Module_id( void ) 
{
    return ti_uia_runtime_LoggerProbePoint_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_uia_runtime_LoggerProbePoint_Module_hasMask( void ) 
{
    return ti_uia_runtime_LoggerProbePoint_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 ti_uia_runtime_LoggerProbePoint_Module_getMask( void ) 
{
    return ti_uia_runtime_LoggerProbePoint_Module__diagsMask__C != NULL ? *ti_uia_runtime_LoggerProbePoint_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void ti_uia_runtime_LoggerProbePoint_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_uia_runtime_LoggerProbePoint_Module__diagsMask__C != NULL) *ti_uia_runtime_LoggerProbePoint_Module__diagsMask__C = mask;
}

/* Params_init */
static inline void ti_uia_runtime_LoggerProbePoint_Params_init( ti_uia_runtime_LoggerProbePoint_Params* prms ) 
{
    if (prms) {
        ti_uia_runtime_LoggerProbePoint_Params__init__S(prms, 0, sizeof(ti_uia_runtime_LoggerProbePoint_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_uia_runtime_LoggerProbePoint_Params_copy( ti_uia_runtime_LoggerProbePoint_Params* dst, const ti_uia_runtime_LoggerProbePoint_Params* src ) 
{
    if (dst) {
        ti_uia_runtime_LoggerProbePoint_Params__init__S(dst, (xdc_Ptr)src, sizeof(ti_uia_runtime_LoggerProbePoint_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_uia_runtime_LoggerProbePoint_Object_count() ti_uia_runtime_LoggerProbePoint_Object__count__C

/* Object_sizeof */
#define ti_uia_runtime_LoggerProbePoint_Object_sizeof() ti_uia_runtime_LoggerProbePoint_Object__sizeof__C

/* Object_get */
static inline ti_uia_runtime_LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_Object_get( ti_uia_runtime_LoggerProbePoint_Instance_State* oarr, int i ) 
{
    return (ti_uia_runtime_LoggerProbePoint_Handle)ti_uia_runtime_LoggerProbePoint_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_uia_runtime_LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_Object_first( void )
{
    return (ti_uia_runtime_LoggerProbePoint_Handle)ti_uia_runtime_LoggerProbePoint_Object__first__S();
}

/* Object_next */
static inline ti_uia_runtime_LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_Object_next( ti_uia_runtime_LoggerProbePoint_Object* obj )
{
    return (ti_uia_runtime_LoggerProbePoint_Handle)ti_uia_runtime_LoggerProbePoint_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_uia_runtime_LoggerProbePoint_Handle_label( ti_uia_runtime_LoggerProbePoint_Handle inst, xdc_runtime_Types_Label* lab )
{
    return ti_uia_runtime_LoggerProbePoint_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline String ti_uia_runtime_LoggerProbePoint_Handle_name( ti_uia_runtime_LoggerProbePoint_Handle inst )
{
    xdc_runtime_Types_Label lab;
    return ti_uia_runtime_LoggerProbePoint_Handle__label__S(inst, &lab)->iname;
}

/* create */
static inline ti_uia_runtime_LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_create( const ti_uia_runtime_LoggerProbePoint_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    return (ti_uia_runtime_LoggerProbePoint_Handle)ti_uia_runtime_LoggerProbePoint_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(ti_uia_runtime_LoggerProbePoint_Params), __eb);
}

/* construct */
static inline void ti_uia_runtime_LoggerProbePoint_construct( ti_uia_runtime_LoggerProbePoint_Struct* __obj, const ti_uia_runtime_LoggerProbePoint_Params* __prms, xdc_runtime_Error_Block* __eb )
{
    ti_uia_runtime_LoggerProbePoint_Object__create__S(__obj, sizeof (ti_uia_runtime_LoggerProbePoint_Struct), 0, (const xdc_UChar*)__prms, sizeof(ti_uia_runtime_LoggerProbePoint_Params), __eb);
}

/* delete */
static inline void ti_uia_runtime_LoggerProbePoint_delete( ti_uia_runtime_LoggerProbePoint_Handle* instp )
{
    ti_uia_runtime_LoggerProbePoint_Object__delete__S(instp);
}

/* destruct */
static inline void ti_uia_runtime_LoggerProbePoint_destruct( ti_uia_runtime_LoggerProbePoint_Struct* obj )
{
    ti_uia_runtime_LoggerProbePoint_Object__destruct__S(obj);
}

/* handle */
static inline ti_uia_runtime_LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_handle( ti_uia_runtime_LoggerProbePoint_Struct* str )
{
    return (ti_uia_runtime_LoggerProbePoint_Handle)str;
}

/* struct */
static inline ti_uia_runtime_LoggerProbePoint_Struct* ti_uia_runtime_LoggerProbePoint_struct( ti_uia_runtime_LoggerProbePoint_Handle inst )
{
    return (ti_uia_runtime_LoggerProbePoint_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_uia_runtime_LoggerProbePoint__top__
#undef __nested__
#endif

#endif /* ti_uia_runtime_LoggerProbePoint__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_uia_runtime_LoggerProbePoint__internalaccess))

#ifndef ti_uia_runtime_LoggerProbePoint__include_state
#define ti_uia_runtime_LoggerProbePoint__include_state

/* Module_State */
struct ti_uia_runtime_LoggerProbePoint_Module_State {
    xdc_runtime_Diags_Mask level1;
    xdc_runtime_Diags_Mask level2;
    xdc_runtime_Diags_Mask level3;
    xdc_runtime_Types_ModuleId moduleIdToRouteToStatusLogger;
};

/* Module__state__V */
extern struct ti_uia_runtime_LoggerProbePoint_Module_State__ ti_uia_runtime_LoggerProbePoint_Module__state__V;

/* Object */
struct ti_uia_runtime_LoggerProbePoint_Object {
    const ti_uia_runtime_LoggerProbePoint_Fxns__* __fxns;
    ti_uia_runtime_QueueDescriptor_Header hdr;
    xdc_runtime_IHeap_Handle bufHeap;
    xdc_SizeT maxEventSizeInBits32;
    xdc_Bits16 serial;
    ti_uia_runtime_IUIATransfer_TransferType transferType;
    xdc_Bool enabled;
    xdc_Bool flush;
    xdc_Int droppedEvents;
    xdc_Ptr queueStartAdrs;
    xdc_SizeT queueSizeInMAUs;
    xdc_Ptr endOfBufferAdrsPlus1;
    __TA_ti_uia_runtime_LoggerProbePoint_Instance_State__bufferArray bufferArray;
    xdc_Int numCores;
};

#endif /* ti_uia_runtime_LoggerProbePoint__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_uia_runtime_LoggerProbePoint__nolocalnames)

#ifndef ti_uia_runtime_LoggerProbePoint__localnames__done
#define ti_uia_runtime_LoggerProbePoint__localnames__done

/* module prefix */
#define LoggerProbePoint_Instance ti_uia_runtime_LoggerProbePoint_Instance
#define LoggerProbePoint_Handle ti_uia_runtime_LoggerProbePoint_Handle
#define LoggerProbePoint_Module ti_uia_runtime_LoggerProbePoint_Module
#define LoggerProbePoint_Object ti_uia_runtime_LoggerProbePoint_Object
#define LoggerProbePoint_Struct ti_uia_runtime_LoggerProbePoint_Struct
#define LoggerProbePoint_TransferType ti_uia_runtime_LoggerProbePoint_TransferType
#define LoggerProbePoint_Priority ti_uia_runtime_LoggerProbePoint_Priority
#define LoggerProbePoint_Module_State ti_uia_runtime_LoggerProbePoint_Module_State
#define LoggerProbePoint_Instance_State ti_uia_runtime_LoggerProbePoint_Instance_State
#define LoggerProbePoint_TransferType_RELIABLE ti_uia_runtime_LoggerProbePoint_TransferType_RELIABLE
#define LoggerProbePoint_TransferType_LOSSY ti_uia_runtime_LoggerProbePoint_TransferType_LOSSY
#define LoggerProbePoint_Priority_LOW ti_uia_runtime_LoggerProbePoint_Priority_LOW
#define LoggerProbePoint_Priority_STANDARD ti_uia_runtime_LoggerProbePoint_Priority_STANDARD
#define LoggerProbePoint_Priority_HIGH ti_uia_runtime_LoggerProbePoint_Priority_HIGH
#define LoggerProbePoint_Priority_SYNC ti_uia_runtime_LoggerProbePoint_Priority_SYNC
#define LoggerProbePoint_filterByLevel ti_uia_runtime_LoggerProbePoint_filterByLevel
#define LoggerProbePoint_E_badLevel ti_uia_runtime_LoggerProbePoint_E_badLevel
#define LoggerProbePoint_isTimestampEnabled ti_uia_runtime_LoggerProbePoint_isTimestampEnabled
#define LoggerProbePoint_enableFlush ti_uia_runtime_LoggerProbePoint_enableFlush
#define LoggerProbePoint_statusLogger ti_uia_runtime_LoggerProbePoint_statusLogger
#define LoggerProbePoint_overflowLogger ti_uia_runtime_LoggerProbePoint_overflowLogger
#define LoggerProbePoint_level1Mask ti_uia_runtime_LoggerProbePoint_level1Mask
#define LoggerProbePoint_level2Mask ti_uia_runtime_LoggerProbePoint_level2Mask
#define LoggerProbePoint_level3Mask ti_uia_runtime_LoggerProbePoint_level3Mask
#define LoggerProbePoint_level4Mask ti_uia_runtime_LoggerProbePoint_level4Mask
#define LoggerProbePoint_Params ti_uia_runtime_LoggerProbePoint_Params
#define LoggerProbePoint_getTransferType ti_uia_runtime_LoggerProbePoint_getTransferType
#define LoggerProbePoint_getTransferType_fxnP ti_uia_runtime_LoggerProbePoint_getTransferType_fxnP
#define LoggerProbePoint_getTransferType_FxnT ti_uia_runtime_LoggerProbePoint_getTransferType_FxnT
#define LoggerProbePoint_getContents ti_uia_runtime_LoggerProbePoint_getContents
#define LoggerProbePoint_getContents_fxnP ti_uia_runtime_LoggerProbePoint_getContents_fxnP
#define LoggerProbePoint_getContents_FxnT ti_uia_runtime_LoggerProbePoint_getContents_FxnT
#define LoggerProbePoint_isEmpty ti_uia_runtime_LoggerProbePoint_isEmpty
#define LoggerProbePoint_isEmpty_fxnP ti_uia_runtime_LoggerProbePoint_isEmpty_fxnP
#define LoggerProbePoint_isEmpty_FxnT ti_uia_runtime_LoggerProbePoint_isEmpty_FxnT
#define LoggerProbePoint_getMaxLength ti_uia_runtime_LoggerProbePoint_getMaxLength
#define LoggerProbePoint_getMaxLength_fxnP ti_uia_runtime_LoggerProbePoint_getMaxLength_fxnP
#define LoggerProbePoint_getMaxLength_FxnT ti_uia_runtime_LoggerProbePoint_getMaxLength_FxnT
#define LoggerProbePoint_getInstanceId ti_uia_runtime_LoggerProbePoint_getInstanceId
#define LoggerProbePoint_getInstanceId_fxnP ti_uia_runtime_LoggerProbePoint_getInstanceId_fxnP
#define LoggerProbePoint_getInstanceId_FxnT ti_uia_runtime_LoggerProbePoint_getInstanceId_FxnT
#define LoggerProbePoint_getPriority ti_uia_runtime_LoggerProbePoint_getPriority
#define LoggerProbePoint_getPriority_fxnP ti_uia_runtime_LoggerProbePoint_getPriority_fxnP
#define LoggerProbePoint_getPriority_FxnT ti_uia_runtime_LoggerProbePoint_getPriority_FxnT
#define LoggerProbePoint_setPriority ti_uia_runtime_LoggerProbePoint_setPriority
#define LoggerProbePoint_setPriority_fxnP ti_uia_runtime_LoggerProbePoint_setPriority_fxnP
#define LoggerProbePoint_setPriority_FxnT ti_uia_runtime_LoggerProbePoint_setPriority_FxnT
#define LoggerProbePoint_reset ti_uia_runtime_LoggerProbePoint_reset
#define LoggerProbePoint_reset_fxnP ti_uia_runtime_LoggerProbePoint_reset_fxnP
#define LoggerProbePoint_reset_FxnT ti_uia_runtime_LoggerProbePoint_reset_FxnT
#define LoggerProbePoint_writeMemoryRange ti_uia_runtime_LoggerProbePoint_writeMemoryRange
#define LoggerProbePoint_writeMemoryRange_fxnP ti_uia_runtime_LoggerProbePoint_writeMemoryRange_fxnP
#define LoggerProbePoint_writeMemoryRange_FxnT ti_uia_runtime_LoggerProbePoint_writeMemoryRange_FxnT
#define LoggerProbePoint_setModuleIdToRouteToStatusLogger ti_uia_runtime_LoggerProbePoint_setModuleIdToRouteToStatusLogger
#define LoggerProbePoint_flushAll ti_uia_runtime_LoggerProbePoint_flushAll
#define LoggerProbePoint_flushAllInternal ti_uia_runtime_LoggerProbePoint_flushAllInternal
#define LoggerProbePoint_flush ti_uia_runtime_LoggerProbePoint_flush
#define LoggerProbePoint_flush_fxnP ti_uia_runtime_LoggerProbePoint_flush_fxnP
#define LoggerProbePoint_flush_FxnT ti_uia_runtime_LoggerProbePoint_flush_FxnT
#define LoggerProbePoint_getNumDropped ti_uia_runtime_LoggerProbePoint_getNumDropped
#define LoggerProbePoint_getNumDropped_fxnP ti_uia_runtime_LoggerProbePoint_getNumDropped_fxnP
#define LoggerProbePoint_getNumDropped_FxnT ti_uia_runtime_LoggerProbePoint_getNumDropped_FxnT
#define LoggerProbePoint_enable ti_uia_runtime_LoggerProbePoint_enable
#define LoggerProbePoint_enable_fxnP ti_uia_runtime_LoggerProbePoint_enable_fxnP
#define LoggerProbePoint_enable_FxnT ti_uia_runtime_LoggerProbePoint_enable_FxnT
#define LoggerProbePoint_disable ti_uia_runtime_LoggerProbePoint_disable
#define LoggerProbePoint_disable_fxnP ti_uia_runtime_LoggerProbePoint_disable_fxnP
#define LoggerProbePoint_disable_FxnT ti_uia_runtime_LoggerProbePoint_disable_FxnT
#define LoggerProbePoint_write0 ti_uia_runtime_LoggerProbePoint_write0
#define LoggerProbePoint_write0_fxnP ti_uia_runtime_LoggerProbePoint_write0_fxnP
#define LoggerProbePoint_write0_FxnT ti_uia_runtime_LoggerProbePoint_write0_FxnT
#define LoggerProbePoint_write1 ti_uia_runtime_LoggerProbePoint_write1
#define LoggerProbePoint_write1_fxnP ti_uia_runtime_LoggerProbePoint_write1_fxnP
#define LoggerProbePoint_write1_FxnT ti_uia_runtime_LoggerProbePoint_write1_FxnT
#define LoggerProbePoint_write2 ti_uia_runtime_LoggerProbePoint_write2
#define LoggerProbePoint_write2_fxnP ti_uia_runtime_LoggerProbePoint_write2_fxnP
#define LoggerProbePoint_write2_FxnT ti_uia_runtime_LoggerProbePoint_write2_FxnT
#define LoggerProbePoint_write4 ti_uia_runtime_LoggerProbePoint_write4
#define LoggerProbePoint_write4_fxnP ti_uia_runtime_LoggerProbePoint_write4_fxnP
#define LoggerProbePoint_write4_FxnT ti_uia_runtime_LoggerProbePoint_write4_FxnT
#define LoggerProbePoint_write8 ti_uia_runtime_LoggerProbePoint_write8
#define LoggerProbePoint_write8_fxnP ti_uia_runtime_LoggerProbePoint_write8_fxnP
#define LoggerProbePoint_write8_FxnT ti_uia_runtime_LoggerProbePoint_write8_FxnT
#define LoggerProbePoint_setFilterLevel ti_uia_runtime_LoggerProbePoint_setFilterLevel
#define LoggerProbePoint_setFilterLevel_fxnP ti_uia_runtime_LoggerProbePoint_setFilterLevel_fxnP
#define LoggerProbePoint_setFilterLevel_FxnT ti_uia_runtime_LoggerProbePoint_setFilterLevel_FxnT
#define LoggerProbePoint_getFilterLevel ti_uia_runtime_LoggerProbePoint_getFilterLevel
#define LoggerProbePoint_getFilterLevel_fxnP ti_uia_runtime_LoggerProbePoint_getFilterLevel_fxnP
#define LoggerProbePoint_getFilterLevel_FxnT ti_uia_runtime_LoggerProbePoint_getFilterLevel_FxnT
#define LoggerProbePoint_getFreeSize ti_uia_runtime_LoggerProbePoint_getFreeSize
#define LoggerProbePoint_getFreeSize_fxnP ti_uia_runtime_LoggerProbePoint_getFreeSize_fxnP
#define LoggerProbePoint_getFreeSize_FxnT ti_uia_runtime_LoggerProbePoint_getFreeSize_FxnT
#define LoggerProbePoint_getUnreadSize ti_uia_runtime_LoggerProbePoint_getUnreadSize
#define LoggerProbePoint_getUnreadSize_fxnP ti_uia_runtime_LoggerProbePoint_getUnreadSize_fxnP
#define LoggerProbePoint_getUnreadSize_FxnT ti_uia_runtime_LoggerProbePoint_getUnreadSize_FxnT
#define LoggerProbePoint_Module_name ti_uia_runtime_LoggerProbePoint_Module_name
#define LoggerProbePoint_Module_id ti_uia_runtime_LoggerProbePoint_Module_id
#define LoggerProbePoint_Module_startup ti_uia_runtime_LoggerProbePoint_Module_startup
#define LoggerProbePoint_Module_startupDone ti_uia_runtime_LoggerProbePoint_Module_startupDone
#define LoggerProbePoint_Module_hasMask ti_uia_runtime_LoggerProbePoint_Module_hasMask
#define LoggerProbePoint_Module_getMask ti_uia_runtime_LoggerProbePoint_Module_getMask
#define LoggerProbePoint_Module_setMask ti_uia_runtime_LoggerProbePoint_Module_setMask
#define LoggerProbePoint_Object_heap ti_uia_runtime_LoggerProbePoint_Object_heap
#define LoggerProbePoint_Module_heap ti_uia_runtime_LoggerProbePoint_Module_heap
#define LoggerProbePoint_construct ti_uia_runtime_LoggerProbePoint_construct
#define LoggerProbePoint_create ti_uia_runtime_LoggerProbePoint_create
#define LoggerProbePoint_handle ti_uia_runtime_LoggerProbePoint_handle
#define LoggerProbePoint_struct ti_uia_runtime_LoggerProbePoint_struct
#define LoggerProbePoint_Handle_label ti_uia_runtime_LoggerProbePoint_Handle_label
#define LoggerProbePoint_Handle_name ti_uia_runtime_LoggerProbePoint_Handle_name
#define LoggerProbePoint_Instance_init ti_uia_runtime_LoggerProbePoint_Instance_init
#define LoggerProbePoint_Object_count ti_uia_runtime_LoggerProbePoint_Object_count
#define LoggerProbePoint_Object_get ti_uia_runtime_LoggerProbePoint_Object_get
#define LoggerProbePoint_Object_first ti_uia_runtime_LoggerProbePoint_Object_first
#define LoggerProbePoint_Object_next ti_uia_runtime_LoggerProbePoint_Object_next
#define LoggerProbePoint_Object_sizeof ti_uia_runtime_LoggerProbePoint_Object_sizeof
#define LoggerProbePoint_Params_copy ti_uia_runtime_LoggerProbePoint_Params_copy
#define LoggerProbePoint_Params_init ti_uia_runtime_LoggerProbePoint_Params_init
#define LoggerProbePoint_Instance_finalize ti_uia_runtime_LoggerProbePoint_Instance_finalize
#define LoggerProbePoint_delete ti_uia_runtime_LoggerProbePoint_delete
#define LoggerProbePoint_destruct ti_uia_runtime_LoggerProbePoint_destruct
#define LoggerProbePoint_Module_upCast ti_uia_runtime_LoggerProbePoint_Module_upCast
#define LoggerProbePoint_Module_to_ti_uia_runtime_ILoggerSnapshot ti_uia_runtime_LoggerProbePoint_Module_to_ti_uia_runtime_ILoggerSnapshot
#define LoggerProbePoint_Handle_upCast ti_uia_runtime_LoggerProbePoint_Handle_upCast
#define LoggerProbePoint_Handle_to_ti_uia_runtime_ILoggerSnapshot ti_uia_runtime_LoggerProbePoint_Handle_to_ti_uia_runtime_ILoggerSnapshot
#define LoggerProbePoint_Handle_downCast ti_uia_runtime_LoggerProbePoint_Handle_downCast
#define LoggerProbePoint_Handle_from_ti_uia_runtime_ILoggerSnapshot ti_uia_runtime_LoggerProbePoint_Handle_from_ti_uia_runtime_ILoggerSnapshot
#define LoggerProbePoint_Module_upCast2 ti_uia_runtime_LoggerProbePoint_Module_upCast2
#define LoggerProbePoint_Module_to_ti_uia_runtime_IUIATransfer ti_uia_runtime_LoggerProbePoint_Module_to_ti_uia_runtime_IUIATransfer
#define LoggerProbePoint_Handle_upCast2 ti_uia_runtime_LoggerProbePoint_Handle_upCast2
#define LoggerProbePoint_Handle_to_ti_uia_runtime_IUIATransfer ti_uia_runtime_LoggerProbePoint_Handle_to_ti_uia_runtime_IUIATransfer
#define LoggerProbePoint_Handle_downCast2 ti_uia_runtime_LoggerProbePoint_Handle_downCast2
#define LoggerProbePoint_Handle_from_ti_uia_runtime_IUIATransfer ti_uia_runtime_LoggerProbePoint_Handle_from_ti_uia_runtime_IUIATransfer
#define LoggerProbePoint_Module_upCast3 ti_uia_runtime_LoggerProbePoint_Module_upCast3
#define LoggerProbePoint_Module_to_xdc_runtime_IFilterLogger ti_uia_runtime_LoggerProbePoint_Module_to_xdc_runtime_IFilterLogger
#define LoggerProbePoint_Handle_upCast3 ti_uia_runtime_LoggerProbePoint_Handle_upCast3
#define LoggerProbePoint_Handle_to_xdc_runtime_IFilterLogger ti_uia_runtime_LoggerProbePoint_Handle_to_xdc_runtime_IFilterLogger
#define LoggerProbePoint_Handle_downCast3 ti_uia_runtime_LoggerProbePoint_Handle_downCast3
#define LoggerProbePoint_Handle_from_xdc_runtime_IFilterLogger ti_uia_runtime_LoggerProbePoint_Handle_from_xdc_runtime_IFilterLogger
#define LoggerProbePoint_Module_upCast4 ti_uia_runtime_LoggerProbePoint_Module_upCast4
#define LoggerProbePoint_Module_to_xdc_runtime_ILogger ti_uia_runtime_LoggerProbePoint_Module_to_xdc_runtime_ILogger
#define LoggerProbePoint_Handle_upCast4 ti_uia_runtime_LoggerProbePoint_Handle_upCast4
#define LoggerProbePoint_Handle_to_xdc_runtime_ILogger ti_uia_runtime_LoggerProbePoint_Handle_to_xdc_runtime_ILogger
#define LoggerProbePoint_Handle_downCast4 ti_uia_runtime_LoggerProbePoint_Handle_downCast4
#define LoggerProbePoint_Handle_from_xdc_runtime_ILogger ti_uia_runtime_LoggerProbePoint_Handle_from_xdc_runtime_ILogger

#endif /* ti_uia_runtime_LoggerProbePoint__localnames__done */
#endif
/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:25; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

