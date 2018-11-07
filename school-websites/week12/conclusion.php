<!doctype html>
<html>
	<head>
		<title>Code_Space | Conclusion</title>
		<link rel='stylesheet' type='text/css' href='code_space_style.css'>
	</head>

	<body>
	<div id='content'>
		<a href="index.html">
		<img id='banner' src='codeSpace.png' alt="CODE SPACE LOGO"/>
		</a>
		<div class='navbar' id='navbar_1'>
			<a class="nav_link" id="nav_left_1"  href="../index.html" style="position: absolute; left: 0px;">< BACK TO SITE</a>
		</div>

		<?php
			if (isset($_POST["cancel"])) {
				printf("<p>Your order has been cancelled. Click <a href=\"index.html\">here</a> to return back to the site.</p>");
			} else {
				printf("Your order has been processed, have a nice day :) Click <a href=\"index.html\">here</a> to return back to the site.");
			}
		?>

		<div id='footer'>
			<p>CODE_SPACE is a non-profit organization. This website is open source, under the <a href="http://www.gnu.org/licenses/gpl-3.0.en.html">GNU Public License</a></p>
		</div>
	</div>
	<script src='code_space_script.js'></script>
	</body>
</html>

