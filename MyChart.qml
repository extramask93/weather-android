import QtQuick 2.0
import QtCharts 2.0
Item {
    property alias chart: chartID
    ChartView {
        id : chartID
        anchors.top: parent
        height: parent.height/2
        width: parent.width
        antialiasing: true
        LineSeries {
            axisY: ValueAxis {
                titleText: "temperature"
                min: 0
                max: 4
            }
            axisX: DateTimeAxis {
                //min: new Date(1514647447511)
                //max: new Date(1599999999999)
                titleText: "date"
                format: "yyyy,MM,d"
                labelsAngle: 90
            }
        }
    }
    MouseArea
    {
        anchors.fill: parent
        onClicked: if(chartID.visible===true){
                   mychartID.visible=false;}
    }
}
