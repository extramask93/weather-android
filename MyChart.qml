import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "./config.js" as Config
Item {
    property variant allConfig: Config.config()
    property variant currentConfig: allConfig[0]
    property alias chart: chartID
    property alias periodBox: periodBox
    Background {
        anchors.fill: parent
    }
    ComboBox {
            id: periodBox
            objectName: "periodBoxObject"
            //anchors.bottom: chartID.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            height: 100
            opacity: 0.5
            model: ["Today", "3 days","Week", "Month","Year"]
            onActivated: {
                Interact.onUpdateChartSignal("",currentIndex);

            }// {
    }
    Loader {
        source: "qrc:/Qchart2.qml"
        id:chartID
        visible: true
        height: parent.height-periodBox.height
        width: parent.width
        anchors.top: periodBox.bottom
        onLoaded: {
            chartID.item.chartData = currentConfig.data
            chartID.item.chartOptions = currentConfig.options
            chartID.item.chartType = currentConfig.type
            chartID.item.requestPaint()
        }
    }
    function updater() {
        currentConfig = Config.config2()[0]
        chartID.item._chart.destroy()
        chartID.source = ""
        chartID.source = "qrc:/Qchart2.qml"
    }
}
//    Chart{
//        id: chartID
//        objectName: "chartObject"
//        height: parent.height*0.6
//        width: parent.width
//        anchors.top: periodBox.bottom
//        property int test : 65;
//        onPaint: {
//            line({
//                     labels : Model.dates,
//                     datasets : [
//                         {
//                             fillColor : "rgba(220,220,220,0.9)",
//                             strokeColor : "rgba(220,220,220,1)",
//                             pointColor : "rgba(3,93,49,1)",
//                             pointStrokeColor : "#fff",
//                             data : Model.values
//                         }
//                     ]
//                 },{scaleGridLineColor : "rgba(0,0,0,.5)",
//                     scaleFontColor : "#000",scaleFontSize : 25,
//                     pointDotRadius : 15});
//        }}

//    ChartView {
//        id : chartID
//        height: parent.height*0.6
//        width: parent.width
//        anchors.top: periodBox.bottom
//        antialiasing: true
//        legend.visible: false
//        objectName: "chartObject"
//        ValueAxis {
//            id: valueAxID
//        }
//        DateTimeAxis {
//            id: dateAxID
//            labelsAngle: 90
//            titleText: "date"
//        }
//        ScatterSeries {
//            id: scseries
//            axisX:dateAxID
//            axisY: valueAxID
//        }
//    }
