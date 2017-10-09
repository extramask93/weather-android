import QtQuick 2.0

Item {
    width: parent.width
    height: parent.height
    property alias sky: skyID
    property alias ground: groundID
    property alias grass: grassID
    Image {
        width: parent.width
        height: parent.height
        fillMode: Image.Tile
        id: skyID
        source: "images/sky3.jpg"
        sourceSize.width: tileWidth
        sourceSize.height: tileHeight
    }
    Image{
        id: groundID
        width: parent.width
        height: tileHeight*2
        fillMode: Image.Tile
        anchors.bottom: parent.bottom
        source: "images/ground.svg"
        sourceSize.height: tileHeight
        sourceSize.width: tileWidth
        }
    Image{
        id: grassID
        width: parent.width
        height: tileHeight
        fillMode: Image.TileHorizontally
        anchors.bottom: groundID.top
        source: "images/grass.png"
        sourceSize.height: tileHeight
        sourceSize.width: tileWidth
    }

}
