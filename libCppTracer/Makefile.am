#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libCppTracer.la

#######################################
# Build information for each library
AUTOMAKE_OPTIONS = gnu
INCLUDES = -I$(top_srcdir)
AM_CPPFLAGS = -D_GNU_SOURCE -DCONFIGDIR="$(sysconfdir)" LOGGER=consoleLogger -D_DEBUG_

# Sources for libCppTracer
libCppTracer_la_SOURCES = libCppTracer.c

# Linker options libTestProgram
libCppTracer_la_LDFLAGS = -ldl -shared -ldbgflags

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libCppTracer_la_CPPFLAGS = -I$(top_srcdir)/include

