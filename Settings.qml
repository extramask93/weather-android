import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
Item {
    Background {anchors.fill: parent}
    ColumnLayout {
        width: rootID.width*0.8
        height: parent.height
        anchors.centerIn: parent
        ColumnLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 4
            Label {
                text: "IP:"
            }
            TextField {
                Layout.fillWidth: true
                id: ipFieldID
                text: SettingsManager.getSetting("Server","ip")
                focus: true
            }
            Label {
                text: "Port:"
            }
            TextField {
                id: portFieldID
                Layout.fillWidth: true
                text: SettingsManager.getSetting("Server","port")
            }
        }
        RowLayout {
            Layout.fillWidth: true
            spacing: 16
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Save"
                onClicked: {
                    if(SettingsManager.SaveSetting("Server","ip",ipFieldID.text)) {
                    }

                    if(SettingsManager.SaveSetting("Server","port",portFieldID.text)) {
                    }
                    loaderID.source = "LoginScreen.qml"
                }
            }
            Button {
                text: "Cancel"
                onClicked: loaderID.source = "LoginScreen.qml"
            }
        }
    }
}
