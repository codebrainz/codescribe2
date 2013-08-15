ACLOCAL_AMFLAGS = -I build/m4

AM_CPPFLAGS = -I$(top_srcdir)/include $(GTK3_CFLAGS)
AM_LDFLAGS = $(GTK3_LIBS)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# UI Toolkit Library                                                   #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

lib_LTLIBRARIES = libuitk.la

libuitk_la_SOURCES = \
	$(top_srcdir)/ui/common/Object.cpp

if UITK_BACKEND_GTK
libuitk_la_SOURCES += \
	$(top_srcdir)/ui/gtk/App.cpp \
	$(top_srcdir)/ui/gtk/Container.cpp \
	$(top_srcdir)/ui/gtk/VBox.cpp \
	$(top_srcdir)/ui/gtk/Widget.cpp \
	$(top_srcdir)/ui/gtk/Window.cpp
endif

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Public API Headers                                                   #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

uitkincludedir = $(includedir)/uitk-1.0/UI

uitkinclude_HEADERS = \
	$(top_srcdir)/include/UI/App.hpp \
	$(top_srcdir)/include/UI/AtomicCounter.hpp \
	$(top_srcdir)/include/UI/Container.hpp \
	$(top_srcdir)/include/UI/Object.hpp \
	$(top_srcdir)/include/UI/Types.hpp \
	$(top_srcdir)/include/UI/VBox.hpp \
	$(top_srcdir)/include/UI/Widget.hpp

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Test Program                                                         #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

noinst_PROGRAMS = uitk-test
uitk_test_SOURCES = $(top_srcdir)/test/main.cpp
uitk_test_LDADD = $(top_builddir)/libuitk.la
