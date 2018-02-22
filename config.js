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
            backgroundColor: color("red").alpha(0.5).rgbString(),
            borderColor: "red",
            borderWidth: 1,
            data: [randomScalingFactor(), randomScalingFactor(
                    ), randomScalingFactor(), randomScalingFactor(
                    ), randomScalingFactor(), randomScalingFactor(
                    ), randomScalingFactor()]
        }]
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
                   labelString: 'probability'
                 }
               }],
                xAxes: [{
                  scaleLabel: {
                    display: true,
                    labelString: 'probability'
                  }
                }]
             },
            maintainAspectRatio: false,
            legend: {
                position: 'top'
            },
            title: {
                display: true,
                text: 'Chart.js Bar Chart'
            }
        }
    }

    var retConfig = []
    // 0
    retConfig.push(vertical)
    // 1

    return retConfig
}
