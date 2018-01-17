import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
Item {

    property alias chart: chartID
    property alias periodBox: periodBox
    property alias sc: scseries
    property alias date: dateAxID
    property alias val: valueAxID
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
        anchors.top: periodBox.bottom
        antialiasing: true
        legend.visible: false
        objectName: "chartObject"
        ValueAxis {
            id: valueAxID
        }
        DateTimeAxis {
            id: dateAxID
            labelsAngle: 90
            titleText: "date"
        }
        ScatterSeries {
            id: scseries
            axisX:dateAxID
            axisY: valueAxID
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
