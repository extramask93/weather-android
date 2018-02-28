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
            Column {
                anchors.centerIn: parent
                spacing: 16
                Button {
                    text: "Station Settings"
                    enabled: true
                    onClicked: {
                        loaderID.source = "StationSettingsPage.qml"
                    }
                }
                Button {
                    text: "Help"
                }
                Button {
                    text: "About"
                }
                Button {
                    text: "Logout"
                    enabled: false
                    onClicked:{ logOutSignal();
                    }
                }
            }
        }

    }
}
