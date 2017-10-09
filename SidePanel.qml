import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Item {
    Rectangle {
        color: "white"
        anchors.fill: parent
    ColumnLayout {
        width: parent.width/2
        height: parent.height
        anchors.top: parent.top
        Label {
            anchors.centerIn: parent
            text: "Options"
        }
        Button {
            anchors.centerIn: parent
            text: "Help"
        }
        Button {
            anchors.centerIn: parent
            text: "About"
        }
    }

    }
}
