<?php

if ($_SERVER['argc'] <= 2 || ($_SERVER['argv'][1]!='-c' && $_SERVER['argv'][1]!='-d')) {
	echo "\nusage lzf.php -c file     [ file.lzf ]\n";
	echo "usage lzf.php -d file.laf [ file ]\n\n";
	exit(0);
}

if ($_SERVER['argv'][1]=='-c') {
	$in  = $_SERVER['argv'][2];
	$out = ($_SERVER['argc']>3 ? $_SERVER['argv'][3] : $in.'.lzf');

	$data = file_get_contents($in);
	if (!$data) {
		die("Can't read $in\n");
	}
	printf("Read  %10d from %s\n", $old=strlen($data), $in);

	$time = microtime(true);
	$data = lzf_compress($data);
	$time = microtime(true) - $time;

	if ($len=file_put_contents($out, $data)) {
		printf("Write %10ld to %s\n", $len, $out);
		printf("Saved %d%% in %.4f\"\n", ($old-$len)*100/$old, $time);
	}

} else {
	$in  = $_SERVER['argv'][2];
	if ($_SERVER['argc']>3) {
		$out =  $_SERVER['argv'][3];
	} else if (substr($in, -4)=='.lzf') {
		$out = substr($in, 0, -4);
	} else {
		die("Missing output file name\n");
	}
	$data = file_get_contents($in);
	if (!$data) {
		die("Can't read $in\n");
	}
	printf("Read  %10d from %s\n", $old=strlen($data), $in);

	$time = microtime(true);
	$data = lzf_decompress($data);
	$time = microtime(true) - $time;

	if ($len=file_put_contents($out, $data)) {
		printf("Write %10ld to %s\n", $len, $out);
		printf("Done in %.4f\"\n", $time);
	}
}

