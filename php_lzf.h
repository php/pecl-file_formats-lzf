/*
  +----------------------------------------------------------------------+
  | PHP Version 5, 7, 8                                                  |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2020 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Marcin Gibula <mg@iceni.pl>                                  |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_LZF_H
#define PHP_LZF_H

extern zend_module_entry lzf_module_entry;
#define phpext_lzf_ptr &lzf_module_entry

extern php_stream_filter_factory php_lzf_compress_filter_factory;
extern php_stream_filter_factory php_lzf_decompress_filter_factory;

#define PHP_LZF_VERSION "1.6.8"

#ifdef PHP_WIN32
#define PHP_LZF_API __declspec(dllexport)
#else
#define PHP_LZF_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define LZF_MARGIN	128

PHP_MINFO_FUNCTION(lzf);
PHP_MINIT_FUNCTION(lzf);
PHP_MSHUTDOWN_FUNCTION(lzf);

PHP_FUNCTION(lzf_compress);
PHP_FUNCTION(lzf_decompress);
PHP_FUNCTION(lzf_optimized_for);

#if PHP_MAJOR_VERSION < 7
typedef long zend_long;
typedef int strsize_t;
#define _RETVAL_STRINGL(a,l)  RETVAL_STRINGL(a,l,1)
#define Z_PTR(p) (p)
#else
typedef size_t strsize_t;
#define TSRMLS_C
#define TSRMLS_CC
#define TSRMLS_DC
#define _RETVAL_STRINGL(a,l)  RETVAL_STRINGL(a,l)
#endif

#endif	/* PHP_LZF_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
