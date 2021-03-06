#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Generic support for FLTK applications

AC_COPYRIGHT([Copyright (C) 2009 Dave Freese, W1HKJ (w1hkj AT w1hkj DOT com)])

AC_PREREQ([2.63])

dnl major and minor must be integers; patch may
dnl contain other characters or be empty
m4_define(FLIMG_MAJOR,  [2])
m4_define(FLIMG_MINOR,  [2])
m4_define(FLIMG_PATCH,  [.03])

AC_INIT([FLIMG], FLIMG_MAJOR.FLIMG_MINOR[]FLIMG_PATCH, [w1hkj AT w1hkj DOT com])

AC_SUBST([FLIMG_VERSION_MAJOR], [FLIMG_MAJOR])
AC_SUBST([FLIMG_VERSION_MINOR], [FLIMG_MINOR])
AC_SUBST([FLIMG_VERSION_PATCH], [FLIMG_PATCH])
AC_SUBST([FLIMG_VERSION], [FLIMG_MAJOR.FLIMG_MINOR[]FLIMG_PATCH])

AC_DEFINE([FLIMG_VERSION_MAJOR], [FLIMG_MAJOR], [major version number])
AC_DEFINE([FLIMG_VERSION_MINOR], [FLIMG_MINOR], [minor version number])
AC_DEFINE([FLIMG_VERSION_PATCH], ["FLIMG_PATCH"], [patch/alpha version string])
AC_DEFINE([FLIMG_VERSION], ["FLIMG_MAJOR.FLIMG_MINOR[]FLIMG_PATCH"], [version string])

AC_SUBST([AC_CONFIG_ARGS], [$ac_configure_args])
AC_CONFIG_AUX_DIR([build-aux])

# define build, build_cpu, build_vendor, build_os
AC_CANONICAL_BUILD
# define host, host_cpu, host_vendor, host_os
AC_CANONICAL_HOST
# define target, target_cpu, target_vendor, target_os
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([-Wall foreign std-options subdir-objects 1.9.6])

#change the next config item for the specific application src's
AC_CONFIG_SRCDIR([src/flimg.cxx])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_USE_SYSTEM_EXTENSIONS

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([getaddrinfo gethostbyname hstrerror memmove memset mkdir select setenv snprintf socket socketpair strcasecmp strcasestr strchr strdup strerror strlcpy strncasecmp strrchr strstr strnlen strtol uname unsetenv vsnprintf])

### static flag
# Set ac_cv_static to yes/no
# Substitute RTLIB in Makefile
AC_FL_STATIC

### optimizations
# Set ac_cv_opt to arg
# Substitute OPT_FLAGS in Makefile
AC_FL_OPT

### debug flag
# Set ac_cv_debug to yes/no
# Override CXXFLAGS
# Set ENABLE_DEBUG Makefile conditional
# Substitute RDYNAMIC in Makefile
AC_FL_DEBUG

###### OS support
### OSX
# Set ac_cv_mac_universal to yes/no
# Set DARWIN Makefile conditional
# Substitute MAC_UNIVERSAL_CFLAGS and MAC_UNIVERSAL_LDFLAGS in Makefile
AC_FL_MACOSX

### win32
# Set WIN32 Makefile conditional
# Set HAVE_WINDRES Makefile conditional
# Substitute WINDRES in Makefile
AC_FL_WIN32

### Non-POSIX compatibility (i.e. mingw32)
# Sets various Makefile conditionals; see m4/np-compat.m4
AC_FLIMG_NP_COMPAT

### FLTK
# Substitute FLTK_CFLAGS and FLTK_LIBS in Makefile
# Set FLUID variable
# Set HAVE_FLUID Makefile conditional
AC_CHECK_FLTK

### XML-RPC library
# Set ac_cv_xmlrpc to yes/no
# Substitute XMLRPC_CFLAGS and XMLRPC_LIBS in Makefile
# Define USE_XMLRPC in config.h
# Set ENABLE_XMLRPC Makefile conditional
#AC_FLIMG_XMLRPC


### X11
# Set ac_cv_x to yes/no
# Define USE_X in config.h
# Substitute X_CFLAGS and X_LIBS in Makefile
if test "x$target_darwin" = "xno" && test "x$target_win32" = "xno"; then
    AC_FLIMG_PKG_CHECK([x], [x11], [no], [yes])
fi

### asciidoc
# substitute ASCIIDOC and A2X in doc/Makefile
# set HAVE_ASCIIDOC Makefile conditional
#AC_FLIMG_DOCS

### libflxmlrpc
# Set ac_cv_flxmlrpc to yes/no
# Define USE_FLXMLRPC in config.h
# Substitute FLXMLRPC_CFLAGS and FLXMLRPC_LIBS in Makefile

AC_FLIMG_PKG_CHECK([flxmlrpc], [flxmlrpc >= 0.1.0],
  [yes], [yes], [use external flxmlrpc library @<:@autodetect@:>@],
  [ENABLE_FLXMLRPC])

### build info
# Define various build variables in config.h
AC_FLIMG_BUILD_INFO

#AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile])
AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT

### summary
AC_MSG_RESULT([
Configuration summary:

  Version ..................... $VERSION

  Target OS ................... $target_os

  Have flxmlrpc library ....... $ac_cv_flxmlrpc

  Static linking .............. $ac_cv_static
  CPU optimizations ........... $ac_cv_opt
  Debugging ................... $ac_cv_debug

])
