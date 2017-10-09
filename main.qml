import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Window 2.0
import QtCharts 2.0
Window {
    id: rootID
    visible: true
    width: 480
    height: 640
    title: qsTr("EnvController")
    property int nrOfHorizontalTiles: 4
    property int nrOfVerticalTiles: 8
    property int tileWidth: rootID.width/nrOfHorizontalTiles
    property int tileHeight: rootID.height/nrOfVerticalTiles
    Loader {
        id: loaderID
        anchors.fill: parent
        property bool loginSuccess: false
        source: loginSuccess ? "MainView.qml" : "LoginScreen.qml"
    }
    Loader {
        id: optionsLoaderID
        width: parent.width/2
        height: parent.height
        property bool active: false
        source: active? "SidePanel.qml" : ""
    }
}
