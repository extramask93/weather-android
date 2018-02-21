import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Item {
    objectName: "sidePanelObject"
    id: sidePanel
    signal logOutSignal();
    Rectangle {
        color: "green"
        anchors.fill: parent
        ColumnLayout {
            width: parent.width
            height: parent.height
            anchors.top: parent.top
            Label {
                text: "Options"
                anchors.centerIn: parent
            }
            Column {
                anchors.centerIn: parent
                spacing: 4
                Button {
                    text: "Help"
                }
                Button {
                    text: "About"
                }
                Button {
                    text: "Logout"
                    onClicked:{ logOutSignal();
                    }
                }
            }
        }

    }
}
