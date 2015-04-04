--TEST--
filter lzf.compress
--SKIPIF--
<?php if (!extension_loaded("lzf")) print "skip"; ?>
<?php if (!function_exists("base64_encode")) print "skip"; ?>
--POST--
--GET--
--INI--
--FILE--
<?php
$text = "This is test of LZF extension";
$fp = fopen('php://stdout', 'w');
stream_filter_append($fp, 'lzf.compress', STREAM_FILTER_WRITE);
stream_filter_append($fp, 'convert.base64-encode', STREAM_FILTER_WRITE);
fwrite($fp, $text);
fclose($fp);
?>
--EXPECT--
WlYAAB1UaGlzIGlzIHRlc3Qgb2YgTFpGIGV4dGVuc2lvbg==
