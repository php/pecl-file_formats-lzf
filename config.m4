dnl $Id$
dnl config.m4 for extension lzf

PHP_ARG_ENABLE(lzf, whether to enable lzf support,
[  --enable-lzf           Enable lzf support])

if test "$PHP_LZF" != "no"; then
  PHP_NEW_EXTENSION(lzf, lzf.c lzf_c.c lzf_d.c, $ext_shared)
fi
