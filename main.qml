import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Window 2.0
import QtCharts 2.0
Window {
    id: rootID
    visible: true
    width: 480
    height: 640
    title: qsTr("Hello World")
    property int tileWidth: rootID.width/4
    property int tileHeight: rootID.height/8
    Background
    {
        id:background
    }
    MyChart{
        anchors.fill: parent
        id: mychartID
        z: 2
    }

    MeasureIcon
    {
       id: co2ID
       imWidth: tileWidth
       imHeight: tileHeight
       imSource: "co2.png"
       x: 128
       y: 128
    }
    MeasureIcon
    {
       id: sunID
       imWidth: tileWidth
       imHeight: tileHeight
       imSource: "sun.png"
       x: 128
       y: 128
    }
    MeasureIcon
    {
       id: waterID
       imWidth: tileWidth
       imHeight: tileHeight
       imSource: "water-drop.png"
       x: 200
       y: 200
    }
    MeasureIcon
    {
       id: thermometerID
       imWidth: tileWidth
       imHeight: tileHeight
       imSource: "thermometer.png"
       x: 300
       y: 300
    }
}
