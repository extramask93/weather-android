import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
Item {

    property alias chart: chartID
    property alias periodBox: periodBox
    ColumnLayout {
        width: parent.width
        anchors.fill: parent
        Background {
            anchors.fill: parent
        }

        ComboBox {
            id: periodBox
            objectName: "periodBoxObject"
            anchors.bottom: chartID.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: 2*tileWidth
            model: ["Today", "3 days","Week", "Month","Year"]
            onActivated: Interact.onUpdateChartSignal("")
        }
    ChartView {
        id : chartID
        height: parent.height/2
        width: parent.width
        anchors.centerIn: parent
        antialiasing: true
        legend.visible: false
        objectName: "chartObject"
        ValueAxis {
            id: axisY
            titleText: "temperature"
            min: 0
            max: 100
        }
        DateTimeAxis {
            id: axisX
            titleText: "date"
            format: "yy,MM,dd"
            labelsAngle: 90
        }
        LineSeries {
            axisX: axisX
            axisY: axisY
        }
        ScatterSeries {
            axisX: axisX
            axisY: axisY
        }
    }

    MouseArea
    {
        anchors.top: chartID.bottom
        height: parent.height/2
        width: parent.width
        onClicked: if(chartID.visible===true){
                   mychartID.visible=false;}
    }
    }
}
