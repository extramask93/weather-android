import QtQuick 2.0
import QtQuick.Controls 2.2
CheckBox {
        id : cbox
        text: ""
        font.bold: true
        font.pointSize: 12
        indicator: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 40
                    radius: 3
                    border.color: cbox.activeFocus ? "darkblue" : "gray"
                    border.width: 1
                    Image {
                        visible: cbox.checked
                        source: "/Images/broccoli.png"
                        rotation: 20
                        anchors.margins: -1
                        anchors.fill: parent
                    }
            }
}
