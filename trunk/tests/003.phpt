--TEST--
lzf_decompress()
--SKIPIF--
<?php if (!extension_loaded("lzf")) print "skip"; ?>
<?php if (!function_exists("base64_decode")) print "skip"; ?>
--POST--
--GET--
--INI--
--FILE--
<?php
$decompressed = lzf_decompress(base64_decode("BFRoaXMgIAIUdGVzdCBvZiBMWkYgZXh0ZW5zaW9u"));

echo $decompressed;
?>
--EXPECT--
This is test of LZF extension
