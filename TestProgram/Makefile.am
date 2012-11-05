noinst_PROGRAMS=TestProgram
TestProgram_SOURCES=TestProgram.cpp

test: 
	LD_LIBRARY_PATH=$(top_builddir)/libCppTracer/.libs && \
	LD_PRELOAD=${PWD}/$(top_builddir)/libCppTracer/.libs/libCppTracer.so ./$(noinst_PROGRAMS)
