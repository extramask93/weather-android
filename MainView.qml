import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
Item {
    signal updateChart(var chartObject, string type)
    signal loaded()
    objectName: "mainViewObject"
    Background {id:background}
    Component.onCompleted: Interact.onMainViewLoaded()
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
        y: (tileHeight)
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("co2")

        }
        label: Co2.currentValue>-200?Co2.currentValue+" "+Co2.unit:"No data"
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
        label: Lux.currentValue>-200?Lux.currentValue+" "+Lux.unit:"No data"
        label2.anchors.centerIn: img
        label2.anchors.topMargin: 0
        label2.z:2
    }
    MeasureIcon
    {
        function getIcon() {
            if(Battery.currentValue < 0)
                return "/Images/nodata.png";
            else if(Battery.currentValue >60)
                return "/Images/battery(80).png"
            else if(Battery.currentValue >30)
                return "/Images/battery(50).png"
            else if(Battery.currentValue>1)
                return "/Images/battery(10).png"
            else
                return "/Images/battery(0).png"
        }

        id: batteryID
        objectName: "batteryIconObject"
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: getIcon()
        x: (nrOfHorizontalTiles-1)*tileWidth
        y: tileHeight
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("battery")
        }
        label: Battery.currentValue>-200?Battery.currentValue+" "+Battery.unit:"No data"
        label2.anchors.centerIn: img
        label2.anchors.topMargin: 0
        label2.z:2

    }
    MeasureIcon
    {
        id: waterID
        objectName: "humidityIconObject"
        imWidth: tileWidth-20
        imHeight: tileHeight
        imSource: "/Images/water-drop.png"
        x: 0
        y: (2*tileHeight)
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("humidity")
        }
        label: Humidity.currentValue>-200?Humidity.currentValue+" "+Humidity.unit:"No data"

    }
    MeasureIcon
    {
        id: thermometerID
        objectName: "temperatureIconObject"
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: "/Images/thermometer.png"
        x: 0
        y: (3*tileHeight)
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("temperature")
        }
        label: Temperature.currentValue>-200?Temperature.currentValue+" "+Temperature.unit:"No data"
    }
    MeasureIcon
    {
        id: soilID
        objectName: "soilIconObject"
        imWidth: tileWidth
        imHeight: tileHeight
        imSource: "/Images/water-drop.png"
        x: 0
        y: (6*tileHeight)
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("soil")
        }
        label: Soil.currentValue>-200?Soil.currentValue+" "+Soil.unit:"No data"
    }
}