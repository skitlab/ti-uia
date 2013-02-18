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
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION STUBS
 *     FUNCTION SELECTORS
 *     
 *     EPILOGUE
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_uia_runtime_ICtxFilterCallback__include
#define ti_uia_runtime_ICtxFilterCallback__include

#ifndef __nested__
#define __nested__
#define ti_uia_runtime_ICtxFilterCallback__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_uia_runtime_ICtxFilterCallback___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/uia/runtime/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_uia_runtime_ICtxFilterCallback_Params {
    size_t __size;
    const void* __self;
    void* __fxns;
    xdc_runtime_IInstance_Params* instance;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_uia_runtime_ICtxFilterCallback_Fxns__ {
    xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Void (*updateIsLoggingEnabledFlag)(void*);
    xdc_runtime_Types_SysFxns2 __sfxns;
};

/* Interface__BASE__C */
__extern const xdc_runtime_Types_Base ti_uia_runtime_ICtxFilterCallback_Interface__BASE__C;


/*
 * ======== FUNCTION STUBS ========
 */

/* delete */
static inline void ti_uia_runtime_ICtxFilterCallback_delete( ti_uia_runtime_ICtxFilterCallback_Handle* instp )
{
    (*instp)->__fxns->__sysp->__delete(instp);
}

/* Handle_to_Module */
static inline ti_uia_runtime_ICtxFilterCallback_Module ti_uia_runtime_ICtxFilterCallback_Handle_to_Module( ti_uia_runtime_ICtxFilterCallback_Handle inst )
{
    return inst->__fxns;
}

/* Handle_label */
static inline xdc_runtime_Types_Label* ti_uia_runtime_ICtxFilterCallback_Handle_label( ti_uia_runtime_ICtxFilterCallback_Handle inst, xdc_runtime_Types_Label* lab )
{
    return inst->__fxns->__sysp->__label(inst, lab);
}

/* Module_id */
static inline xdc_runtime_Types_ModuleId ti_uia_runtime_ICtxFilterCallback_Module_id( ti_uia_runtime_ICtxFilterCallback_Module mod )
{
    return mod->__sysp->__mid;
}

/* updateIsLoggingEnabledFlag */
static inline xdc_Void ti_uia_runtime_ICtxFilterCallback_updateIsLoggingEnabledFlag( ti_uia_runtime_ICtxFilterCallback_Handle __inst )
{
    __inst->__fxns->updateIsLoggingEnabledFlag((void*)__inst);
}


/*
 * ======== FUNCTION SELECTORS ========
 */

/* updateIsLoggingEnabledFlag_{FxnT,fxnP} */
typedef xdc_Void (*ti_uia_runtime_ICtxFilterCallback_updateIsLoggingEnabledFlag_FxnT)(void*);
static inline ti_uia_runtime_ICtxFilterCallback_updateIsLoggingEnabledFlag_FxnT ti_uia_runtime_ICtxFilterCallback_updateIsLoggingEnabledFlag_fxnP( ti_uia_runtime_ICtxFilterCallback_Handle __inst )
{
    return (ti_uia_runtime_ICtxFilterCallback_updateIsLoggingEnabledFlag_FxnT)__inst->__fxns->updateIsLoggingEnabledFlag;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_uia_runtime_ICtxFilterCallback__top__
#undef __nested__
#endif

#endif /* ti_uia_runtime_ICtxFilterCallback__include */


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_uia_runtime_ICtxFilterCallback__nolocalnames)

#ifndef ti_uia_runtime_ICtxFilterCallback__localnames__done
#define ti_uia_runtime_ICtxFilterCallback__localnames__done

/* module prefix */
#define ICtxFilterCallback_Instance ti_uia_runtime_ICtxFilterCallback_Instance
#define ICtxFilterCallback_Handle ti_uia_runtime_ICtxFilterCallback_Handle
#define ICtxFilterCallback_Module ti_uia_runtime_ICtxFilterCallback_Module
#define ICtxFilterCallback_Params ti_uia_runtime_ICtxFilterCallback_Params
#define ICtxFilterCallback_updateIsLoggingEnabledFlag ti_uia_runtime_ICtxFilterCallback_updateIsLoggingEnabledFlag
#define ICtxFilterCallback_updateIsLoggingEnabledFlag_fxnP ti_uia_runtime_ICtxFilterCallback_updateIsLoggingEnabledFlag_fxnP
#define ICtxFilterCallback_updateIsLoggingEnabledFlag_FxnT ti_uia_runtime_ICtxFilterCallback_updateIsLoggingEnabledFlag_FxnT
#define ICtxFilterCallback_Module_name ti_uia_runtime_ICtxFilterCallback_Module_name
#define ICtxFilterCallback_delete ti_uia_runtime_ICtxFilterCallback_delete
#define ICtxFilterCallback_Handle_label ti_uia_runtime_ICtxFilterCallback_Handle_label
#define ICtxFilterCallback_Handle_to_Module ti_uia_runtime_ICtxFilterCallback_Handle_to_Module

#endif /* ti_uia_runtime_ICtxFilterCallback__localnames__done */
#endif
/*
 *  @(#) ti.uia.runtime; 1, 0, 0, 2,1; 7-13-2012 11:12:23; /db/vtree/library/trees/uia/uia-d14/src/ xlibrary

 */

