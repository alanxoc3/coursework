// Java script file for the week of 06 javascript tests.
// Author: Alan Morgan

// An age regex function, give it the id for the input and output HTML tag.
function test1(inId, outId) {
   var ssRegex = /^\d\d?\d?$/g;
   var input  = document.getElementById(inId).value;
   var output = document.getElementById(outId);
	var capture = ssRegex.exec(input);
	var age;

	// Calculate Age
	if (capture != null)
		age = parseInt(capture[0]);
	else
		age = -1;

	// Display result.
   if (age >= 0 && age <= 118)
      output.innerHTML = "";
   else
      output.innerHTML = "Invalid Age";
}

// A date regex function, give it the id for the input and output HTML tag.
function test2(inId, outId) {
   var ssRegex = /^\s*\d{3}\-\d{2}\-\d{4}\s*$/g;
	var input  = document.getElementById(inId).value;
	var output = document.getElementById(outId);


	if(input.match(ssRegex) == null)
		output.innerHTML = "Invalid SSN";
	else
		output.innerHTML = "";
}

// A credit card regex function, give it the id for the input and output HTML tag.
function test3(inId, outId) {
   var ssRegex = /^\s*(\d{4} \d{4} \d{4} \d{4}|\d{4}\d{4}\d{4}\d{4})\s*$/g;
	var input  = document.getElementById(inId).value;
	var output = document.getElementById(outId);

	if(input.match(ssRegex) == null)
		output.innerHTML = "Invalid credit card number";
	else
		output.innerHTML = "";
}

// A date regex function, give it the id for the input and output HTML tag.
function test4(inId, outId) {
   var ssRegex = /^\s*(1[0-2]|0*[0-9])\/(3[01]|[012]*[0-9])\/(\d{4})\s*$/g;
	var input   = document.getElementById(inId).value;
	var output  = document.getElementById(outId);
	var capture = ssRegex.exec(input);

	if(capture == null) {
		output.innerHTML = "Invalid date";
	} else {
		// The index to the year element.
		var yearTest = parseInt(capture[3],10);
		if(yearTest < 1753 || yearTest > 2100)
			output.innerHTML = "Invalid date";
		else
			output.innerHTML = "";
	}
}

function test5(inId, outId) {
   var ssRegex = /^\s*[A-Z]{2}\s*$/g;
	var input  = document.getElementById(inId).value;
	var output = document.getElementById(outId);

	if(input.match(ssRegex) == null)
		output.innerHTML = "Invalid state abbreviation";
	else
		output.innerHTML = "";
}

// A money regex function, give it the id for the input and output HTML tag.
function test6(inId, outId) {
   var ssRegex = /^\s*\$?([1-9]\d?\d?(,?\d{3})+?|[1-9]\d*)(\.\d\d)?\s*$/g;
	var input  = document.getElementById(inId).value;
	var output = document.getElementById(outId);

	if(input.match(ssRegex) == null)
		output.innerHTML = "Invalid money amount";
	else
		output.innerHTML = "";
}
