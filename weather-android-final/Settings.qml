import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
Item {
    Background {anchors.fill: parent}
    ColumnLayout {
        anchors.fill: parent
        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                text: "IP:"
            }
            TextField {
                id: ipFieldID
                text: ServerSettings.ip
                focus: true
            }
            Label {
                text: "Port:"
            }
            TextField {
                id: portFieldID
                text: ServerSettings.port
            }
        }
        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Save"
                onClicked: { loaderID.source =loaderID.loginSuccess ? "MainView.qml" : "LoginScreen.qml"
                    ServerSettings.ip = ipFieldID.text
                    ServerSettings.port = parseInt(portFieldID.text);
                }

            }
            Button {
                text: "Cancel"
                onClicked: loaderID.source =loaderID.loginSuccess ? "MainView.qml" : "LoginScreen.qml"
            }
        }
    }
}
