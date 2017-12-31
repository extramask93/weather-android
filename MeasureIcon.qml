import QtQuick 2.0

Item {
    property alias img: imgID
    property alias imSource: imgID.source
    property alias imWidth: imgID.sourceSize.width
    property alias imHeight: imgID.sourceSize.height
        Image {
        id: imgID
        z: 1
        MouseArea{
            anchors.fill: parent
            onClicked:{
                if(mychartID.visible===false) {
                    mychartID.visible=true;
                    MModel.getWeekData(mychartID.chart.series(0),mychartID.chart.axisX())
                }
            }
        }
    }
}

