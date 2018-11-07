<!DOCTYPE html>
<html>
<head>
	<title>Week 11: Problem 4</title>
</head>
<body>
	<h1>Problem 4</h1>
	<p>
	<?php
	# Create an array...
	$engToSpa = array("one" => "uno", "two" => "dos",
							"three" => "tres", "four" => "cuatro",
							"five" => "cinco", "six" => "seis",
							"seven" => "siete", "eight" => "ocho",
							"nine" => "nueve", "ten" => "diez",
							"eleven" => "once", "twelve" => "doce",
							"thirteen" => "trece", "fourteen" => "catorce",
							"fifteen" => "quince", "sixteen" => "dieciseis",
							"seventeen" => "diecisiete", "eighteen" => "dieciocho",
							"nineteen" => "diecinueve", "twenty" => "veinte");

	# Here is number.
	$number = $_POST["input4"];

	# If exists, then print, else, error.
	if (array_key_exists($number, $engToSpa)) {
		printf('The word "%s" in Spanish is "%s"', $number, $engToSpa[$number]);
	} else {
		printf('The English cardinal "%s" is not between "one" and "twenty"', $number);
	}
	?>
	</p>
</body>
</html>
