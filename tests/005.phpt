--TEST--
filter lzf.decompress
--SKIPIF--
<?php if (!extension_loaded("lzf")) print "skip"; ?>
<?php if (!function_exists("base64_encode")) print "skip"; ?>
--XFAIL--
Decompress filter is not implemented
--POST--
--GET--
--INI--
--FILE--
<?php
$text = "WlYAAB1UaGlzIGlzIHRlc3Qgb2YgTFpGIGV4dGVuc2lvbg==";
$fp = fopen('php://stdout', 'w');
stream_filter_append($fp, 'convert.base64-decode', STREAM_FILTER_WRITE);
stream_filter_append($fp, 'lzf.decompress', STREAM_FILTER_WRITE);
fwrite($fp, $text);
fclose($fp);
?>
--EXPECT--
This is test of LZF extension
