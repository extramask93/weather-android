Qt.include("qrc:/color/color.js")


function config2() {
    var dataBar2 = {
        labels: [],
        datasets: [{
                label: 'temperature',
                fontSize: 20,
                backgroundColor: color("red").alpha(0.5).rgbString(),
                borderColor: "red",
                pointRadius:10,
                borderWidth: 1,
                data: []
            }]
    }
    var arrayLength = Model.values.length;
    var labelslen2 = Model.dates.length;
    var labelslen = dataBar2.labels.length;
    var datalen = dataBar2.datasets[0].data.length;
    for (var i = 0; i < arrayLength; i++) {
        dataBar2.datasets[0].data.push(Model.values[i]) ;}
    for (var i = 0; i < labelslen2; i++) {
        dataBar2.labels.push(Model.dates[i]) ;}
    var vertical = {
        type: 'line',
        data: dataBar2,
        options: {
            scales: {
               yAxes: [{
                 scaleLabel: {
                   display: true,
                   fontSize:50,
                   fontColor: "#000",
                   labelString: Model.cType+' ['+Model.unit+']'
                 },
                 ticks: { fontSize: 50,fontColor: "#000",},

               }],
                xAxes: [{
                  scaleLabel: {
                    display: true,
                    fontSize:50,
                    fontColor: "#000",
                    labelString: 'date'
                  },
                  ticks: {fontSize:50,fontColor: "#000",autoSkip: true,
                            maxTicksLimit: 4},

                }]
             },
            maintainAspectRatio: false,
            legend: {
                display:false
            },
            title: {
                display: true,
                text: Model.cType+" Chart",
                fontSize: 50,
                fontColor: "#000"
            }
        }
    }
    var retConfig = []
    retConfig.push(vertical)
    return retConfig
}

