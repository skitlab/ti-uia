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
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_uia_runtime_CtxFilter__include
#define ti_uia_runtime_CtxFilter__include

#ifndef __nested__
#define __nested__
#define ti_uia_runtime_CtxFilter__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_uia_runtime_CtxFilter___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/uia/runtime/CtxFilter__prologue.h>
#include <ti/uia/runtime/package/package.defs.h>

#include <xdc/runtime/IModule.h>
#include <xdc/runtime/Diags.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* ti_uia_runtime_CtxFilter_gFlags */
#define ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gFlags ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gFlags
__extern xdc_Bits16 ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gFlags;

/* ti_uia_runtime_CtxFilter_gEnableMask */
#define ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gEnableMask ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gEnableMask
__extern xdc_Bits16 ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gEnableMask;

/* ti_uia_runtime_CtxFilter_gIsLoggingEnabled */
#define ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gIsLoggingEnabled ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gIsLoggingEnabled
__extern xdc_Bool ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gIsLoggingEnabled;

/* Mask */
typedef xdc_Bits16 ti_uia_runtime_CtxFilter_Mask;

/* ALWAYS_ENABLED */
#define ti_uia_runtime_CtxFilter_ALWAYS_ENABLED (0x0000)

/* CONTEXT_ENABLED */
#define ti_uia_runtime_CtxFilter_CONTEXT_ENABLED (true)

/* CONTEXT_DISABLED */
#define ti_uia_runtime_CtxFilter_CONTEXT_DISABLED (false)


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_uia_runtime_CtxFilter_Module__diagsEnabled;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__diagsEnabled ti_uia_runtime_CtxFilter_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_uia_runtime_CtxFilter_Module__diagsIncluded;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__diagsIncluded ti_uia_runtime_CtxFilter_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_uia_runtime_CtxFilter_Module__diagsMask;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__diagsMask ti_uia_runtime_CtxFilter_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_uia_runtime_CtxFilter_Module__gateObj;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__gateObj ti_uia_runtime_CtxFilter_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_uia_runtime_CtxFilter_Module__gatePrms;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__gatePrms ti_uia_runtime_CtxFilter_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_uia_runtime_CtxFilter_Module__id;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__id ti_uia_runtime_CtxFilter_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_uia_runtime_CtxFilter_Module__loggerDefined;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__loggerDefined ti_uia_runtime_CtxFilter_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_uia_runtime_CtxFilter_Module__loggerObj;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__loggerObj ti_uia_runtime_CtxFilter_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_uia_runtime_CtxFilter_Module__loggerFxn0;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__loggerFxn0 ti_uia_runtime_CtxFilter_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_uia_runtime_CtxFilter_Module__loggerFxn1;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__loggerFxn1 ti_uia_runtime_CtxFilter_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_uia_runtime_CtxFilter_Module__loggerFxn2;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__loggerFxn2 ti_uia_runtime_CtxFilter_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_uia_runtime_CtxFilter_Module__loggerFxn4;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__loggerFxn4 ti_uia_runtime_CtxFilter_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_uia_runtime_CtxFilter_Module__loggerFxn8;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__loggerFxn8 ti_uia_runtime_CtxFilter_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_uia_runtime_CtxFilter_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Module__startupDoneFxn ti_uia_runtime_CtxFilter_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_uia_runtime_CtxFilter_Object__count;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Object__count ti_uia_runtime_CtxFilter_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_uia_runtime_CtxFilter_Object__heap;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Object__heap ti_uia_runtime_CtxFilter_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_uia_runtime_CtxFilter_Object__sizeof;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Object__sizeof ti_uia_runtime_CtxFilter_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_uia_runtime_CtxFilter_Object__table;
__extern __FAR__ const CT__ti_uia_runtime_CtxFilter_Object__table ti_uia_runtime_CtxFilter_Object__table__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_uia_runtime_CtxFilter_Module_startup( state ) -1

/* Module__startupDone__S */
xdc__CODESECT(ti_uia_runtime_CtxFilter_Module__startupDone__S, "ti_uia_runtime_CtxFilter_Module__startupDone")
__extern xdc_Bool ti_uia_runtime_CtxFilter_Module__startupDone__S( void );

/* setContextFilterFlags__E */
#define ti_uia_runtime_CtxFilter_setContextFilterFlags ti_uia_runtime_CtxFilter_setContextFilterFlags__E
xdc__CODESECT(ti_uia_runtime_CtxFilter_setContextFilterFlags__E, "ti_uia_runtime_CtxFilter_setContextFilterFlags")
__extern xdc_Void ti_uia_runtime_CtxFilter_setContextFilterFlags__E( xdc_Bits16 flags );
xdc__CODESECT(ti_uia_runtime_CtxFilter_setContextFilterFlags__F, "ti_uia_runtime_CtxFilter_setContextFilterFlags")
__extern xdc_Void ti_uia_runtime_CtxFilter_setContextFilterFlags__F( xdc_Bits16 flags );
__extern xdc_Void ti_uia_runtime_CtxFilter_setContextFilterFlags__R( xdc_Bits16 flags );

/* isLoggingEnabledForChanCtx__E */
#define ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx__E
xdc__CODESECT(ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx__E, "ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx")
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx__E( xdc_Int newChanId );
xdc__CODESECT(ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx__F, "ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx")
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx__F( xdc_Int newChanId );
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx__R( xdc_Int newChanId );

/* isLoggingEnabledForFrameCtx__E */
#define ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx__E
xdc__CODESECT(ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx__E, "ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx")
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx__E( xdc_Int newFrameId );
xdc__CODESECT(ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx__F, "ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx")
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx__F( xdc_Int newFrameId );
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx__R( xdc_Int newFrameId );

/* isLoggingEnabledForThreadCtx__E */
#define ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx__E
xdc__CODESECT(ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx__E, "ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx")
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx__E( xdc_Int newThreadId );
xdc__CODESECT(ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx__F, "ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx")
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx__F( xdc_Int newThreadId );
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx__R( xdc_Int newThreadId );

/* isLoggingEnabledForUserCtx__E */
#define ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx__E
xdc__CODESECT(ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx__E, "ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx")
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx__E( xdc_Int newUserCtx );
xdc__CODESECT(ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx__F, "ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx")
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx__F( xdc_Int newUserCtx );
__extern xdc_Bool ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx__R( xdc_Int newUserCtx );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_uia_runtime_CtxFilter_Module_startupDone() ti_uia_runtime_CtxFilter_Module__startupDone__S()

/* Object_heap */
#define ti_uia_runtime_CtxFilter_Object_heap() ti_uia_runtime_CtxFilter_Object__heap__C

/* Module_heap */
#define ti_uia_runtime_CtxFilter_Module_heap() ti_uia_runtime_CtxFilter_Object__heap__C

/* Module_id */
static inline CT__ti_uia_runtime_CtxFilter_Module__id ti_uia_runtime_CtxFilter_Module_id( void ) 
{
    return ti_uia_runtime_CtxFilter_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_uia_runtime_CtxFilter_Module_hasMask( void ) 
{
    return ti_uia_runtime_CtxFilter_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 ti_uia_runtime_CtxFilter_Module_getMask( void ) 
{
    return ti_uia_runtime_CtxFilter_Module__diagsMask__C != NULL ? *ti_uia_runtime_CtxFilter_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void ti_uia_runtime_CtxFilter_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_uia_runtime_CtxFilter_Module__diagsMask__C != NULL) *ti_uia_runtime_CtxFilter_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#include <ti/uia/runtime/CtxFilter__epilogue.h>

#ifdef ti_uia_runtime_CtxFilter__top__
#undef __nested__
#endif

#endif /* ti_uia_runtime_CtxFilter__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_uia_runtime_CtxFilter__internalaccess))

#ifndef ti_uia_runtime_CtxFilter__include_state
#define ti_uia_runtime_CtxFilter__include_state


#endif /* ti_uia_runtime_CtxFilter__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_uia_runtime_CtxFilter__nolocalnames)

#ifndef ti_uia_runtime_CtxFilter__localnames__done
#define ti_uia_runtime_CtxFilter__localnames__done

/* module prefix */
#define CtxFilter_ti_uia_runtime_CtxFilter_gFlags ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gFlags
#define CtxFilter_ti_uia_runtime_CtxFilter_gEnableMask ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gEnableMask
#define CtxFilter_ti_uia_runtime_CtxFilter_gIsLoggingEnabled ti_uia_runtime_CtxFilter_ti_uia_runtime_CtxFilter_gIsLoggingEnabled
#define CtxFilter_Mask ti_uia_runtime_CtxFilter_Mask
#define CtxFilter_ALWAYS_ENABLED ti_uia_runtime_CtxFilter_ALWAYS_ENABLED
#define CtxFilter_CONTEXT_ENABLED ti_uia_runtime_CtxFilter_CONTEXT_ENABLED
#define CtxFilter_CONTEXT_DISABLED ti_uia_runtime_CtxFilter_CONTEXT_DISABLED
#define CtxFilter_isCtxEnabled ti_uia_runtime_CtxFilter_isCtxEnabled
#define CtxFilter_setContextFilterFlags ti_uia_runtime_CtxFilter_setContextFilterFlags
#define CtxFilter_isLoggingEnabledForChanCtx ti_uia_runtime_CtxFilter_isLoggingEnabledForChanCtx
#define CtxFilter_isLoggingEnabledForFrameCtx ti_uia_runtime_CtxFilter_isLoggingEnabledForFrameCtx
#define CtxFilter_isLoggingEnabledForThreadCtx ti_uia_runtime_CtxFilter_isLoggingEnabledForThreadCtx
#define CtxFilter_isLoggingEnabledForUserCtx ti_uia_runtime_CtxFilter_isLoggingEnabledForUserCtx
#define CtxFilter_Module_name ti_uia_runtime_CtxFilter_Module_name
#define CtxFilter_Module_id ti_uia_runtime_CtxFilter_Module_id
#define CtxFilter_Module_startup ti_uia_runtime_CtxFilter_Module_startup
#define CtxFilter_Module_startupDone ti_uia_runtime_CtxFilter_Module_startupDone
#define CtxFilter_Module_hasMask ti_uia_runtime_CtxFilter_Module_hasMask
#define CtxFilter_Module_getMask ti_uia_runtime_CtxFilter_Module_getMask
#define CtxFilter_Module_setMask ti_uia_runtime_CtxFilter_Module_setMask
#define CtxFilter_Object_heap ti_uia_runtime_CtxFilter_Object_heap
#define CtxFilter_Module_heap ti_uia_runtime_CtxFilter_Module_heap

#endif /* ti_uia_runtime_CtxFilter__localnames__done */
#endif
/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:23; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

