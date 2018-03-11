import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Item {
    objectName: "sidePanelObject"
    property alias logOutButton: logoutButton
    property alias stationSettingsButton: stationSettingsButton_
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
                CButton {
                    id: stationSettingsButton_
                    text: "Station Settings"
                    enabled: false
                    onClicked: {
                        loaderID.source = "StationSettingsPage.qml"
                    }
                }
                CButton {
                    text: "Help"
                }
                CButton {
                    text: "About"
                }
                CButton {
                    id: logoutButton
                    text: "Logout"
                    enabled: false
                    onClicked:{ loaderID.source = "LoginScreen.qml" ;logOutSignal();
                    }
                }
            }
        }

    }
}
