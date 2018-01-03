import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
Item {
    signal updateChart(var chartObject, string type)
    signal loaded()
    objectName: "mainViewObject"
    Background {id:background}
    ComboBox {
            objectName: "stationBoxObject"
            anchors.horizontalCenter: parent.horizontalCenter
            width: 2*tileWidth
            opacity: 0.5
            spacing: 4
            model: Interact.stations
    }
    MyChart{
        anchors.fill: parent
        id: mychartID
        objectName: "mychartObject"
        z: 2
    }
    MeasureIcon
    {
        id: co2ID
        objectName: "co2IconObject"
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: "/Images/co2.png"
        x: 0
        y: (2*tileHeight)
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("co2")
        }
        label: Co2.currentValue
    }
    MeasureIcon
    {
        id: sunID
        objectName: "luxIconObject"
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: "/Images/sun.png"
        x: (nrOfHorizontalTiles-1)*tileWidth
        y: 0
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("lux")
        }
        label: Lux.currentValue
    }
    MeasureIcon
    {
        id: waterID
        objectName: "humidityIconObject"
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: "/Images/water-drop.png"
        x: 0
        y: (3*tileHeight)
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("humidity")
        }
        label: Humidity.currentValue
    }
    MeasureIcon
    {
        id: thermometerID
        objectName: "temperatureIconObject"
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: "/Images/thermometer.png"
        x: 0
        y: (4*tileHeight)
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("temperature")
        }
        label: Temperature.currentValue
    }
}
