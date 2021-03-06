import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
Item {
    id: settingsPage
    focus: true
    Background {anchors.fill: parent}
    ColumnLayout {
        width: parent.width
        anchors.centerIn: parent
        spacing: 16
        CLabel {
            text: "IP:"
            Layout.alignment: Qt.AlignHCenter
        }
        TextField {
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            id: ipFieldID
            text: SettingsManager.getSetting("Server","ip")
        }
        CLabel {
            Layout.alignment: Qt.AlignHCenter
            text: "Port:"
        }
        TextField {
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            id: portFieldID
            text: SettingsManager.getSetting("Server","port")}
        RowLayout {
            Layout.fillWidth: true
            spacing: 16
            anchors.horizontalCenter: parent.horizontalCenter
            CButton {
                height: ipFieldID.height
                Layout.preferredWidth: ipFieldID.width/4
                Layout.alignment: Qt.AlignLeft
                text: "Save"
                onClicked: {
                    if(SettingsManager.SaveSetting("Server","ip",ipFieldID.text)) {
                    }

                    if(SettingsManager.SaveSetting("Server","port",portFieldID.text)) {
                    }
                    loaderID.source = "LoginScreen.qml"
                }
            }
            CButton {
                height: ipFieldID.height
                Layout.preferredWidth: ipFieldID.width/4
                Layout.alignment: Qt.AlignRight
                text: "Cancel"
                onClicked: loaderID.source = "LoginScreen.qml"
            }
        }
}
    Keys.onBackPressed: {
        loaderID.source = "LoginScreen.qml"
        event.accepted = true;
    }
    Keys.onEscapePressed: {
        loaderID.source = "LoginScreen.qml"
        event.accepted =true;
    }
}
