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

#ifndef __G_WRAP_FFI_SUPPORT_H__
#define __G_WRAP_FFI_SUPPORT_H__

#include <ffi.h>

#ifdef __cplusplus
extern "C" {
#endif

/* FFI has messed-up type #defines, see
 * http://gcc.gnu.org/bugzilla/show_bug.cgi?id=12782 */
#if !defined(ffi_type_ulong_long)

#undef ffi_type_ulong
#undef ffi_type_slong

#if SIZEOF_LONG == 4

#define ffi_type_ulong ffi_type_uint32
#define ffi_type_slong ffi_type_sint32

#elif SIZEOF_LONG == 8

#define ffi_type_ulong ffi_type_uint64
#define ffi_type_slong ffi_type_sint64

#endif

/* any machines with 128bit long longs yet? */
#define ffi_type_ulong_long ffi_type_uint64
#define ffi_type_slong_long ffi_type_sint64

#endif /* !defined(ffi_type_ulong_long) */

#ifdef __cplusplus
}
#endif

#endif