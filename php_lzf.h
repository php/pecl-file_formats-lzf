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

#ifndef PHP_LZF_H
#define PHP_LZF_H

extern zend_module_entry lzf_module_entry;
#define phpext_lzf_ptr &lzf_module_entry

extern php_stream_filter_factory php_lzf_compress_filter_factory;
extern php_stream_filter_factory php_lzf_decompress_filter_factory;

#define PHP_LZF_VERSION "1.7.0-dev"

#define LZF_MARGIN	128

PHP_MINFO_FUNCTION(lzf);
PHP_MINIT_FUNCTION(lzf);
PHP_MSHUTDOWN_FUNCTION(lzf);

#endif	/* PHP_LZF_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
