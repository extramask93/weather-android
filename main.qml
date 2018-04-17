import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Window 2.0
import QtCharts 2.0
import QtQuick.Controls 2.1
Window {
    Connections {
        target: LoginHandler
        onLoginSuccess:{
            loaderID.source = "MainView.qml"
        }
        onLoggedOut: {
            loaderID.source = "LoginScreen.qml"
        }
    }
    Keys.onBackPressed: {
        optionsID.x = -optionsID.width
        active = false
        event.accepted = false;
    }
    Keys.onEscapePressed: {
        optionsID.x = -optionsID.width
        active = false
        event.accepted = false;
    }
    id: rootID
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("EnvController")
    property int nrOfHorizontalTiles: 4
    property string appTitle: "EnvController"
    property int nrOfVerticalTiles: 8
    property int tileWidth: rootID.width/nrOfHorizontalTiles
    property int tileHeight: rootID.height/nrOfVerticalTiles
    property int widthOfSeizure: 10
     property int durationOfMenuAnimation: 500

    Rectangle {
        anchors.bottom: parent.bottom
        height: parent.height-(parent.height*0.10)
        width: parent.width
    Loader {
        id: loaderID
        focus: true
        objectName: "loaderObject"
        anchors.fill: parent
        height: parent.height-(parent.height*0.10)
        source: "LoginScreen.qml"
    }
    SidePanel {
        id: optionsID
        x: -parent.width/2
        width: parent.width/2
        height: parent.height
        property bool active: false
        Behavior on x { NumberAnimation { duration: durationOfMenuAnimation; easing.type: Easing.OutQuad } }
        MouseArea {
          anchors.right: parent.right
          anchors.rightMargin: optionsID.active ? (optionsID.width - rootID.width) : -widthOfSeizure
          anchors.top: parent.top
          width: optionsID.active ? (rootID.width - optionsID.width) : widthOfSeizure
          height: parent.height
          drag {
            target: optionsID
            axis: Drag.XAxis
            minimumX: -optionsID.width
            maximumX: 0
          }
          onClicked: {
            if(optionsID.active) onMenu()
          }
          onReleased: {
            if( Math.abs(optionsID.x) > 0.5*optionsID.width ) {
              optionsID.x = -optionsID.width //close the menu
              optionsID.active = false
            } else {
              optionsID.x = 0 //fully opened
              optionsID.active = true
            }
          }
        }
    }
    }
    /*****( Menu bar )*****/
    MenuBar{
        id: menuBar
        anchors.top: parent.top
        anchors.topMargin: 0
        width: parent.width
        z:5
    }
    function onMenu() {
        optionsID.x = optionsID.active ? -optionsID.width:0
        optionsID.active = !optionsID.active
        if(optionsID.active)
            optionsID.focus = true;
    }
}
