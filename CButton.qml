import QtQuick 2.0

Rectangle {
    id: container
    property alias text: txt.text
    signal clicked
    radius: 8
    border.width: 1

    width: txt.width+10
    height: txt.height+20
    gradient: enabled?enabledGradient:disabledGradient
    Gradient {
        id: disabledGradient
        GradientStop { position: 1.0; color: "grey" }
    }

    Gradient {
        id: enabledGradient
        GradientStop { position: 1.0; color: ma.pressed ? "darkgreen" : "green"}
    }
    Text {
        id: txt
        text: "Button"
        color: "black"
        font.bold: true
        font.pointSize: 12
        anchors.centerIn: parent
    }
    MouseArea {
        id: ma
        anchors.fill: parent
        onClicked: container.clicked()
    }
}
