##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
m4_define([v_maj], [0])
m4_define([v_min], [9])
m4_define([v_mic], [99])
m4_define([v_rev], m4_esyscmd([(svnversion "${SVN_REPO_PATH:-.}" | grep -v export || echo 0) | awk -F : '{printf("%s\n", $1);}' | tr -d ' :MSP\n']))
m4_if(v_rev, [0], [m4_define([v_rev], m4_esyscmd([git log 2> /dev/null | (grep -m1 git-svn-id || echo 0) | sed -e 's/.*@\([0-9]*\).*/\1/' | tr -d '\n']))])
##--   When released, remove the dnl on the below line
dnl m4_undefine([v_rev])
##--   When doing snapshots - change soname. remove dnl on below line
m4_define([relname], [ver-svn-06])
m4_define([v_rel], [-release relname])
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
m4_ifdef([v_rev], [m4_define([v_ver], [v_maj.v_min.v_mic.v_rev])],
[m4_define([v_ver], [v_maj.v_min.v_mic])])
m4_define([lt_rev], m4_eval(v_maj + v_min))
m4_define([lt_cur], v_mic)
m4_define([lt_age], v_min)
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##

AC_INIT([edje], [v_ver], [enlightenment-devel@lists.sourceforge.net])
AC_PREREQ([2.52])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_ISC_POSIX

AM_INIT_AUTOMAKE([1.6 dist-bzip2])
AM_CONFIG_HEADER([config.h])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_LIBTOOL_WIN32_DLL
define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
AC_PROG_LIBTOOL

##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
m4_ifdef([v_rev], , [m4_define([v_rev], [0])])
m4_ifdef([v_rel], , [m4_define([v_rel], [])])
AC_DEFINE_UNQUOTED(VMAJ, [v_maj], [Major version])
AC_DEFINE_UNQUOTED(VMIN, [v_min], [Minor version])
AC_DEFINE_UNQUOTED(VMIC, [v_mic], [Micro version])
AC_DEFINE_UNQUOTED(VREV, [v_rev], [Revison])
version_info="lt_rev:lt_cur:lt_age"
release_info="v_rel"
AC_SUBST(version_info)
AC_SUBST(release_info)
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##

AC_DEFINE_UNQUOTED([SHARED_LIB_SUFFIX], ["$shrext_cmds"], [Suffix for shared objects])

EFL_CHECK_PATH_MAX

### Default options with respect to host

case "$host_os" in
   mingw32ce* | cegcc*)
      install_vim="no"
      have_edje_cc="no"
      ;;
   *)
      install_vim="yes"
      have_edje_cc="yes"
      ;;
esac

requirement_edje=""


### Additional options to configure

AC_ARG_ENABLE([amalgamation],
   [AC_HELP_STRING([--enable-amalgamation], [enable generation of one single file with all source code in it, helps compiler optimizations.])],
   [if test "x${enableval}" = "xyes"; then
       do_amalgamation="yes"
    else
       do_amalgamation="no"
    fi
   ],
   [do_amalgamation="no"]
)
AM_CONDITIONAL([EDJE_AMALGAMATION], [test "x${do_amalgamation}" = "xyes"])

EFL_ENABLE_BIN([edje-cc])
EFL_ENABLE_BIN([edje-decc])
EFL_ENABLE_BIN([edje-recc])
EFL_ENABLE_BIN([edje-player])

# Optional EDJE_PROGRAM_CACHE (use much more ram, but increase speed in some cases)
want_edje_program_cache="no"

AC_ARG_ENABLE([edje-program-cache],
   [AC_HELP_STRING(
       [--enable-edje-program-cache],
       [enable EDJE_PROGRAM_CACHE support. [[default=disabled]]]
    )],
   [want_edje_program_cache=$enableval]
)
AM_CONDITIONAL([EDJE_PROGRAM_CACHE], [test "x${want_edje_program_cache}" = "xyes"])

if test "x${want_edje_program_cache}" = "xyes" ; then
   AC_DEFINE([EDJE_PROGRAM_CACHE], [1], [Cache result of program glob matches - this uses up extra ram with the gain of faster program matching])
fi

# Optional EDJE_CALC_CACHE (use more ram, but increase speed by reducing the need to recalculate static stuff)
want_edje_calc_cache="yes"

AC_ARG_ENABLE([edje-calc-cache],
   [AC_HELP_STRING(
       [--enable-edje-calc-cache],
       [enable EDJE_CALC_CACHE support. [[default=disabled]]]
    )],
   [want_edje_calc_cache=$enableval]
)
AM_CONDITIONAL([EDJE_CALC_CACHE], [test "x${want_edje_calc_cache}" = "xyes"])

if test "x${want_edje_calc_cache}" = "xyes" ; then
   AC_DEFINE([EDJE_CALC_CACHE], [1], [Cache result of edje_part_recalc - this uses up extra ram with the gain of reducing CPU usage when edje object are not resized])
fi

# Enable Fixed Point use
want_fixed_point="no"

AC_ARG_ENABLE([fixed-point],
   [AC_HELP_STRING(
       [--enable-fixed-point],
       [reduce use of FPU by using Fixed Point provided by Eina and Eet, [[default=disabled]]]
    )],
    [want_fixed_point=$enableval]
)
AM_CONDITIONAL([BUILD_EDJE_FP], [test "x${want_fixed_point}" = "xyes"])

if test "x${want_fixed_point}" = "xyes" ; then
   AC_DEFINE([BUILD_EDJE_FP], [1], [Use Fixed Point instead of FPU])
fi

install_vim="yes"
AC_ARG_WITH([vim],
    [AC_HELP_STRING([--with-vim=DIR], [Location of Vim data files [[autodetect]]])],
    [
     if test -d "${withval}"; then
        vimdir="${withval}"
     fi
    ]
)

if test "x${vimdir}" = "x" ; then
   if test -d "${prefix}/share/vim"; then
      vimdir="${prefix}/share/vim"
   elif test -d "/usr/share/vim"; then
      vimdir="/usr/share/vim"
   elif test -d "/usr/local/share/vim"; then
      vimdir="/usr/local/share/vim"
   elif test -d "/opt/share/vim"; then
      vimdir="/opt/share/vim"
   else
      install_vim="no"
   fi
fi

AC_MSG_CHECKING([for location of Vim data files])

if test "${install_vim}" = "yes"; then
   AC_MSG_RESULT([$vimdir])
else
   AC_MSG_RESULT([Not found, EDC syntax file will not be installed])
fi

AC_SUBST(vimdir)

### Checks for programs
AC_PROG_CC

# doxygen program for documentation building

EFL_CHECK_DOXYGEN([build_doc="yes"], [build_doc="no"])

# python

AM_PATH_PYTHON([2.5], , [:])
AM_CONDITIONAL([HAVE_PYTHON], [test "$PYTHON" != : ])

# pkg-config

PKG_PROG_PKG_CONFIG

# Check whether pkg-config supports Requires.private

if $PKG_CONFIG --atleast-pkgconfig-version 0.22; then
   pkgconfig_requires_private="Requires.private"
else
   pkgconfig_requires_private="Requires"
fi
AC_SUBST(pkgconfig_requires_private)


### Checks for libraries

# Evil library for compilation on Windows

EFL_EDJE_BUILD=""
case "$host_os" in
   mingw* | cegcc*)
      PKG_CHECK_MODULES([EVIL], [evil])
      AC_DEFINE([HAVE_EVIL], [1], [Set to 1 if Evil library is installed])
      requirement_edje="evil ${requirement_edje}"
      EFL_EDJE_BUILD="-DEFL_EDJE_BUILD"
   ;;
esac
AC_SUBST(EFL_EDJE_BUILD)

# Dependencies for the library

# Lua pkg-config hack for different naming conventions
have_lua="yes"
requirement_lua=""
lua_libs=""
PKG_CHECK_MODULES([LUA], [lua >= 5.1.0], requirement_lua="lua",
   [PKG_CHECK_MODULES([LUA], [lua5.1 >= 5.1.0], requirement_lua="lua5.1",
      [PKG_CHECK_MODULES([LUA], [lua-5.1 >= 5.1.0], requirement_lua="lua-5.1",
         [PKG_CHECK_MODULES([LUA], [lua51 >= 5.1.0], requirement_lua="lua51",
            [have_lua="no"])])])])

if test "x${have_lua}" = "xno" ; then
   AC_MSG_CHECKING([whether lua_newstate() is in liblua])
   AC_CHECK_LIB([lua], [lua_newstate],
      [
       have_lua="yes"
       lua_libs="-llua"
      ],
      [have_lua="no"])
   AC_MSG_RESULT([${have_lua}])
fi
AC_SUBST(lua_libs)

if test "x${have_lua}" = "xno" ; then
   AC_MSG_ERROR([Cannot find lua library. Be sure that you have installed it and set CFLAGS and LDFLAGS correctly])
fi

PKG_CHECK_MODULES([EDJE],
   [
    eina-0
    eet >= 1.2.3
    evas >= 0.9.9
    ecore >= 0.9.9
    ecore-file >= 0.9.9
    embryo >= 0.9.1
   ])

EDJE_LIBS="${EDJE_LIBS} ${LUA_LIBS} ${lua_libs}"
EDJE_CFLAGS="${EDJE_CFLAGS} ${LUA_CFLAGS}"

requirement_edje="embryo ecore evas eet eina-0 ${requirement_edje}"
requirement_edje="${requirement_lua} ${requirement_edje}"

have_ecore_imf="no"
PKG_CHECK_MODULES([ECORE_IMF],
   [
    ecore-imf >= 0.9.9
    ecore-imf-evas >= 0.9.9
   ],
   [
    AC_DEFINE([HAVE_ECORE_IMF], [1], [Input Method Support for Edje Entry])
    have_ecore_imf="yes"
    requirement_edje="ecore-imf-evas ecore-imf ${requirement_edje}"
   ],
   [have_ecore_imf="no"])

# Dependencies for the binaries

if test "x$have_edje_cc" = "xyes"; then
   PKG_CHECK_MODULES([ECORE_FILE], [ecore-file >= 0.9.9])
   PKG_CHECK_MODULES([ECORE_EVAS], [ecore-evas >= 0.9.9])
fi

if test "x$have_edje_player" = "xyes"; then
   PKG_CHECK_MODULES([ECORE_EVAS], [ecore-evas >= 0.9.9])
fi


### Checks for header files
AC_CHECK_HEADERS([locale.h])


### Checks for types


### Checks for structures


### Checks for compiler characteristics
AM_PROG_CC_C_O
AC_C_CONST
AC_PROG_CC_STDC
AC_HEADER_STDC
AC_C___ATTRIBUTE__

case "$host_os" in
   mingw32ce*)
      EDJE_CFLAGS="${EDJE_CFLAGS} -D_WIN32_WCE=0x0420"
      ;;
   cegcc*)
      EDJE_CFLAGS="${EDJE_CFLAGS} -mwin32 -D_WIN32_WCE=0x0420"
      ;;
esac


### Checks for linker characteristics

lt_enable_auto_import=""
case "$host_os" in
   mingw* | cegcc*)
      lt_enable_auto_import="-Wl,--enable-auto-import"
      ;;
esac
AC_SUBST(lt_enable_auto_import)


### Checks for library functions
AC_FUNC_ALLOCA

case "$host_os" in
   mingw* | cegcc*)
      AC_DEFINE([HAVE_REALPATH], [1], [Define to 1 if you have the `realpath' function.])
      ;;
   *)
      AC_CHECK_FUNCS([realpath])
      ;;
esac


AC_SUBST(requirement_edje)

AC_OUTPUT([
edje.pc
edje.spec
Makefile
data/Makefile
data/include/Makefile
doc/Makefile
doc/edje.dox
src/Makefile
src/lib/Makefile
src/bin/Makefile
utils/Makefile
])


#####################################################################
## Info

echo
echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE $VERSION"
echo "------------------------------------------------------------------------"
echo
echo "Configuration Options Summary:"
echo
echo "  Amalgamation.........: ${do_amalgamation}"
echo "  Ecore IMF............: $have_ecore_imf"
echo "  EDJE_PROGRAM_CACHE...: $want_edje_program_cache"
echo "  EDJE_CALC_CACHE......: $want_edje_calc_cache"
echo "  Fixed point..........: $want_fixed_point"
echo
echo "  Build edje_cc........: $have_edje_cc"
echo "  Build edje_decc......: $have_edje_decc"
echo "  Build edje_recc......: $have_edje_recc"
echo "  Build edje_player....: $have_edje_player"
echo
echo "  Documentation........: ${build_doc}"
echo
echo "Compilation............: make (or gmake)"
echo "  CPPFLAGS.............: $CPPFLAGS"
echo "  CFLAGS...............: $CFLAGS"
echo "  LDFLAGS..............: $LDFLAGS"
echo
echo "Installation...........: make install (as root if needed, with 'su' or 'sudo')"
echo "  prefix...............: $prefix"
echo
