#######################################
# The list of executables we are building seperated by spaces
# the 'bin_' indicates that these build products will be installed
# in the $(bindir) directory. For example /usr/bin
#bin_PROGRAMS=TestProgram

# Because a.out is only a sample program we don't want it to be installed.
# The 'noinst_' prefix indicates that the following targets are not to be
# installed.
noinst_PROGRAMS=TestProgram

#######################################
# Build information for each executable. The variable name is derived
# by use the name of the executable with each non alpha-numeric character is
# replaced by '_'. So a.out becomes a_out and the appropriate suffex added.
# '_SOURCES' for example.

# Sources for the a.out 
TestProgram_SOURCES= TestProgram.cpp

# Linker options for a.out
TestProgram_LDFLAGS = 
#$(top_srcdir)/libCppExceptionsTracer/libCppExceptionsTracer.la

# Compiler options for a.out
TestProgram_CPPFLAGS = -I$(top_srcdir)/include

test: 
	LD_LIBRARY_PATH=$(top_builddir)/libCppExceptionsTracer/.libs && \
	LD_PRELOAD=${PWD}/$(top_builddir)/libCppExceptionsTracer/.libs/libCppExceptionsTracer.so ./$(noinst_PROGRAMS)
