/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y23
 */

#ifndef ti_uia_runtime_LoggerCircBuf__INTERNAL__
#define ti_uia_runtime_LoggerCircBuf__INTERNAL__

#ifndef ti_uia_runtime_LoggerCircBuf__internalaccess
#define ti_uia_runtime_LoggerCircBuf__internalaccess
#endif

#include <ti/uia/runtime/LoggerCircBuf.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* getTransferType */
#undef ti_uia_runtime_LoggerCircBuf_getTransferType
#define ti_uia_runtime_LoggerCircBuf_getTransferType ti_uia_runtime_LoggerCircBuf_getTransferType__F

/* getContents */
#undef ti_uia_runtime_LoggerCircBuf_getContents
#define ti_uia_runtime_LoggerCircBuf_getContents ti_uia_runtime_LoggerCircBuf_getContents__E

/* isEmpty */
#undef ti_uia_runtime_LoggerCircBuf_isEmpty
#define ti_uia_runtime_LoggerCircBuf_isEmpty ti_uia_runtime_LoggerCircBuf_isEmpty__E

/* getMaxLength */
#undef ti_uia_runtime_LoggerCircBuf_getMaxLength
#define ti_uia_runtime_LoggerCircBuf_getMaxLength ti_uia_runtime_LoggerCircBuf_getMaxLength__E

/* getInstanceId */
#undef ti_uia_runtime_LoggerCircBuf_getInstanceId
#define ti_uia_runtime_LoggerCircBuf_getInstanceId ti_uia_runtime_LoggerCircBuf_getInstanceId__E

/* getPriority */
#undef ti_uia_runtime_LoggerCircBuf_getPriority
#define ti_uia_runtime_LoggerCircBuf_getPriority ti_uia_runtime_LoggerCircBuf_getPriority__E

/* setPriority */
#undef ti_uia_runtime_LoggerCircBuf_setPriority
#define ti_uia_runtime_LoggerCircBuf_setPriority ti_uia_runtime_LoggerCircBuf_setPriority__E

/* reset */
#undef ti_uia_runtime_LoggerCircBuf_reset
#define ti_uia_runtime_LoggerCircBuf_reset ti_uia_runtime_LoggerCircBuf_reset__F

/* writeMemoryRange */
#undef ti_uia_runtime_LoggerCircBuf_writeMemoryRange
#define ti_uia_runtime_LoggerCircBuf_writeMemoryRange ti_uia_runtime_LoggerCircBuf_writeMemoryRange__E

/* setModuleIdToRouteToStatusLogger */
#undef ti_uia_runtime_LoggerCircBuf_setModuleIdToRouteToStatusLogger
#define ti_uia_runtime_LoggerCircBuf_setModuleIdToRouteToStatusLogger ti_uia_runtime_LoggerCircBuf_setModuleIdToRouteToStatusLogger__E

/* flushAll */
#undef ti_uia_runtime_LoggerCircBuf_flushAll
#define ti_uia_runtime_LoggerCircBuf_flushAll ti_uia_runtime_LoggerCircBuf_flushAll__F

/* flushAllInternal */
#undef ti_uia_runtime_LoggerCircBuf_flushAllInternal
#define ti_uia_runtime_LoggerCircBuf_flushAllInternal ti_uia_runtime_LoggerCircBuf_flushAllInternal__E

/* flush */
#undef ti_uia_runtime_LoggerCircBuf_flush
#define ti_uia_runtime_LoggerCircBuf_flush ti_uia_runtime_LoggerCircBuf_flush__E

/* getNumDropped */
#undef ti_uia_runtime_LoggerCircBuf_getNumDropped
#define ti_uia_runtime_LoggerCircBuf_getNumDropped ti_uia_runtime_LoggerCircBuf_getNumDropped__E

/* enable */
#undef ti_uia_runtime_LoggerCircBuf_enable
#define ti_uia_runtime_LoggerCircBuf_enable ti_uia_runtime_LoggerCircBuf_enable__E

/* disable */
#undef ti_uia_runtime_LoggerCircBuf_disable
#define ti_uia_runtime_LoggerCircBuf_disable ti_uia_runtime_LoggerCircBuf_disable__E

/* write0 */
#undef ti_uia_runtime_LoggerCircBuf_write0
#define ti_uia_runtime_LoggerCircBuf_write0 ti_uia_runtime_LoggerCircBuf_write0__E

/* write1 */
#undef ti_uia_runtime_LoggerCircBuf_write1
#define ti_uia_runtime_LoggerCircBuf_write1 ti_uia_runtime_LoggerCircBuf_write1__E

/* write2 */
#undef ti_uia_runtime_LoggerCircBuf_write2
#define ti_uia_runtime_LoggerCircBuf_write2 ti_uia_runtime_LoggerCircBuf_write2__E

/* write4 */
#undef ti_uia_runtime_LoggerCircBuf_write4
#define ti_uia_runtime_LoggerCircBuf_write4 ti_uia_runtime_LoggerCircBuf_write4__E

/* write8 */
#undef ti_uia_runtime_LoggerCircBuf_write8
#define ti_uia_runtime_LoggerCircBuf_write8 ti_uia_runtime_LoggerCircBuf_write8__E

/* setFilterLevel */
#undef ti_uia_runtime_LoggerCircBuf_setFilterLevel
#define ti_uia_runtime_LoggerCircBuf_setFilterLevel ti_uia_runtime_LoggerCircBuf_setFilterLevel__E

/* getFilterLevel */
#undef ti_uia_runtime_LoggerCircBuf_getFilterLevel
#define ti_uia_runtime_LoggerCircBuf_getFilterLevel ti_uia_runtime_LoggerCircBuf_getFilterLevel__E

/* getFreeSize */
#undef ti_uia_runtime_LoggerCircBuf_getFreeSize
#define ti_uia_runtime_LoggerCircBuf_getFreeSize ti_uia_runtime_LoggerCircBuf_getFreeSize__E

/* getUnreadSize */
#undef ti_uia_runtime_LoggerCircBuf_getUnreadSize
#define ti_uia_runtime_LoggerCircBuf_getUnreadSize ti_uia_runtime_LoggerCircBuf_getUnreadSize__E

/* readBlockOfMemory */
#define LoggerCircBuf_readBlockOfMemory ti_uia_runtime_LoggerCircBuf_readBlockOfMemory__I

/* writeBlockOfMemory */
#define LoggerCircBuf_writeBlockOfMemory ti_uia_runtime_LoggerCircBuf_writeBlockOfMemory__I

/* filterOutEvent */
#define LoggerCircBuf_filterOutEvent ti_uia_runtime_LoggerCircBuf_filterOutEvent__I

/* postIncrementPtr */
#define LoggerCircBuf_postIncrementPtr ti_uia_runtime_LoggerCircBuf_postIncrementPtr__I

/* Module_startup */
#undef ti_uia_runtime_LoggerCircBuf_Module_startup
#define ti_uia_runtime_LoggerCircBuf_Module_startup ti_uia_runtime_LoggerCircBuf_Module_startup__F

/* Instance_init */
#undef ti_uia_runtime_LoggerCircBuf_Instance_init
#define ti_uia_runtime_LoggerCircBuf_Instance_init ti_uia_runtime_LoggerCircBuf_Instance_init__F

/* Instance_finalize */
#undef ti_uia_runtime_LoggerCircBuf_Instance_finalize
#define ti_uia_runtime_LoggerCircBuf_Instance_finalize ti_uia_runtime_LoggerCircBuf_Instance_finalize__F

/* module */
#define LoggerCircBuf_module ((ti_uia_runtime_LoggerCircBuf_Module_State *)(xdc__MODOBJADDR__(ti_uia_runtime_LoggerCircBuf_Module__state__V)))
#if !defined(__cplusplus) || !defined(ti_uia_runtime_LoggerCircBuf__cplusplus)
#define module ((ti_uia_runtime_LoggerCircBuf_Module_State *)(xdc__MODOBJADDR__(ti_uia_runtime_LoggerCircBuf_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_uia_runtime_LoggerCircBuf_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_uia_runtime_LoggerCircBuf_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_uia_runtime_LoggerCircBuf_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_uia_runtime_LoggerCircBuf_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_uia_runtime_LoggerCircBuf_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_uia_runtime_LoggerCircBuf_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_uia_runtime_LoggerCircBuf_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_uia_runtime_LoggerCircBuf_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_uia_runtime_LoggerCircBuf_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_uia_runtime_LoggerCircBuf_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_uia_runtime_LoggerCircBuf_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_uia_runtime_LoggerCircBuf_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_uia_runtime_LoggerCircBuf_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_uia_runtime_LoggerCircBuf_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_uia_runtime_LoggerCircBuf_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_uia_runtime_LoggerCircBuf_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_uia_runtime_LoggerCircBuf_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_uia_runtime_LoggerCircBuf_Module_GateProxy_query

/* Object__sizingError */
#line 1 "Error_inconsistent_object_size_in_ti.uia.runtime.LoggerCircBuf"
typedef char ti_uia_runtime_LoggerCircBuf_Object__sizingError[sizeof(ti_uia_runtime_LoggerCircBuf_Object) > sizeof(ti_uia_runtime_LoggerCircBuf_Struct) ? -1 : 1];


#endif /* ti_uia_runtime_LoggerCircBuf__INTERNAL____ */
