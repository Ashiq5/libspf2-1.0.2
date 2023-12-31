#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(libspf2, 1.0.2, wayne@midwestcs.com)
AM_INIT_AUTOMAKE(libspf2, $PACKAGE_VERSION)
AC_CONFIG_SRCDIR([src/libspf2/spf.c])
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)

# remember the version info for later

major=`echo $PACKAGE_VERSION | sed 's/^\([[0-9]]*\)\.[[0-9]]*\.[[0-9]]*/\1/'`
minor=`echo $PACKAGE_VERSION | sed 's/^[[0-9]]*\.\([[0-9]]*\)\.[[0-9]]*/\1/'`
patch=`echo $PACKAGE_VERSION | sed 's/^[[0-9]]*\.[[0-9]]*\.\([[0-9]]*\)/\1/'`

cat >src/libspf2/spf_lib_version.h <<_EOF_VERSION
#ifndef INC_SPF_VERSION
#define INC_SPF_VERSION

#define SPF_LIB_VERSION_MAJOR	$major
#define SPF_LIB_VERSION_MINOR	$minor
#define SPF_LIB_VERSION_PATCH	$patch

#endif
_EOF_VERSION


# Checks for programs.
AC_PROG_CC
if test "X$ac_cv_prog_gcc" = "Xyes"; then
        gcc_ver=`gcc -v 2>&1 | grep version | sed 's/.*gcc version \([[0-9]][[0-9]]*\)\..*/\1/'`
#        echo "GCC version: $gcc_ver"
        if test "X$gcc_ver" = "X3"; then
        	CFLAGS="$CFLAGS -W -Wall -Wmissing-prototypes -Wwrite-strings"
#        	CFLAGS="$CFLAGS -std=c89 -D_BSD_SOURCE -W -Wall -Wmissing-prototypes -Wwrite-strings"
#        	CFLAGS="$CFLAGS -std=c99 -W -Wall -Wmissing-prototypes -Wwrite-strings"
#        	CFLAGS="$CFLAGS -std=gnu99 -W -Wall -Wmissing-prototypes -Wwrite-strings"
        else
        	CFLAGS="$CFLAGS -Wall"
        fi
fi
AC_PROG_CPP
AC_SUBST(SUBDIRS)
AC_PROG_MAKE_SET
AC_SUBST(LIBPROGS)
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB

# Check if the linker accepts --rpath (for Darwin)
AC_MSG_CHECKING([if ld accepts --rpath])
SAVEDLDFLAGS=$LDFLAGS
LDFLAGS=$LDFLAGS" -Wl,--rpath=/"
AC_LINK_IFELSE([AC_LANG_PROGRAM([],[])],
    [rpath="--rpath="; ldrpath=yes], [rpath="-L"; ldrpath=no])
LDFLAGS=$SAVEDLDFLAGS
AC_MSG_RESULT([$ldrpath])

AC_ARG_WITH(bind,
        [  --with-bind=DIR  Find BIND resolver in DIR],
        [AC_CHECK_FILE([$withval/include/bind/resolv.h],
                [CFLAGS="$CFLAGS -I$withval/include/bind"],
                [CFLAGS="$CFLAGS -I$withval/include"])
         LDFLAGS="$LDFLAGS -L$withval/lib -Wl,$rpath$withval/lib"
         AC_CHECK_LIB([bind], [res_query], [LIBS="$LIBS -lbind"],
                [AC_CHECK_LIB([resolv],
                        [res_query],
                        [LIBS="$LIBS -lresolv"],
                        [echo "cannot find resolver library"; exit 1;])
                ])
        ], [AC_CHECK_LIB(resolv, res_query)])


# Checks for libraries.
AC_CHECK_LIB(nsl, inet_pton)
AC_CHECK_LIB(socket, socket)
AC_CHECK_LIB(intl, gettext)

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_HEADER_TIME
AC_CHECK_HEADERS([netinet/in.h sys/socket.h syslog.h sys/time.h errno.h sys/types.h])
AC_CHECK_HEADERS([netdb.h arpa/inet.h arpa/nameser.h])
AC_CHECK_HEADERS([syslog.h])
AC_CHECK_HEADERS([resolv.h], [], [],
      [[#if HAVE_SYS_TYPES_H
	#  include <sys/types.h>
	#endif
	#ifdef HAVE_NETINET_IN_H
	#  include <netinet/in.h>   /* inet_ functions / structs */
	#endif
	#ifdef HAVE_ARPA_NAMESER_H
	#  include <arpa/nameser.h> /* DNS HEADER struct */
	#endif
	#ifdef HAVE_SYS_SOCKET_H
	#  include <sys/socket.h> /* DNS HEADER struct */
	#endif
     ]])
AC_CHECK_HEADERS([fcntl.h malloc.h nmemory.h stddef.h inttypes.h stdlib.h string.h syslog.h unistd.h stdarg.h])
AC_CHECK_HEADERS([libintl.h ])
AC_CHECK_HEADERS([getopt.h ])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_C_VOLATILE
AC_C_BIGENDIAN
AC_C_INLINE
AC_C_CHAR_UNSIGNED
AC_CHECK_TYPES([u_char, u_int8_t, u_int16_t, u_int32_t, uint8_t, uint16_t, uint32_t])
AC_CHECK_TYPES([ns_type], [], [],
	[[
	#ifdef HAVE_SYS_SOCKET_H
	# include <sys/socket.h>		/* inet_ functions / structs */
	#endif
	#ifdef HAVE_NETINET_IN_H
	# include <netinet/in.h>		/* inet_ functions / structs */
	#endif
	#ifdef HAVE_ARPA_NAMESER_H
	#  include <arpa/nameser.h> /* DNS HEADER struct */
	#endif
	]])
AC_CHECK_TYPES([struct in6_addr], [], [],
	[[
	#ifdef HAVE_NETINET_IN_H
	#  include <netinet/in.h>   /* inet_ functions / structs */
	#endif
	]])

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_FUNC_SETPGRP
AC_TYPE_SIGNAL


# It is not clear if BIND8 and/or BIND9 require the use of the
# res_ninit() and res_nquery() functions when threading, but it is
# safest to use them.

AC_CHECK_DECLS([res_ninit], [], [], [[
	#ifdef HAVE_SYS_SOCKET_H
	# include <sys/socket.h>		/* inet_ functions / structs */
	#endif
	#ifdef HAVE_NETINET_IN_H
	# include <netinet/in.h>		/* inet_ functions / structs */
	#endif
	#ifdef HAVE_ARPA_NAMESER_H
	#  include <arpa/nameser.h> /* DNS HEADER struct */
	#endif
	#include <resolv.h>
	]])

AC_CHECK_FUNCS([ftruncate gethostname memmove memset socket strcasecmp strchr strcspn strdup strerror strncasecmp strspn strtoul])
AC_REPLACE_FUNCS([getopt_long_only])
AC_REPLACE_FUNCS([__ns_initparse __ns_name_uncompress __ns_get16 __ns_msg_getflag])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/include/Makefile
                 src/libreplace/Makefile
                 src/libspf2/Makefile
                 src/spfquery/Makefile
                 src/spftest/Makefile
                 src/spfd/Makefile
                 src/spf_example/Makefile
                 docs/Makefile
                 tests/Makefile])
AC_OUTPUT
