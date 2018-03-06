import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
    Timer {
        id: timer
        interval: 3500
        running: false
        repeat: false
        onTriggered: {infoLabelID.text = ""}
    }

    Connections {
        target: LoginHandler
        onLoginFailed: {
            infoLabelID.text = message
            busy.running  = false
            loginButton.enabled = true
            settingsButton.enabled = true
            name.enabled=true
            timer.restart()
        }
        onLoginSuccess: {
            loaderID.source = "MainView.qml"
            busy.running  = false
            loginButton.enabled = true
            settingsButton.enabled = true
            name.enabled = true
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
                //Layout.alignment: Qt.AlignLeft
                //Layout.preferredHeight:userNameID.height
                //Layout.preferredWidth: userNameID.width/2
                id : rememberCheckBox
                checked: LoginHandler.rememberMe
                objectName: "rememberCheckBox"
                text: "Remember me"
                indicator.width: userNameID.height
                indicator.height: userNameID.height
            }
        RowLayout {
            Layout.fillWidth: true
            spacing: 16
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: loginButton
                text: "Login"
                height: userNameID.height
                Layout.preferredWidth: userNameID.width/4
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    busy.running  = true
                    loginButton.enabled = false
                    settingsButton.enabled = false
                    name.enabled= false
                    infoLabelID.text = ""
                    LoginHandler.login = userNameID.text
                    LoginHandler.password = passwordID.text
                    LoginHandler.rememberMe = rememberCheckBox.checked
                    LoginHandler.Login(userNameID.text,passwordID.text)
                }
            }
            Button {
                id: settingsButton
                height: userNameID.height
                Layout.preferredWidth: userNameID.width/4
                Layout.alignment: Qt.AlignRight
                text: "Settings"
                onClicked: loaderID.source = "Settings.qml"
            }
        }
        Text {
            id: name
            text: '<html><style type="text/css"></style><a href="http://google.com">Register</a></html>'
            linkColor: "black"
            Layout.alignment: Qt.AlignHCenter
            font.pointSize: 14
            Layout.margins: 10
            onLinkActivated: {
                loaderID.source = "RegisterPage.qml"
            }
        }
        BusyIndicator {
            id: busy
            running: false
            Layout.preferredHeight: userNameID.height*2
            Layout.preferredWidth: height*2
            Layout.alignment: Qt.AlignHCenter
            z: 20
        }
    }
}
