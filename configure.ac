m4_define([fun_major_version],[0])
m4_define([fun_minor_version],[0])
m4_define([fun_micro_version],[1])
m4_define([fun_version],[fun_major_version.fun_minor_version.fun_micro_version])

AC_INIT([fun], m4_esyscmd_s(echo $(git describe)$(git status --porcelain | awk '{if ($1 == "M") {print "-wip";exit}}')), [ctor@pknanme.com])

AC_CANONICAL_HOST

WINDOWS_FLAGS=""
case "${host_os}" in
	cygwin*|mingw*)
		WINDOWS_FLAGS="-lmingw32 -lSDL2main"
		;;
esac

AC_CONFIG_MACRO_DIR([autoconf-archive/m4])
AC_ENABLE_SHARED
AC_DISABLE_STATIC
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC
AM_PROG_AR
LT_INIT

# -Wunsafe-loop-optimizations 
AC_SUBST([AM_CFLAGS], ["-std=c11 -v -g -O -Wextra -Wfloat-equal -Wunused -Wall -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wunreachable-code -Wno-unused-function -Wno-cpp -Werror -pedantic -pedantic-errors -Waggregate-return -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization -Wformat -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimplicit -Wimport -Winit-self -Winline -Winvalid-pch -Wlong-long -Wmissing-braces -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpadded -Wparentheses -Wredundant-decls -Wreturn-type -Wsequence-point -Wsign-compare -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch -Wswitch-default -Wswitch-enum -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunreachable-code -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable -Wvariadic-macros -Wvolatile-register-var -Wwrite-strings ${WINDOWS_FLAGS}"])

FUN_API_VERSION=0.1.0
FUN_API_MAJOR_VERSION=0
FUN_API_MINOR_VERSION=1

AC_SUBST([FUN_API_VERSION])
AC_SUBST([FUN_API_MAJOR_VERSION])
AC_SUBST([FUN_API_MINOR_VERSION])
AC_SUBST([FUN_API_VERSION_U],[AS_TR_SH([$FUN_API_VERSION])])

# ===========================================================================

AC_SUBST([FUN_LT_VERSION_INFO],[fun_lt_version_info])
AC_SUBST([LIBFUN_MAJOR_VERSION],[fun_major_version])
AC_SUBST([LIBFUN_MINOR_VERSION],[fun_minor_version])
AC_SUBST([LIBFUN_MICRO_VERSION],[fun_micro_version])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
                 Makefile
                 src/Makefile
                 ])

AC_CHECK_TYPES(long long) 

AC_OUTPUT

