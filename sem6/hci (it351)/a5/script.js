function startTime() {
	var today = new Date();
	var dd =today.getDate();
	var mm = today.getMonth()+1;
	var yyyy = today.getFullYear();
	var hr = today.getHours();
	var min = today.getMinutes();
	var sec = today.getSeconds();
	hr= check(hr);
	min= check(min);
	sec= check(sec);
	dd= check(dd);
	mm= check(mm);
	document.getElementById("time").innerHTML = dd+'/'+mm+'/'+yyyy+"  "+hr+":"+min+":"+sec;
	var t=setTimeout(startTime, 1000);
}

function check(i) {
		if (i<10) i=("0"+i);
		return i;
}
