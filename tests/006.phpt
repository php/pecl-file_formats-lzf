--TEST--
lzf.compress on binary may result in larger string than input
--SKIPIF--
<?php if (!extension_loaded("lzf")) print "skip"; ?>
<?php if (!function_exists("random_bytes")) print "skip"; ?>
--FILE--
<?php
for ($i = 0 ; $i<32 ; $i++) {
	$in = random_bytes(random_int(10000,50000));
	$out = lzf_compress($in);
	if (!$out) echo "Failure\n";
}
?>
Done
--EXPECT--
Done
