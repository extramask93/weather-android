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
                placeholderText: "192.168.2.1"
                focus: true
            }
            Label {
                text: "Port:"
            }
            TextField {
                placeholderText: "90"
            }
        }
        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Save"
                onClicked: loaderID.source =loaderID.loginSuccess ? "MainView.qml" : "LoginScreen.qml"

            }
            Button {
                text: "Cancel"
                onClicked: loaderID.source =loaderID.loginSuccess ? "MainView.qml" : "LoginScreen.qml"
            }
        }
    }
}
