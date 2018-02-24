Qt.include("qrc:/color/color.js")

function getRandomArbitrary(min, max) {
    return Math.random() * (max - min) + min
}

function randomScalingFactor() {
    return Math.round(getRandomArbitrary(-100, 100))
}

var dataBar1 = {
    labels: ["January", "February", "March", "April", "May", "June", "July"],
    datasets: [{
            label: 'temperature',
            fontSize: 20,
            backgroundColor: color("red").alpha(0.5).rgbString(),
            borderColor: "red",
            borderWidth: 1,
            data: [randomScalingFactor(), randomScalingFactor(
                    ), randomScalingFactor(), randomScalingFactor(
                    ), randomScalingFactor(), randomScalingFactor(
                    ), randomScalingFactor()]
        }]
}
var dataBar2 = {
    labels: Model.dates,
    datasets: [{
            label: 'temperature',
            fontSize: 20,
            backgroundColor: color("red").alpha(0.5).rgbString(),
            borderColor: "red",
            borderWidth: 1,
            data: []
        }]
}
function config2() {
console.log(Model.values);
    var arrayLength = Model.values.length;
    for (var i = 0; i < arrayLength; i++) {
        dataBar2.datasets[0].data.push(Model.values[i]) ;}
    var vertical = {
        type: 'line',
        data: dataBar2,
        options: {
            scales: {
               yAxes: [{
                 scaleLabel: {
                   display: true,
                   fontSize:20,
                   fontColor: "#000",
                   labelString: 'temperature[°C]'
                 },
                 ticks: { fontSize: 20,fontColor: "#000",},

               }],
                xAxes: [{
                  scaleLabel: {
                    display: true,
                    fontSize:20,
                    fontColor: "#000",
                    labelString: 'date'
                  },
                  ticks: {fontSize:20,fontColor: "#000",},

                }]
             },
            maintainAspectRatio: false,
            legend: {
                display:false
            },
            title: {
                display: true,
                text: 'Temperature chart',
                fontSize: 20,
                fontColor: "#000"
            }
        }
    }

    var retConfig = []
    // 0
    retConfig.push(vertical)
    // 1

    return retConfig
}
function config() {

    var vertical = {
        type: 'line',
        data: dataBar1,
        options: {
            scales: {
               yAxes: [{
                 scaleLabel: {
                   display: true,
                   fontSize:20,
                   fontColor: "#000",
                   labelString: 'temperature[°C]'
                 },
                 ticks: { fontSize: 20,fontColor: "#000",},

               }],
                xAxes: [{
                  scaleLabel: {
                    display: true,
                    fontSize:20,
                    fontColor: "#000",
                    labelString: 'date'
                  },
                  ticks: {fontSize:20,fontColor: "#000",},

                }]
             },
            maintainAspectRatio: false,
            legend: {
                display:false
            },
            title: {
                display: true,
                text: 'Temperature chart',
                fontSize: 20,
                fontColor: "#000"
            }
        }
    }

    var retConfig = []
    // 0
    retConfig.push(vertical)
    // 1

    return retConfig
}
