function eucDistance(a, b) {
    return Math.round(a
        .map((x, i) => Math.abs( x - b[i] ) ** 2) 
        .reduce((sum, now) => sum + now) 
        ** (1/2))
}

var counter = 0;
var prev_radius = 75;
var prev_left = 250;
var prev_top = 10;
var parameter_list = [];
var distance = eucDistance([0,0], [prev_left,prev_top]);
var params = [1, distance, 2*prev_radius];
var d = new Date();
var prev_time = d.getTime();


function startGame() {
    window.location.href="game.html";
}

function getRndInteger(min, max) {
    return Math.floor(Math.random() * (max - min)) + min;
  }

function getRandomColor() {
    var letters = '0123456789ABCDEF';
    var color = '#';
    for (var i = 0; i < 6; i++) {
        color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
}

function next() {
    var timer = new Date();
    var time = timer.getTime();
    params.push(time-prev_time);
    prev_time=time;
    console.log(params);
    parameter_list.push(params);

    counter+=1;
    if(counter>=30)
    {
        sessionStorage.setItem("parameter_list", JSON.stringify(parameter_list));
        window.location.href = "results.html";
        return;
    }

    r = getRndInteger(30,200);
    var h = r + "px";
    var w=h;
    document.getElementById("btn").style.height=h;
    document.getElementById("btn").style.width=w;
    l = getRndInteger(10,1500);
    document.getElementById("btn").style.left=l+"px";
    t = getRndInteger(10,350);
    document.getElementById("btn").style.top=t+"px";
    color = getRandomColor();
    document.getElementById("btn").style.backgroundColor=color;

    distance = eucDistance([prev_left,prev_top],[l,r]);
    prev_radius = r;
    prev_left = l;
    prev_top = t;
    params = [counter+1, distance, 2*r];
}

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

function loadTableData(item) {
    const table = document.getElementById("testBody");
      let row = table.insertRow();
      let circle = row.insertCell(0);
      circle.innerHTML = item[0];
      let dist = row.insertCell(1);
      dist.innerHTML = item[1];
      let width = row.insertCell(2);
      width.innerHTML = item[2];
      let stime = row.insertCell(3);
      stime.innerHTML = item[3];
  }

function getList() {
    list = JSON.parse(sessionStorage.getItem("parameter_list"));
    console.log(list[0]);
    for (let index = 0; index < list.length; index++) {
        var param = list[index];
        loadTableData(param);
    }
}


function plotGraph() {
    var data =[]
    var xValues = [];
    var yValues = [];
    for (let i = 0; i < list.length; i++) {
        data.push([list[i][2],list[i][3]]);
    }
    data.sort(function(a,b){return a[0] - b[0];});

    for (let i = 0; i < data.length; i++) {
        xValues.push(data[i][0]);
        yValues.push(data[i][1]);
    }

    new Chart("myChart", {
        type: "line",
        data: {
            labels: xValues,
            datasets: [{
                fill: false,
                lineTension: 0,
                backgroundColor: "red",
                borderColor: "orange",
                label: 'Selection time',
                pointRadius: 5,
                pointHoverRadius: 10,
                data: yValues
            }]
        },
        options: {
            title: {
                display: true,
                text: 'Diameter of target circle v/s Selection Time',
                fontColor : "black",
                fontSize : 30
            },
            legend: {
                display: false,
            },
            scales: {
                yAxes: [{
                    ticks:{
                        fontColor : "black",
                        fontSize : 16
                    },
                    gridLines:{
                        color: "grey",
                        lineWidth:1,
                        zeroLineColor :"#F5F5F5",
                        zeroLineWidth : 2
                    },
                    scaleLabel: {
                        display: true,
                        labelString: 'Selection Time (in ms)',
                        fontColor : "black",
                        fontSize : 16
                    }
                }],
                xAxes: [{
                    ticks:{
                        fontColor : "black",
                        fontSize : 16
                    },
                    gridLines:{
                        color: "grey",
                        lineWidth:1,
                        zeroLineColor :"#F5F5F5",
                        zeroLineWidth : 2
                    },
                    scaleLabel: {
                        display: true,
                        labelString: 'Diameter of Target Circle (in px)',
                        fontColor : "black",
                        fontSize : 16
                    }
                }]
            },
            maintainAspectRatio: false,
        }
    });
    
}
    

