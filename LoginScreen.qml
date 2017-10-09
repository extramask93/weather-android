import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
Item {
    Rectangle {
        anchors.fill: parent
        Background {}
    ColumnLayout {
        anchors.fill: parent
        //spacing: 16
        ColumnLayout { /* username */
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 4
            Label { text: "Username"; color: "black"}
            TextField {
                focus: true
                placeholderText: "user"
            }
            //anchors.horizontalCenter: parent.horizontalCenter
            //spacing: 4
            Label { text:"Password"; color: "black" }
            TextField {
                echoMode: TextInput.Password
                placeholderText: "password"
            }
        }
        RowLayout {
            spacing: 16
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "Login"
                onClicked: loaderID.source = "MainView.qml";
            }
            Button {
                text: "Settings"
                onClicked: loaderID.source = "Settings.qml"
            }
        }
    }
    }
}
