include $(top_srcdir)/common.mk

noinst_LTLIBRARIES = libmiscutils.la
libmiscutils_la_SOURCES = miscutils.c miscutils.h

noinst_LTLIBRARIES += libgw-guile-miscutils.la
libgw_guile_miscutils_la_SOURCES = miscutils-guile.c miscutils-guile.h
nodist_libgw_guile_miscutils_la_SOURCES = gw-miscutils.c
libgw_guile_miscutils_la_CFLAGS = -I$(top_srcdir) -I$(top_srcdir)/guile \
				  $(GUILE_CFLAGS) $(LIBFFI_CFLAGS)
libgw_guile_miscutils_la_LDFLAGS = -module
libgw_guile_miscutils_la_LIBADD = libmiscutils.la \
				  $(top_builddir)/guile/g-wrap/libgwrap-guile-runtime.la \
	                          $(top_builddir)/g-wrap/libgwrap-core-runtime.la \
				  $(LIBFFI_LIBS)

EXTRA_DIST= README miscutils-spec.scm update-format.scm

CLEANFILES = $(wildcard gw-*)

# Wrapset generation
gw-%.c gw-%.scm: %-spec.scm
	LD_LIBRARY_PATH=${LOCALPWD}/..:${LD_LIBRARY_PATH} \
	$(GUILE) $(GUILE_FLAGS) -c  \
	  ${SETGWPATH}" \
	  (use-modules (g-wrap)) \
	  (use-modules (examples $*-spec)) \
	  (generate-wrapset 'guile '$* \"gw-$*\")"
