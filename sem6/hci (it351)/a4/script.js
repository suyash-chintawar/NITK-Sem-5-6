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

function convertMass() {
	var m = {
		"kilograms": 0,
		"grams": 1,
		"ounces": 2,
		"pounds": 3
	};

	var rates = [
		[1,1000,35.274,2.204],
		[0.001,1,0.035274,0.002204],
		[0.0283495,28.3495,1,0.0625],
		[0.453592,453.592,16,1]
	];

	var fromUnit = document.getElementById("unit-from").value;
	var toUnit = document.getElementById("unit-to").value;

	var idf=m[fromUnit],idt=m[toUnit];

	document.getElementById("second").value=document.getElementById("first").value*rates[idf][idt];
}

function convertLength() {
	var m = {
		"meter": 0,
		"yard": 1,
		"foot": 2,
		"inch": 3
	};

	var rates = [
		[1,1.0936,3.2808,39.37],
		[0.9144,1,3,36],
		[0.3048,0.3333,1,12],
		[0.0254,0.0277,0.0833,1]
	];
	
	var fromUnit = document.getElementById("unit-from").value;
	var toUnit = document.getElementById("unit-to").value;

	var idf=m[fromUnit],idt=m[toUnit];

	document.getElementById("second").value=document.getElementById("first").value*rates[idf][idt];
}

function convertTime() {
	var m = {
		"seconds": 0,
		"minutes": 1,
		"milliseconds": 2,
		"hours": 3
	};

	var rates = [
		[1,0.0166,1000,0.00027],
		[60,1,60000,0,0166],
		[0.001,0.000016,1,0.00000027],
		[3600,60,3600000,1]
	];
	
	var fromUnit = document.getElementById("unit-from").value;
	var toUnit = document.getElementById("unit-to").value;

	var idf=m[fromUnit],idt=m[toUnit];

	document.getElementById("second").value=document.getElementById("first").value*rates[idf][idt];
}