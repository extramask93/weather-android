import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Controls 2.1
Item {

    property alias chart: chartID
    property alias periodBox: periodBox
    ChartView {
        id : chartID
        height: parent.height/2
        width: parent.width
        antialiasing: true
        objectName: "chartObject"
        LineSeries {
            axisY: ValueAxis {
                titleText: "temperature"
                min: 0
                max: 4
            }
            axisX: DateTimeAxis {
                titleText: "date"
                format: "yyyy,MM,d"
                labelsAngle: 90
            }
        }
    }
    ComboBox {
        id: periodBox
        objectName: "periodBoxObject"
        anchors.top: chartID.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: 2*tileWidth
        model: ["Today", "3 days","Week", "Month","Year"]
    }

    MouseArea
    {
        anchors.bottom: parent.bottom
        height: parent.height/2
        width: parent.width
        onClicked: if(chartID.visible===true){
                   mychartID.visible=false;}
    }
}
