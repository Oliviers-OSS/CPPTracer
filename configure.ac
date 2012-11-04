dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(CppTracer,0.0.0,oliviers.open.source.softwares@gmail.com)
AM_CONFIG_HEADER([config.h])

AC_PROG_CC

AC_CANONICAL_SYSTEM

dnl Initialize automake
AM_INIT_AUTOMAKE

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 
AC_PROG_CXX
AC_PROG_RANLIB
 
AC_CHECK_HEADERS([stddef.h])
AC_TYPE_SIZE_T

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

AC_CONFIG_FILES(Makefile                
                libCppTracer/Makefile
                TestProgram/Makefile
                include/Makefile)
AC_OUTPUT