/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: cafc352823f0a71f7df7acaca7ac7dbedfd6bcad */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_lzf_compress, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, string, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_lzf_decompress arginfo_lzf_compress

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_lzf_optimized_for, 0, 0, MAY_BE_LONG|MAY_BE_FALSE)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(lzf_compress);
ZEND_FUNCTION(lzf_decompress);
ZEND_FUNCTION(lzf_optimized_for);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(lzf_compress, arginfo_lzf_compress)
	ZEND_FE(lzf_decompress, arginfo_lzf_decompress)
	ZEND_FE(lzf_optimized_for, arginfo_lzf_optimized_for)
	ZEND_FE_END
};
