<!DOCTYPE html>
<html>
<head>
	<title>Week 11: Problem 5</title>
</head>
<body>
	<h1>Problem 5</h1>
	<p>Here is the table of stuff! Yayy.</p>
	<table style="text-align: left; border: 3px solid black;">
	<?php

	# The numbers b stands for base.
	$b = $_POST["x"];
	$n = $_POST["n"];
	$x = $b;

	# Print the header - Randomly have this in the php part.
	printf('<tr><th>n</th><th>x^n</th></tr>');

	for ($count = 0; $count < $n;) {
		printf('<tr><td>%d</td><td>%d</td></tr>', $count + 1, $x);
		$x *= $b;
		$count++;
	}
	?>
	</table>
</body>
</html>
