import QtQuick 2.2
import QtQuick.Controls 1.1
Column
{
    id: rootID
    property alias vFieldLabelID: someLabelID
    property alias vFieldTextID: textFieldID
    Label{
        id: someLabelID
        text: "some label"
    }
    TextField{
        id: textFieldID
        maximumLength: 100
    }
}
