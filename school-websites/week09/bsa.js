function toggleRow(rid, curid) {
	var row = document.getElementById(rid);

	if (row.style.visibility == "collapse") {
		row.style.visibility = "visible";
	}
	else {
		row.style.visibility = "collapse";
	}
}
