import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
Item {
    focus: true
    Background {anchors.fill: parent}
    BusyIndicator {
        id: busy
        running: false
        anchors.centerIn: parent
        width: parent.width/4
        height: parent.width/4
        z: 20
    }
    Connections {
        target: RegisterModel
        onRegistrationFailed: {messageDialog.text = reason;busy.running = false; messageDialog.visible = true; }
        onRegistrationSuccess: {messageDialog.text = "Registration Succeed";  busy.running = false;messageDialog.visible = true;}
    }

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
                registerButton.enabled = true
            }
        }
        ColumnLayout {
            id: layout
            width: parent.width
            anchors.centerIn: parent
            spacing: 15
            anchors.horizontalCenter: parent.horizontalCenter
            CLabel {
                topPadding: 15
                text: "Username:"
                id: usernameLab
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                id: username
                validator: RegExpValidator { regExp: /[\w]{30}/ }
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "username"
            }
            CLabel {
                text: "Email:"
                id:emailLab
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                id: email
                validator: RegExpValidator { regExp: /[\S]{50}/ }
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "email"
            }
            CLabel {
                text: "Password:"

                id: passwordLab
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                id: password
                echoMode: TextInput.Password
                validator: RegExpValidator { regExp: /[\S]{50}/ }
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "passsword"
            }
            CLabel {
                text: "Repeat the password:"
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                id: passwordRepeatLab
            }
            TextField {
                id: passwordRepeat
                echoMode: TextInput.Password
                validator: RegExpValidator { regExp: /[\S]{50}/ }
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "password"
            }
            CLabel {
                text: "Phone number:"
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                id: phoneNrLab
            }
            TextField {
                id: phoneNr
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                validator: RegExpValidator { regExp: /[0-9]{9}/ }
                placeholderText: "phone number"
            }
            RowLayout {
                Layout.fillWidth: true
                spacing: 16
                anchors.horizontalCenter: parent.horizontalCenter
                CButton {
                    height: username.height
                    Layout.preferredWidth: username.width/4
                    Layout.alignment: Qt.AlignRight
                    id: registerButton
                    text: "Register"
                    onClicked: {
                        staticValidate();
                    }
                }
                CButton {
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
    function staticValidate() {
        if(phoneNr.text.length==0 || username.text.length==0 || password.text.length==0 || passwordRepeat.text.length==0
                || email.text.length==0 || phoneNr.text.length==0) {
            messageDialog.text = "Please fill all of the fields";
            messageDialog.visible = true;
            return;
        }
        if(password.text != passwordRepeat.text) {
            messageDialog.text = "Passwords must match";
            messageDialog.visible = true;
            return;
        }
        busy.running = true
        registerButton.enabled = false
        RegisterModel.registerUser(username.text,email.text,password.text,phoneNr.text);
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
