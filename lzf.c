/*
  +----------------------------------------------------------------------+
  | Copyright (c) The PHP Group                                          |
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_lzf.h"

#include "lzf.h"

#ifndef PHP_LZF_ULTRA_FAST
#define PHP_LZF_ULTRA_FAST 1
#endif

#if PHP_VERSION_ID < 80000
#define RETURN_THROWS() return
#include "lzf_legacy_arginfo.h"
#else
#include "lzf_arginfo.h"
#endif

/* {{{ lzf_module_entry
*/
zend_module_entry lzf_module_entry = {
	STANDARD_MODULE_HEADER,
	"lzf",
	ext_functions,
	PHP_MINIT(lzf),
	PHP_MSHUTDOWN(lzf),
	NULL,
	NULL,
	PHP_MINFO(lzf),
	PHP_LZF_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_LZF
ZEND_GET_MODULE(lzf)
#endif

/* {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(lzf)
{
	php_stream_filter_register_factory("lzf.compress", &php_lzf_compress_filter_factory);
	php_stream_filter_register_factory("lzf.decompress", &php_lzf_decompress_filter_factory);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
*/
PHP_MSHUTDOWN_FUNCTION(lzf)
{
	php_stream_filter_unregister_factory("lzf.compress");
	php_stream_filter_unregister_factory("lzf.decompress");

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(lzf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "lzf support", "enabled");
	php_info_print_table_row(2, "extension version", PHP_LZF_VERSION);
#ifdef HAVE_LIBLZF
	php_info_print_table_row(2, "liblzf version", "system");
#else
	php_info_print_table_row(2, "liblzf version", "bundled");
	#if PHP_LZF_ULTRA_FAST
	php_info_print_table_row(2, "optimized for", "speed");
	#else
	php_info_print_table_row(2, "optimized for", "compression quality");
	#endif
#endif
	php_info_print_table_end();
}
/* }}} */


/* {{{ proto string lzf_compress(string arg)
Return a string compressed with LZF */
PHP_FUNCTION(lzf_compress)
{
	char *retval, *arg = NULL;
	size_t arg_len, out_len, result;


	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		RETURN_THROWS();
	}

	if (arg_len > UINT_MAX) { /* LZF library do not support support large strings */
		RETURN_FALSE;
	}

	out_len = arg_len + MIN(UINT_MAX - arg_len, MAX(LZF_MARGIN, arg_len / 25));
	retval = emalloc(out_len);
	if (!retval) {
		RETURN_FALSE;
	}

	result = lzf_compress(arg, arg_len, retval, out_len);
	if (result == 0) {
		efree(retval);
		RETURN_FALSE;
	}

	retval[result] = 0;

	RETVAL_STRINGL(retval, result);
	efree(retval);
}
/* }}} */

/* {{{ proto string lzf_decompress(string arg)
Return a string decompressed with LZF */
PHP_FUNCTION(lzf_decompress)
{
	char *arg = NULL;
	size_t arg_len, result;
	char *buffer;
	size_t buffer_size = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		RETURN_THROWS();
	}

	do {
		if (buffer_size) {
			buffer = safe_erealloc(buffer, buffer_size, 2, 1);
			buffer_size *= 2;
		} else {
			buffer_size = (arg_len > 512 ? arg_len : 512);
			buffer = safe_emalloc(buffer_size, 2, 1);
			buffer_size *= 2;
		}

		result = lzf_decompress(arg, arg_len, buffer, buffer_size);
	} while (result == 0 && errno == E2BIG);

	if (result == 0) {
		if (errno == EINVAL) {
			php_error(E_WARNING, "%s LZF decompression failed, compressed data corrupted", get_active_function_name());
		}

		efree(buffer);
		RETURN_FALSE;
	}

	buffer[result] = 0;

	RETVAL_STRINGL(buffer, result);
	efree(buffer);
}
/* }}} */

/* {{{ proto int lzf_optimized_for()
Return 1 if lzf was optimized for speed, 0 for compression */
PHP_FUNCTION(lzf_optimized_for)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

#ifdef HAVE_LIBLZF
	RETURN_FALSE;
#else
	RETURN_LONG(PHP_LZF_ULTRA_FAST);
#endif
}

/* }}} */

/*
* Local variables:
* tab-width: 4
* c-basic-offset: 4
* End:
* vim600: noet sw=4 ts=4 fdm=marker
* vim<600: noet sw=4 ts=4
*/
