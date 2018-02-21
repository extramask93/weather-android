import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
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
                text: SettingsManager.getSetting("Server","ip")
                focus: true
            }
            Label {
                text: "Port:"
            }
            TextField {
                id: portFieldID
                text: SettingsManager.getSetting("Server","port")
            }
        }
        RowLayout {
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
