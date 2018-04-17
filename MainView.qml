import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQml 2.2
Item {
    focus: true
    signal updateChart(var chartObject, string type)
    signal loaded()
    objectName: "mainViewObject"
    Background {id:background}
    Component.onCompleted: { Interact.onMainViewLoaded(); optionsID.logOutButton.enabled = true; optionsID.stationSettingsButton.enabled = true}
    Component.onDestruction: Interact.pauseTimer()
    Image {
             id: refIcon
             anchors.horizontalCenter: parent.horizontalCenter
             visible: false

             RotationAnimator {
                 id: ro
                 target: refIcon
                 running: refIcon.visible
                 from: 0
                 to: 360
                 loops: Animation.Infinite
                 duration: 2000
             }

             source: "Images/tomato.png"
             z:4
             width: 50
             height: 50
     }

    Flickable {
        property var ended: false
        id: flick2
        clip: true;
        anchors.fill: parent; // use a flickable to allow scrolling
        contentWidth: parent.width; // flickable content width is its own width, scroll only vertically
        contentHeight: parent.height*1.01; // content height is the height of the layout of items
        boundsBehavior: Flickable.DragAndOvershootBounds
        function endRefresh() {
            refIcon.visible = false;
        }

        onContentYChanged: {
            if(flick2.contentY < 0 && !ended) {
               refIcon.visible = true
               refIcon.y = flick2.verticalOvershoot<(-parent.height/6)?(parent.height/6):-flick2.verticalOvershoot;}
        }
        onDragEnded: {
            if(flick2.verticalOvershoot < -200) {
                console.log("refreshing"); //call here
                ended = true
                refIcon.visible = true
                refIcon.y = parent.height/6;
            }
            else {
                refIcon.visible = false
                refIcon.y = 0;
                ended  = true
            }
        }
        onDragStarted: {
            ended = false
        }
    ComboBox {
            id: cmb3
            objectName: "stationBoxObject"
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            height: 40
            opacity: 0.5
            spacing: 4
            model: Interact.stations
            onCurrentIndexChanged: Interact.onStationChanged(currentIndex)
    }

    MyChart{
        anchors.fill: parent
        anchors.bottomMargin: 20
        id: mychartID
        objectName: "mychartObject"
        visible: false
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
                Interact.onUpdateChartSignal("co2", mychartID.periodBox.currentIndex)

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
        y: tileHeight
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("lux",mychartID.periodBox.currentIndex)
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
            else if(Battery.currentValue>80)
                return "/Images/battery(100).png"
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
        y: tileHeight*2
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("battery",mychartID.periodBox.currentIndex)
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
                Interact.onUpdateChartSignal("humidity",mychartID.periodBox.currentIndex)
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
                Interact.onUpdateChartSignal("temperature",mychartID.periodBox.currentIndex)
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
        y: (5*tileHeight)
        mouseArea.onClicked: {
                mychartID.visible = !mychartID.visible
                Interact.onUpdateChartSignal("soil",mychartID.periodBox.currentIndex);
        }
        label: Soil.currentValue>-200?Soil.currentValue+" "+Soil.unit:"No data"
    }
    }
    Keys.onBackPressed: {
        if(mychartID.visible===true){
            mychartID.visible=false;
            event.accepted = true;}
        else {
            event.accepted = false;
            Qt.quit()
        }
    }
    Keys.onEscapePressed: {
        if(mychartID.visible===true){
            mychartID.visible=false;
            event.accepted = true;}
    }
}
