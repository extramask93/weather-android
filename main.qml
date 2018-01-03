import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Window 2.0
import QtCharts 2.0
import QtQuick.Controls 2.1
Window {
    id: rootID
    visible: true
    width: 480
    height: 640
    title: qsTr("EnvController")
    property int nrOfHorizontalTiles: 4
    property string appTitle: "EnvController"
    property int nrOfVerticalTiles: 8
    property int tileWidth: rootID.width/nrOfHorizontalTiles
    property int tileHeight: rootID.height/nrOfVerticalTiles
    property int widthOfSeizure: 5
     property int durationOfMenuAnimation: 500
    Rectangle {
        anchors.bottom: parent.bottom
        height: parent.height-50
        width: parent.width
    Loader {
        id: loaderID
        objectName: "loaderObject"
        anchors.fill: parent
        height: parent.height-50
        property bool loginSuccess: false
        source: selectSource(LoginHandler.state)
        function selectSource(v) {
            console.log(v);
            switch(v)
            {
            case 0:
                return "MainView.qml";
                break;
            case 1:
                return "MainView.qml";
                break;
            case 2:
                return "Settings.qml";
                break;
            default:
                return "";
            }
        }
    }
    SidePanel {
        id: optionsID
        width: parent.width/2
        x: -optionsID.width
        height: parent.height
        property bool active: false
        Behavior on x { NumberAnimation { duration: durationOfMenuAnimation; easing.type: Easing.OutQuad } }
        onXChanged: {
          //menuProgressOpening = (1-Math.abs(optionsID.x/optionsID.width))
        }
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
            } else {
              optionsID.x = 0 //fully opened
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
    }
}
