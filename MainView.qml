import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
Item {
    Background {id:background}
    ComboBox {
            anchors.top: menuBar.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: 2*tileWidth
            opacity: 0.5
            spacing: 4
            model: ["Station 1"]
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
        imSource: "images/co2.png"
        x: 0
        y: (2*tileHeight)
    }
    MeasureIcon
    {
        id: sunID
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: "images/sun.png"
        x: (nrOfHorizontalTiles-1)*tileWidth
        y: 0
    }
    MeasureIcon
    {
        id: waterID
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: "images/water-drop.png"
        x: 0
        y: (3*tileHeight)
    }
    MeasureIcon
    {
        id: thermometerID
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: "images/thermometer.png"
        x: 0
        y: (4*tileHeight)
    }
}
