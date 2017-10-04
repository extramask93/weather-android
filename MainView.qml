import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
Item {
    Background
    {
        id:background
    }
    Button {
        width: tileWidth/2
        height: tileWidth/2
        x:0
        y:0
        background: Rectangle {
            border.color: "green"
            border.width: 1
            opacity: 0.6
            radius: 4
            Image {
                anchors.fill: parent
                source: "more.png"
                fillMode: Image.Stretch
                opacity: 1.0
            }
        }
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
       x: 0
       y: (2*tileHeight)
    }
    MeasureIcon
    {
       id: sunID
       imWidth: tileWidth
       imHeight: tileHeight
       imSource: "sun.png"
       x: (nrOfHorizontalTiles-1)*tileWidth
       y: 0
    }
    MeasureIcon
    {
       id: waterID
       imWidth: tileWidth
       imHeight: tileHeight
       imSource: "water-drop.png"
       x: 0
       y: (3*tileHeight)
    }
    MeasureIcon
    {
       id: thermometerID
       imWidth: tileWidth
       imHeight: tileHeight
       imSource: "thermometer.png"
       x: 0
       y: (4*tileHeight)
    }
}
