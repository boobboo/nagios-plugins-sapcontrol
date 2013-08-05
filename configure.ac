AC_INIT([nagios-plugins-sapcontrol], [1.0], [dlittle@toyatech.net])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_CC_C_O

AC_PATH_PROG([WSDL2H], [wsdl2h])
AC_PATH_PROG([SOAPCPP2], [soapcpp2])

PKG_CHECK_MODULES([GSOAP], [gsoap])

np_srcdir=""
AC_ARG_WITH([nagios_plugins],
  [AS_HELP_STRING([--with-nagios-plugins=DIR],
    [Specifies the Nagios plugins source directory @<:@default=check@:>@])],
  [np_srcdir=$withval],
  [with_nagios_plugins=check])

if test "x$with_nagios_plugins" = xcheck; then
  if test -d "../nagios-plugins"; then
    np_srcdir="../nagios-plugins"
  fi
fi

AM_PATH_XML2(2.4.0)

AC_SUBST([np_srcdir])
AC_SUBST([DEPLIBS])

AC_C_CONST
AC_STRUCT_TM
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SIGNAL

AC_TRY_COMPILE([#include <sys/time.h>],
               [struct timeval *tv;
                struct timezone *tz;],
               AC_DEFINE(HAVE_STRUCT_TIMEVAL,1,[Define if we have a timeval structure])
               AC_TRY_COMPILE([#include <sys/time.h>],
                              [struct timeval *tv;
                               struct timezone *tz;
                               gettimeofday(tv, tz);],
                              AC_DEFINE(HAVE_GETTIMEOFDAY,1,[Define if gettimeofday is found]),
                              AC_DEFINE(NEED_GETTIMEOFDAY,1,[Define if gettimeofday is needed])))

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  plugins/Makefile
])
AC_OUTPUT
