# vasnprintf.m4 serial 11
dnl Copyright (C) 2002-2004, 2006-2007 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_VASNPRINTF],
[
  AC_REQUIRE([gl_EOVERFLOW])
  AC_CHECK_FUNCS_ONCE([vasnprintf])
  if test $ac_cv_func_vasnprintf = no; then
    gl_REPLACE_VASNPRINTF
  fi
])

AC_DEFUN([gl_REPLACE_VASNPRINTF],
[
  AC_CHECK_FUNCS_ONCE([vasnprintf])
  AC_LIBOBJ([vasnprintf])
  AC_LIBOBJ([printf-args])
  AC_LIBOBJ([printf-parse])
  AC_LIBOBJ([asnprintf])
  if test $ac_cv_func_vasnprintf = yes; then
    AC_DEFINE([REPLACE_VASNPRINTF], 1,
      [Define if vasnprintf exists but is overridden by gnulib.])
  fi
  gl_PREREQ_PRINTF_ARGS
  gl_PREREQ_PRINTF_PARSE
  gl_PREREQ_VASNPRINTF
  gl_PREREQ_ASNPRINTF
])

# Prequisites of lib/printf-args.h, lib/printf-args.c.
AC_DEFUN([gl_PREREQ_PRINTF_ARGS],
[
  AC_REQUIRE([AC_TYPE_LONG_LONG_INT])
  AC_REQUIRE([gt_TYPE_LONGDOUBLE])
  AC_REQUIRE([gt_TYPE_WCHAR_T])
  AC_REQUIRE([gt_TYPE_WINT_T])
])

# Prequisites of lib/printf-parse.h, lib/printf-parse.c.
AC_DEFUN([gl_PREREQ_PRINTF_PARSE],
[
  AC_REQUIRE([AC_TYPE_LONG_LONG_INT])
  AC_REQUIRE([gt_TYPE_LONGDOUBLE])
  AC_REQUIRE([gt_TYPE_WCHAR_T])
  AC_REQUIRE([gt_TYPE_WINT_T])
  AC_REQUIRE([AC_TYPE_SIZE_T])
  AC_CHECK_TYPES(ptrdiff_t)
  AC_REQUIRE([gt_AC_TYPE_INTMAX_T])
])

# Prerequisites of lib/vasnprintf.c.
AC_DEFUN([gl_PREREQ_VASNPRINTF],
[
  AC_REQUIRE([AC_FUNC_ALLOCA])
  AC_REQUIRE([AC_TYPE_LONG_LONG_INT])
  AC_REQUIRE([gt_TYPE_LONGDOUBLE])
  AC_REQUIRE([gt_TYPE_WCHAR_T])
  AC_REQUIRE([gt_TYPE_WINT_T])
  AC_CHECK_FUNCS(snprintf wcslen)
])

# Extra prerequisites of lib/vasnprintf.c for supporting the 'a' directive.
AC_DEFUN([gl_PREREQ_VASNPRINTF_DIRECTIVE_A],
[
  AC_REQUIRE([gl_PRINTF_DIRECTIVE_A])
  case "$gl_cv_func_printf_directive_a" in
    *yes)
      ;;
    *)
      AC_DEFINE([NEED_PRINTF_DIRECTIVE_A], 1,
        [Define if the vasnprintf implementation needs special code for
         the 'a' and 'A' directives.])
      AC_CHECK_FUNCS([nl_langinfo])
      ;;
  esac
])

# Prerequisites of lib/asnprintf.c.
AC_DEFUN([gl_PREREQ_ASNPRINTF],
[
])
