var num1 = document.getElementById('shirt_num');
var num2 = document.getElementById('mug_num');
var num3 = document.getElementById('tie_num');
var num4 = document.getElementById('frisbee_num');
var stuff  = document.getElementById('products');
var order  = document.getElementById('order');
var error = document.getElementById('error_text');
var nav1 = document.getElementById('navbar_1');
var nav2 = document.getElementById('navbar_2');

var total1 = document.getElementById('shirt_total');
var total2 = document.getElementById('mug_total');
var total3 = document.getElementById('tie_total');
var total4 = document.getElementById('frisbee_total');
var total = document.getElementById('all_total');

function orderProduct(outId) {
	var numPlace = document.getElementById(outId);
	numPlace.style.visibility = "visible";
}

function updatePrice(inId, outId) {
	var priceValue = document.getElementById(inId);
	var priceSpace = document.getElementById(outId);

	if (priceValue.value > 0 && priceValue.value <= 50) {
		priceSpace.innerHTML = "$10 X " + priceValue.value;
	}
	else if (priceValue.value == 0) {
		priceSpace.innerHTML = "$10";
	}
	else {
		priceSpace.innerHTML = "OUT OF RANGE";
	}
}

// Submits the number of items.
function firstSubmit() {
	var price1 = parseInt(num1.value);
	var price2 = parseInt(num2.value);
	var price3 = parseInt(num3.value);
	var price4 = parseInt(num4.value);

	var sum = price1 + price2 + price3 + price4;

	// Get out of here if the numbers are invalid.
	if (price1 < 0 || price2 < 0 || price3 < 0 || price4 < 0
    || price1 > 50 || price2 > 50 || price3 > 50 || price4 > 50) {
		error.innerHTML = "You have items that are out of range.";
		return;
	}

	if (sum == 0) {
		error.innerHTML = "You didn't order anything.";
		return;
	}

	total1.innerHTML = "$" + price1 * 10;
	total2.innerHTML = "$" + price2 * 10;
	total3.innerHTML = "$" + price3 * 10;
	total4.innerHTML = "$" + price4 * 10;

	total.innerHTML = "$" + sum * 10;

	stuff.style.display = 'none';
	order.style.display = 'block';

	nav1.style.display = 'none';
	nav2.style.display = 'block';

	error.innerHTML = " ";
}

function lastSubmit() {

}

function backToStart() {
	stuff.style.display = 'block';
	order.style.display = 'none';

	nav1.style.display = 'block';
	nav2.style.display = 'none';
}

function validateName(inId) {
	var nameRegex = /^\s*[A-Za-z]+ [A-Za-z]+$/g;
	var testName = document.getElementById(inId).value;

	if (testName.match(nameRegex) == null) {
		error.innerHTML = "Invalid name entry. Need first and last name.";
		return 1;
	} else {
		return 0;
	}
}

function validateAddress(inId) {
	// hard to really validate an address. Especially just with regex.
	var addrRegex = /^[\w\s]+$/g;
	var testAddress = document.getElementById(inId).value;

	if (testAddress.match(addrRegex) == null) {
		error.innerHTML = "Invalid address entry. Needs something.";
		return 1;
	} else {
		return 0;
	}
}

function validatePhone(inId) {
	var phoneRegex = /^\d{10}$/g;
	var testPhone = document.getElementById(inId).value;

	if (testPhone.match(phoneRegex) == null) {
		error.innerHTML = "Invalid phone number, need 10 digits.";
		return 1;
	} else {
		return 0;
	}
}

function validateCardNumber(inId) {
	var cardRegex = /^\d{16}$/g;
	var testCard = document.getElementById(inId).value;

	if (testCard.match(cardRegex) == null) {
		error.innerHTML = "Invalid card number. Change it please.";
		return 1;
	} else {
		return 0;
	}
}

function validateCardDate(inId) {
	var cardRegex = /^\d\d\/\d\d$/g;
	var testCard = document.getElementById(inId).value;

	if (testCard.match(cardRegex) == null) {
		error.innerHTML = "Invalid card date, must be MM/YY.";
		return 1;
	} else {
		return 0;
	}
}

function validateForm() {
	var sum = validatePhone('enter_phone') + validateCardNumber('card_number') + validateCardDate('card_expiration') + validateName('enter_name') + validateAddress('enter_addr');

	if (sum != 0) {
		error.innerHTML = "You still have form errors. Fix it!";
		return false;
	} else
		error.innerHTML = " ";
		return true;
		
}
