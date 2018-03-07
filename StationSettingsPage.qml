import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import foo.bar 1.0
Item {
    width: rootID.width
    Background {anchors.fill: parent}
    Component.onCompleted: Interact.onSettingsLoaded()
    Flickable {
        id: flick
        clip: true;
        anchors.fill: parent; // use a flickable to allow scrolling
        contentWidth: parent.width; // flickable content width is its own width, scroll only vertically
        contentHeight: layout.height; // content height is the height of the layout of items
        Button {
            Layout.alignment: Qt.AlignRight
            opacity: 0.5
            width: (rootID.height*0.10)
            height: width
            anchors.left: parent.left
            anchors.top: parent.top
            text: "+"
            id: plButton
            onClicked:  {
                contextMenu.open()
            }
        }
        Menu {
            id: contextMenu
            y: plButton.height
            MenuItem {text: "Add"}
            MenuItem{text: "Remove"}
        }

        MessageDialog {
            id: messageDialog
            title: "Info"
            text: "Register failed"
            visible: false
            onAccepted: {
                visible = false;
            }
        }
        ColumnLayout {
            id: layout
            width: parent.width
            anchors.centerIn: parent
            spacing: 15
            anchors.horizontalCenter: parent.horizontalCenter
                ComboBox {
                    id: cbox
                    Layout.alignment: Qt.AlignRight
                    Layout.preferredWidth: parent.width*0.8
                    Layout.maximumWidth: parent.width*0.9
                    opacity: 0.5
                    model: Interact.stations
                }

            Label {
                topPadding: 15
                text: "ID:"
                id: idLabel
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                    id: idField
                    Layout.preferredWidth: parent.width-20
                    Layout.alignment: Qt.AlignHCenter
                    placeholderText: "id"
                    text: CurrentStation.id
            }
            Label {
                topPadding: 15
                text: "Name:"
                id: nameLabel
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
            }
            TextField {
                id: nameField
                Layout.preferredWidth: parent.width-20
                Layout.alignment: Qt.AlignHCenter
                placeholderText: "station name"
                text: CurrentStation.name
            }
            Label {
                font.pointSize: 14
                Layout.margins: 10
                text: "Refresh Time: "
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                clip: true
                Label {text: "H:"}
                TextField {
                    Layout.maximumWidth: flick.width/4
                    text: CurrentStation.reftime.getHours()

                }
                Label {text: "M:"}
                TextField {
                    Layout.maximumWidth: flick.width/4
                    text: CurrentStation.reftime.getMinutes()

                }
                Label {text: "S:"}
                TextField {
                     Layout.maximumWidth: flick.width/4
                     text: CurrentStation.reftime.getSeconds()

                }
            }

            Label {
                font.pointSize: 14
                Layout.margins: 10
                text: "Active sensors: "
            }

            CheckBox {
                text: "Temperature"
                id: tempCheckBox
                indicator.width: idField.height
                indicator.height: idField.height
                checked: CurrentStation.tempSensor.enabled

            }
            CheckBox {
                text: "Humidty"
                id: humidityCheckBox
                indicator.width: idField.height
                indicator.height: idField.height
                checked: CurrentStation.humiditySensor.enabled

            }
            CheckBox {
                text: "Lux"
                id: luxCheckBox
                indicator.width: idField.height
                indicator.height: idField.height
                checked: CurrentStation.luxSensor.enabled

            }
            CheckBox {
                text: "Soil"
                id: soildCheckBox
                indicator.width: idField.height
                indicator.height: idField.height
                checked: CurrentStation.soilSensor.enabled

            }
            CheckBox {
                text: "CO2"
                id: co2ChecBox
                indicator.width: idField.height
                indicator.height: idField.height
                checked: CurrentStation.co2Sensor.enabled
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 16
                anchors.horizontalCenter: parent.horizontalCenter
                Button {
                    height: idField.height
                    Layout.alignment: Qt.AlignRight
                    id: registerButton
                    text: "Save"
                    onClicked: {
                        messageDialog.visible = true
                        loaderID.source = "MainView.qml"
                    }
                }
                Button {
                    height: idField.height
                    Layout.alignment: Qt.AlignRight
                    id: cancelButton
                    text: "Cancel"
                    onClicked: {
                        cbox.model = false
                        loaderID.source = "MainView.qml"
                    }
                }
            }
        }
    }
}

