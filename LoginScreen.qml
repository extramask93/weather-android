import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
Item {
    objectName: "loginObject"
    signal loginSignal(string email, string password);
    Rectangle {
        anchors.fill: parent
        Background {}
    ColumnLayout {
        anchors.fill: parent
        ColumnLayout { /* username */
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 4
            Label { text: "Username"; color: "black"}
            TextField {
                id: userNameID
                objectName: "userTextField"
                focus: true
                text: "cloakengage2@gmail.com"
                placeholderText: "user"
            }
            Label { text:"Password"; color: "black" }
            TextField {
                id: passwordID
                objectName: "passwordTextField"
                text: "admin123"
                echoMode: TextInput.Password
                placeholderText: "password"
            }
            Label {
                id: infoLabelID
                text: LoginHandler.message
                color: "red"
            }
            CheckBox {
                id : rememberCheckBox
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
                    loginSignal(userNameID.text,passwordID.text);
                   //LoginHandler.doLogin(userNameID.text,passwordID.text);
                }
            }
            Button {
                text: "Settings"
                onClicked: LoginHandler.doChangeState(2);
            }
        }
    }
    }
}
