import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
    Connections {
        target: LoginHandler
        onLoginFailed: {
            infoLabelID.text = message
        }
        onLoginSuccess: {
            loaderID.source = "MainView.qml"
        }
    }
    objectName: "loginObject"
    signal loginSignal(string email, string password);
    Rectangle {
        anchors.fill: parent
        Background {}
    ColumnLayout {
        width: rootID.width/2
        height: parent.height
        anchors.centerIn: parent
        ColumnLayout { /* username */
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 4
            Label { text: "Username"; color: "black"}
            TextField {
                id: userNameID
                Layout.fillWidth: true
                objectName: "userTextField"
                focus: true
                text: LoginHandler.login
                placeholderText: "user"
            }
            Label { text:"Password"; color: "black" }
            TextField {
                id: passwordID
                Layout.fillWidth: true
                objectName: "passwordTextField"
                text: LoginHandler.password
                echoMode: TextInput.Password
                placeholderText: "password"
            }
            Label {
                id: infoLabelID
                text: ""
                color: "red"
            }
            CheckBox {
                id : rememberCheckBox
                checked: LoginHandler.rememberMe
                objectName: "rememberCheckBox"
                text: "Remember me"
            }
        }
        RowLayout {
            spacing: 16
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Login"
                onClicked: {
                    infoLabelID.text = ""
                    LoginHandler.login = userNameID.text
                    LoginHandler.password = passwordID.text
                    LoginHandler.rememberMe = rememberCheckBox.checked
                    LoginHandler.Login(userNameID.text,passwordID.text)
                }
            }
            Button {
                text: "Settings"
                onClicked: loaderID.source = "Settings.qml"
            }
        }
    }
    }
}
