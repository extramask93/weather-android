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

    Background {anchors.fill: parent}
    ColumnLayout {
        width: parent.width
        anchors.centerIn: parent
        spacing: 15
        anchors.horizontalCenter: parent.horizontalCenter
            Label {
                text: "Username";
                color: "black";
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                id: userNameID
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                objectName: "userTextField"
                focus: true
                text: LoginHandler.login
                placeholderText: "user"
            }
            Label {
                Layout.alignment: Qt.AlignHCenter
                text:"Password";
                color: "black";
            }
            TextField {
                id: passwordID
                Layout.preferredWidth: parent.width - 20
                Layout.alignment: Qt.AlignHCenter
                objectName: "passwordTextField"
                text: LoginHandler.password
                echoMode: TextInput.Password
                placeholderText: "password"
            }
            Label {
                Layout.alignment: Qt.AlignHCenter
                id: infoLabelID
                text: ""
                color: "red"
            }
            CheckBox {
                Layout.alignment: Qt.AlignLeft
                height: passwordID.height
                Layout.preferredWidth: userNameID.width/4
                id : rememberCheckBox
                checked: LoginHandler.rememberMe
                objectName: "rememberCheckBox"
                text: "Remember me"
            }
        RowLayout {
            Layout.fillWidth: true
            spacing: 16
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Login"
                height: ipFieldID.height
                Layout.preferredWidth: userNameID.width/4
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    infoLabelID.text = ""
                    LoginHandler.login = userNameID.text
                    LoginHandler.password = passwordID.text
                    LoginHandler.rememberMe = rememberCheckBox.checked
                    LoginHandler.Login(userNameID.text,passwordID.text)
                }
            }
            Button {
                height: ipFieldID.height
                Layout.preferredWidth: userNameID.width/4
                Layout.alignment: Qt.AlignRight
                text: "Settings"
                onClicked: loaderID.source = "Settings.qml"
            }
        }
    }
}
