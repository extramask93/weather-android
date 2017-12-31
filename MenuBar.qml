import QtQuick 2.0
import QtQuick.Controls 2.1
Item {
    Rectangle {
      id: menuBar
      z: 5
      anchors.top: parent.top
      anchors.topMargin: 0
      width: parent.width
      height: 50
      color: "green"
      Rectangle {
        id: menuButton
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: height
        height: parent.height
        scale: maMenuBar.pressed ? 1.2 : 1
        color: "transparent"
        MouseArea {
          id: maMenuBar
          anchors.fill: parent
          onClicked: rootID.onMenu()
        }
        Image {
            anchors.fill: parent
            source: "/Images/more.png"
        }
        clip: true
      }
      Label {
        id: titleText
        anchors.centerIn: parent
        anchors.verticalCenter: parent.verticalCenter
        text: appTitle
        font.pixelSize: 0.35*parent.height
        color: palette.text
      }
    } //menuBar
}
