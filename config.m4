dnl $Id$
dnl config.m4 for extension lzf

PHP_ARG_ENABLE(lzf, whether to enable lzf support,
[  --enable-lzf            Enable lzf support])

PHP_ARG_ENABLE(lzf-better-compression, whether to sacrifice speed in favour of compression ratio,
[  --enable-lzf-better-compression      Sacrifice speed in favour of compression ratio], no, no)

PHP_ARG_WITH(liblzf, Use system liblzf,
[  --with-liblzf[=DIR]       Use system liblzf], no, no)

if test "$PHP_LZF" != "no"; then
  if test "$PHP_LZF_BETTER_COMPRESSION" != "yes"; then
    AC_DEFINE(PHP_LZF_ULTRA_FAST,1,[ ])
  else
    AC_DEFINE(PHP_LZF_ULTRA_FAST,0,[ ])
  fi

  if test "$PHP_LIBLZF" != "no"; then
    AC_MSG_CHECKING(for liblzf)
    for i in $PHP_LIBLZF /usr/local /usr; do
      if test -r $i/include/lzf.h; then
        LIBLZF_CFLAGS="-I$i/include"
        LIBLZF_LIBDIR="$i/$PHP_LIBDIR"
        AC_MSG_RESULT(found in $i)
        break
      fi
    done
    if test -z "$LIBLZF_LIBDIR"; then
      AC_MSG_RESULT(not found)
      AC_MSG_ERROR(Please reinstall the liblzf distribution)
    fi
    PHP_CHECK_LIBRARY(lzf, lzf_compress,
    [
      PHP_ADD_LIBRARY_WITH_PATH(lzf, $LIBLZF_LIBDIR, LZF_SHARED_LIBADD)
      AC_DEFINE(HAVE_LIBLZF,1,[ ])
    ], [
      AC_MSG_ERROR(could not find usable liblzf)
    ], [
      -L$LIBLZF_LIBDIR
    ])
    PHP_NEW_EXTENSION(lzf, lzf.c filter.c, $ext_shared)
    PHP_SUBST(LZF_SHARED_LIBADD)

  else
    PHP_NEW_EXTENSION(lzf, lzf.c lib/lzf_c.c lib/lzf_d.c filter.c, $ext_shared)
    PHP_ADD_BUILD_DIR($ext_builddir/lib, 1)
    PHP_ADD_INCLUDE([$ext_srcdir/lib])
  fi
fi
