import QtQuick 2.0
import QtQuick.Controls 2.1
Item {
    property alias img: imgID
    property alias imSource: imgID.source
    property alias imWidth: imgID.sourceSize.width
    property alias imHeight: imgID.sourceSize.height
    property alias mouseArea: iconMauseArea
    property alias label: label.text
    property alias label2: label
        Image {
        id: imgID
        z: 1
        MouseArea{
            id: iconMauseArea
            anchors.fill: parent
        }
    }
        Label {
            id: label
            anchors.left: imgID.right
            anchors.top: imgID.top
            anchors.topMargin: imgID.height/2
            font.bold: true
            font.pixelSize: 20
            text: "no data"
        }
}

