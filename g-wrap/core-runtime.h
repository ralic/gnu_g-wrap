/**********************************************************************
Copyright (C) 2003-2004 Andreas Rottmann
 
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 2.1, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public
License along with this software; see the file COPYING.  If not, write
to the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139,
USA.
**********************************************************************/

#ifndef __G_WRAP_CORE_RUNTIME_H__
#define __G_WRAP_CORE_RUNTIME_H__

#include <g-wrap/ffi-support.h> // TODO: Make conditional

#ifdef __cplusplus
extern "C" {
#endif

typedef void GWLangValue;
typedef enum _GWErrorStatus GWErrorStatus;
typedef struct _GWError GWError;
typedef struct _GWLangSupport GWLangSupport;
typedef struct _GWWrapSet GWWrapSet;

enum _GWErrorStatus
{
  GW_ERR_NONE,
  GW_ERR_MISC,
  GW_ERR_MEMORY,
  GW_ERR_RANGE,
  GW_ERR_TYPE,
  GW_ERR_ARGC,
  GW_ERR_ARG_RANGE,
  GW_ERR_ARG_TYPE
};

struct _GWError
{
    GWErrorStatus status;
    const char *message;
    GWLangValue *data;
};

struct _GWLangSupport
{
    void  (*register_wrapset) (GWWrapSet *ws);
    
    void *(*malloc) (size_t size);
    void *(*realloc) (void *mem, size_t size);
    void  (*raise_error) (const char *func_name, const char *error);
    void  (*handle_wrapper_error) (GWError *error,
                                   const char *func_name,
                                   unsigned int arg_pos);
};

int        gw_runtime_init (GWLangSupport *lang);
void *     gw_malloc (size_t size);
void *     gw_realloc (void *mem, size_t size);
void       gw_raise_error (const char *proc, const char *fmt, ...);
void       gw_handle_wrapper_error (GWError *error,
                                    const char *func_name,
                                    unsigned int arg_pos);

/*
 * Runtime information (RTI) section
 */

typedef struct _GWFunctionInfo GWFunctionInfo;
typedef struct _GWTypeInfo GWTypeInfo;

typedef unsigned long GWTypeSpec;

enum
{
  GW_TYPESPEC_CALLER_OWNED = 0x01,
  GW_TYPESPEC_CALLEE_OWNED = 0x02
};

#define GW_TYPESPEC_USER_SHIFT 8

typedef void (*GWUnWrapValueFunc)(void *instance,
                                  const GWTypeSpec *ts,
                                  GWLangValue *val,
                                  GWError *error);
typedef void (*GWWrapValueFunc)(void *instance,
                                const GWTypeSpec *ts,
                                GWLangValue *val,
                                GWError *error);
typedef void (*GWDestructValueFunc)(void *instance,
                                    const GWTypeSpec *ts,
                                    GWError *error);


struct _GWTypeInfo
{
    const char *name;
    const char *class_name;

    ffi_type *type; /* if non-NULL, this type may passed dynamically */

    GWWrapValueFunc wrap_value;
    GWUnWrapValueFunc unwrap_value;
    GWDestructValueFunc destruct_value;
};

struct _GWFunctionInfo
{
    int dynamic; /* set if all arg types are dynamic and we should
                  * create the function dynamically. */
    
    void *proc;            /* Wrapper function (if !dynamic) or real C
                            * function */
    int n_args;

    GWTypeInfo *ret_type;
    GWTypeSpec ret_typespec;
    
    int nargs;
    GWTypeInfo **arg_types; /* array */
    GWTypeSpec *arg_typespecs;
    
    const char *proc_name;
    const char *generic_name;

    ffi_cif cif;
    unsigned int data_area_size; /* Size needed for the dynamic-call info */
};

struct _GWWrapSet
{
    const char *name;
    
    int ndependencies;
    GWWrapSet **dependencies;
    
    int ntypes;
    GWTypeInfo *types;
    
    int nfunctions;
    GWFunctionInfo *functions;

    /* private */
    int ntypes_allocated;
    int types_sorted;
    int nfuncs_allocated;
};

GWWrapSet *gw_wrapset_new(const char *name, const char *dependency, ...);
void       gw_wrapset_add_type(GWWrapSet *ws,
                               const char *name,        /* static */
                               const char *class_name,  /* static */
                               ffi_type *type,
                               const char **subtypes,
                               GWWrapValueFunc wrap_value,
                               GWUnWrapValueFunc unwrap_value,
                               GWDestructValueFunc destruct_value);
GWTypeInfo *gw_wrapset_lookup_type(GWWrapSet *ws, const char *name);

void 	   gw_wrapset_add_function(GWWrapSet *ws,
                                   void *proc,
                                   int n_args,
                                   const char *ret_type,
                                   GWTypeSpec ret_typespec,
                                   const char **arg_types,
                                   GWTypeSpec *arg_typespecs,
                                   const char *proc_name,
                                   const char *generic_name);

void 	   gw_wrapset_register(GWWrapSet *ws);

#ifdef __cplusplus
}
#endif

#endif
