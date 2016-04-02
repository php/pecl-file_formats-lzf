--TEST--
bug70727 zend_mm_heap corrupted when uncompressed size multiple of 1024
--SKIPIF--
<?php if (!extension_loaded("lzf")) print "skip"; ?>
<?php if (!function_exists("base64_decode")) print "skip"; ?>
--FILE--
<?php
$data = 'F2E6Njp7czo4OiJiYXRjaF9pZCI7YToxNEAUEjExOiJTQ0hFTUFfTkFNRSI7TjsgFAcwOiJUQUJMRaATIBELNDoiZGF0YWZsb3dfYEVgFSA8BUNPTFVNTuAAKOAEZCA3ADXgACEMUE9TSVR' .
	'JT04iO2k6MSAaCjk6IkRBVEFfVFlQIHYHczozOiJpbnRACQA3IBkFRUZBVUxUgI4gUwNOVUxMQJAEIjtiOjAgLAg2OiJMRU5HVEiAISBlAlNDQUAeQL4gWQVQUkVDSVNgbUARIEEHVU5TSUdORU' .
	'RAQUB+IGQGUFJJTUFSWcARADEgVKAS4AisIEAGSURFTlRJVKAuAH0gLyElBnByb2ZpbGXhVFLgB2cgESDvoXfhA1UAMiAaIPvhGlUgQgI6IjBAByDY4VdbQa/hDVuhmuEDWQAwQVkglANzdG9y4' .
	'VVW4ARkIKHhDVMAMyAa4QdTQDkDbWFsbOIKriBH4ZNYIvQGYWRhcHRlcuRRAeADYyEO4Q1WADQgGuEHViA4BXZhcmNoYSCcYA3kEwRDwiOvxARkPgIxMjhACSBx5CEMQoIgeKP3RAriKa4ghwVw' .
	'YXJhbXPhUVTgAmLhEFMANSAa4QdTJbYCdGV45RtV4QZQQRfhaEhE6QhjcmVhdGVkX2EgtOZPpOAHZyARIOvlClEANiAa4QdSIA8IdGltZXN0YW1wQDoiPeIiqOFpVwF9fQ==';

echo strlen($data) . "\n";

$data = lzf_decompress(base64_decode($data));

echo strlen($data) . "\n";
?>
Done
--EXPECT--
716
2048
Done

