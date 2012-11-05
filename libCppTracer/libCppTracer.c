#include "config.h"

/*
 * set a hook to the __cxa_allocate_exception function of the libstdc++
 * based on an analyze of a cpp program throwing a C++ exception
 * build with gcc 4.4.5-8 running on a debian 6-64
 * then the gcc-4.4.5 to get it's signature
 *
 * objdump -T /usr/lib/libstdc++.so.6 | grep __cxa_allocate_exception
 * 000bbb80 g    DF .text	000001db  CXXABI_1.3  __cxa_allocate_exception
 *
 * gcc-4.4.5/libstdc++-v3/libsupc++/eh_alloc.cc:97
 * extern "C" void * __cxxabiv1::__cxa_allocate_exception(std::size_t thrown_size) throw()
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stddef.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <errno.h>

#ifndef _DEBUG_
#define _DEBUG_
#endif

#ifndef DEBUG_EOL
#define DEBUG_EOL "\n"
#endif /* DEBUG_EOL */

#if HAVE_DBGFLAGS_1_LOGGERS_H
#define LOGGER consoleLogger
#include <dbgflags-1/loggers.h>
#include <dbgflags-1/debug_macros.h>
#else /* HAVE_DBGFLAGS_1_LOGGERS_H */
#include <stdio.h>
#define CRIT_MSG(fmt,...)	fprintf (stderr, "[fatal] (file: %s, line: %d) " fmt DEBUG_EOL, __FILE__, __LINE__, ##__VA_ARGS__);
#ifdef _DEBUG_
#define INFO_MSG(fmt,...)	fprintf (stderr, "[info] (file: %s, line: %d) " fmt DEBUG_EOL, __FILE__, __LINE__, ##__VA_ARGS__);
#define DEBUG_MSG(fmt,...)	fprintf (stderr, "[debug] (file: %s, line: %d) " fmt DEBUG_EOL, __FILE__, __LINE__, ##__VA_ARGS__);
#define DEBUG_VAR(x,f)          fprintf (stderr,"[debug] (file: " __FILE__ ", line: %d) in function %s: "  #x " = " f DEBUG_EOL,__LINE__,__FUNCTION__,x);
#else /* _DEBUG_ */
#define INFO_MSG(fmt,...)
#define DEBUG_MSG(fmt,...)
#define DEBUG_VAR(x,f)
#endif /*_DEBUG_*/
#endif /* HAVE_DBGFLAGS_1_LOGGERS_H */

void* (*libcpp__cxa_allocate_exception)(size_t thrown_size) = NULL;

int __attribute__((constructor)) initialize(void) {
   int error = EXIT_SUCCESS;
   char *errorMsg = NULL;

   INFO_MSG("initializing...");
   libcpp__cxa_allocate_exception = dlsym(RTLD_NEXT, "__cxa_allocate_exception");
   errorMsg = dlerror();
   if (NULL == errorMsg) {
	   DEBUG_MSG("__cxa_allocate_exception = 0x%08X",libcpp__cxa_allocate_exception);
   } else {
	   CRIT_MSG("failed to find the function __cxa_allocate_exception (%s)",errorMsg);
	   error = ENOENT;
   }
   return error;
}

#define FRAME_DEEP             0
#define FRAME_CPP_DEEP         1
#define CALLSTACK_LEVEL(x) if (__builtin_frame_address(x) != NULL) { void *caller = __builtin_return_address(x); DEBUG_MSG("### level =" #x " caller = 0x%X",caller);}
#define CALLSTACK_MAXDEEP  10

static void callstack() {
   void *array[CALLSTACK_MAXDEEP];
   char **strings;
   int i;
   const size_t size = backtrace(array, sizeof(array)/sizeof(array[0]));
   DEBUG_VAR(size,"%u");
   strings = backtrace_symbols((void *const *)array, size);

   for (i = 1; i < size; i++) {
      //if (strncmp(strings[i],"/lib",4) != 0) { /* don't print system's library lines */
      //   DEBUG_MSG ("%s", strings[i]);
      //}
	   DEBUG_MSG ("%d:\t%s",i,strings[i]);
   }
   free (strings);
}

void *__cxa_allocate_exception(size_t thrown_size) {
	//void *caller = __builtin_return_address(FRAME_DEEP);
	//void *callersParent = __builtin_return_address(FRAME_CPP_DEEP);
	//DEBUG_VAR(caller,"(" TO_STRING(FRAME_DEEP) ") 0x%08X");
	//DEBUG_VAR(callersParent,"(" TO_STRING(FRAME_CPP_DEEP) ") 0x%08X");
	//CALLSTACK_LEVEL(0);
	//CALLSTACK_LEVEL(1);
	callstack();
	return libcpp__cxa_allocate_exception(thrown_size);
}
