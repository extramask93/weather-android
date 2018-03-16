import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item {
    focus: true
    Component.onCompleted: { optionsID.logOutButton.enabled = false; optionsID.stationSettingsButton.enabled = false}
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
            CLabel {
                text: "Username";
                color: "black";
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                id: userNameID
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                objectName: "userTextField"
                text: LoginHandler.login
                placeholderText: "user"
            }
            CLabel {
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
            CLabel {
                Layout.alignment: Qt.AlignHCenter
                id: infoLabelID
                text: ""
                color: "red"
            }
            CCheckBox {
                Layout.leftMargin: 10
                id : rememberCheckBox
                checked: LoginHandler.rememberMe
                objectName: "rememberCheckBox"
                text: "Remember me"
                }
        RowLayout {
            Layout.fillWidth: true
            spacing: 16
            anchors.horizontalCenter: parent.horizontalCenter
            CButton {
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
            CButton {
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

    }
    Keys.onBackPressed: {
        Qt.quit();
        event.accepted = true;
    }
    Keys.onEscapePressed: {
        Qt.quit();
        event.accepted =true;
    }
    CBusy {
        id: busy
        running: false
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        //Layout.preferredHeight: userNameID.height*2
        //Layout.preferredWidth: height
        //Layout.alignment: Qt.AlignHCenter
//        z: 20
//        contentItem:Image {
//            id: img
//            visible: busy.running
//            anchors.centerIn: parent
//            source: "Images/sunflower.png"
//            RotationAnimator {
//                target: img
//                running: busy.visible && busy.running
//                from: 0
//                to: 360
//                loops: Animation.Infinite
//                duration: 2000
//            }
//        }
    }
}
