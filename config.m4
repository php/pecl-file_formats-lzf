dnl $Id$
dnl config.m4 for extension lzf

PHP_ARG_ENABLE(lzf, whether to enable lzf support,
[  --enable-lzf           Enable lzf support])

PHP_ARG_ENABLE(lzf-better-compression, whether to sacrifice speed in favour of compression ratio,
[  --enable-lzf-better-compression      Sacrifice speed in favour of compression ratio], no, no)

if test "$PHP_LZF" != "no"; then
  if test "$PHP_LZF_BETTER_COMPRESSION" != "yes"; then
	AC_DEFINE(ULTRA_FAST,1,[ ])
  else
    AC_DEFINE(ULTRA_FAST,0,[ ])
  fi

  PHP_NEW_EXTENSION(lzf, lzf.c lzf_c.c lzf_d.c, $ext_shared)
fi
