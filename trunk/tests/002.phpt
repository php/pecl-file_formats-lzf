--TEST--
lzf_compress()
--SKIPIF--
<?php if (!extension_loaded("lzf")) print "skip"; ?>
<?php if (!function_exists("base64_encode")) print "skip"; ?>
--POST--
--GET--
--INI--
--FILE--
<?php
$compressed = lzf_compress("This is test of LZF extension");

echo base64_encode($compressed);
?>
--EXPECT--
BFRoaXMgIAIUdGVzdCBvZiBMWkYgZXh0ZW5zaW9u
