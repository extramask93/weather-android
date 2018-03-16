import QtQuick 2.9
import QtQuick.Controls 2.2


Item {
    property alias running: busy.running
    Rectangle {
        anchors.fill: parent
        color:"green"
        opacity: busy.running?0.6:0
    }
    BusyIndicator {
        id: busy
        running: false
        anchors.centerIn: parent
        width: parent.width/2
        height: width
        z: 20
        contentItem:Image {
            id: img
            visible: busy.running
            anchors.centerIn: parent
            source: "Images/sunflower.png"
            RotationAnimator {
                target: img
                running: busy.visible && busy.running
                from: 0
                to: 360
                loops: Animation.Infinite
                duration: 2000
            }
        }
    }
    Label {
        font.bold: true
        font.pointSize: 25
        visible: busy.running
        color: "black"
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: busy.bottom
        text: "Loading..."
    }
}
