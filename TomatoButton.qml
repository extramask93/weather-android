import QtQuick 2.0
import QtQuick 2.0

Rectangle {
    id: container
    property alias text: txt.text
    signal clicked
    radius: 8
    border.width: 1
    width: txt.width+10
    height: txt.height+20
    Image {
        anchors.fill: container
        width: container.width
        height: container.height
        anchors.margins: -1
                clip: true
        source: "Images/tomato.png"
    }

    Text {
        id: txt
        text: "Button"
        color: "black"
        font.bold: true
        font.pointSize: 12
        anchors.centerIn: parent

    }
    MouseArea {
        id: ma
        anchors.fill: parent
        onClicked: container.clicked()
    }
}

