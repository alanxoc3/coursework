<!DOCTYPE html>
<html>
<head>
	<title>Week 11: Problem 6</title>
</head>
<body>
	<h1>Problem 6</h1>
	<p>Here is the table of stuff! Yayy.</p>
	<table style="text-align: center; border: 1px dashed black;">
	<?php
	# Copy the text.
	$text = $_POST["input6"];

	# Text to array.
	$listOfItems = explode(", ", $text);

	# Print each element in their own row.
	foreach ($listOfItems as $item)
		printf('<tr><td>%s</td></tr>', $item);

	?>
	</table>
</body>
</html>
