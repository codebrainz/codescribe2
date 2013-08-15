AC_INIT([uitk], [0.0.1], [mbrush@codebrainz.ca])
AC_PREREQ([2.59])
AC_CONFIG_AUX_DIR([build/aux])
AC_CONFIG_MACRO_DIR([build/m4])
AC_CONFIG_HEADERS([build/ui/Config.h])
AM_INIT_AUTOMAKE([1.11 no-define foreign silent-rules])
AM_SILENT_RULES([yes])
LT_INIT([])
AC_PROG_CXX
PKG_CHECK_MODULES([GTK3], [gtk+-3.0], [use_gtk3=yes], [use_gtk3=no])
AM_CONDITIONAL([UITK_BACKEND_GTK], [test "x$use_gtk3" = "xyes"])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
