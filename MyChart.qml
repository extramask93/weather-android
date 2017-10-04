import QtQuick 2.0
import QtCharts 2.0
Item {
    ChartView {
        id : chartID
        title: "Numerical Data for Dummies"
        anchors.top: parent
        height: parent.height/2
        width: parent.width
        legend.visible: false
        antialiasing: true
        LineSeries {
            axisY: CategoryAxis {
                min: 0
                max: 30
            }
            XYPoint { x: 0; y: 4.3 }
            XYPoint { x: 1; y: 4.1 }
            XYPoint { x: 2; y: 4.7 }
            XYPoint { x: 3; y: 3.9 }
            XYPoint { x: 4; y: 5.2 }
        }
    }
    MouseArea
    {
        anchors.fill: parent
        onClicked: if(chartID.visible===true){
                   mychartID.visible=false;}
    }
}
