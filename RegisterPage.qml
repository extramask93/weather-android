import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
Item {
    Background {anchors.fill: parent}
    Flickable {
        clip: true;
        anchors.fill: parent; // use a flickable to allow scrolling
        contentWidth: width; // flickable content width is its own width, scroll only vertically
        contentHeight: layout.height; // content height is the height of the layout of items
        MessageDialog {
            id: messageDialog
            title: "Info"
            text: "Register failed"
            visible: false
            onAccepted: {
                visible = false;
            }
        }
        ColumnLayout {
            id: layout
            width: parent.width
            anchors.centerIn: parent
            spacing: 15
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                topPadding: 15
                text: "Username:"
                id: usernameLab
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                id: username
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "username"
            }
            Label {
                text: "Email:"
                id:emailLab
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                id: email
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "email"
            }
            Label {
                text: "Password:"
                id: passwordLab
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                id: password
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "passsword"
            }
            Label {
                text: "Repeat the password:"
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                id: passwordRepeatLab
            }
            TextField {
                id: passwordRepeat
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "password"
            }
            Label {
                text: "Phone number:"
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                id: phoneNrLab
            }
            TextField {
                id: phoneNr
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "phone number"
            }
            RowLayout {
                Layout.fillWidth: true
                spacing: 16
                anchors.horizontalCenter: parent.horizontalCenter
                Button {
                    height: username.height
                    Layout.preferredWidth: username.width/4
                    Layout.alignment: Qt.AlignRight
                    id: registerButton
                    text: "Register"
                    onClicked: {
                        messageDialog.visible = true
                    }
                }
                Button {
                    height: username.height
                    Layout.preferredWidth: username.width/4
                    Layout.alignment: Qt.AlignRight
                    id: cancelButton
                    text: "Cancel"
                    onClicked: {
                        loaderID.source = "LoginScreen.qml"
                    }
                }
            }
        }
    }
}
