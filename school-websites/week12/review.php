<!doctype html>
<html>
	<head>
		<title>Code_Space | Review</title>
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

		<p>Here is a review of your information:</p>

		<?php
			$company = $_POST["card_company"];
			$number  = $_POST["card_number"];
			$expiration = $_POST["card_expiration"];
			$name = $_POST["enter_name"];
			$addr = $_POST["enter_addr"];
			$phone = $_POST["enter_phone"];

			# Print the stuff.
			printf('<p>Name: %s</p>', $name);
			printf('<p>Address: %s</p>', $addr);
			printf('<p>Phone: %s</p>', $phone);
			printf('<p>Card Information: %s | num: %s | exp: %s', $company, $number, $expiration);
		?>

		<form name="confirm_form" action="conclusion.php" method="post">
			<input type="submit" name="cancel" value="Cancel" />
			<input type="submit" name="submit"value="Submit" />
			<?php
			echo "<input type=\"hidden\" name=\"card_company\" value=\"$company\">";
			echo "<input type=\"hidden\" name=\"card_number\" value=\"$number\">";
			echo "<input type=\"hidden\" name=\"card_expiration\" value=\"$expiration\">";
			echo "<input type=\"hidden\" name=\"enter_name\" value=\"$name\">";
			echo "<input type=\"hidden\" name=\"enter_addr\" value=\"$addr\">";
			echo "<input type=\"hidden\" name=\"enter_phone\" value=\"$phone\">";
			?>
		</form>

		<div id='footer'>
			<p>CODE_SPACE is a non-profit organization. This website is open source, under the <a href="http://www.gnu.org/licenses/gpl-3.0.en.html">GNU Public License</a></p>
		</div>
	</div>
	<script src='code_space_script.js'></script>
	</body>
</html>

