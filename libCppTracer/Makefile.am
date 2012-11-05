AUTOMAKE_OPTIONS = gnu
lib_LTLIBRARIES = libCppTracer.la

INCLUDES = -I$(top_srcdir)
AM_CPPFLAGS = -D_GNU_SOURCE -DCONFIGDIR="$(sysconfdir)" -DLOGGER=consoleLogger -D_DEBUG_

# Sources for libCppTracer
libCppTracer_la_SOURCES = libCppTracer.c

# Linker options libCppTracer
libCppTracer_la_LDFLAGS = -ldl -shared 



