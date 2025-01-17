import QtQuick 2.7

Item {
    id: root

    property alias textObject: textElement
    property alias text: textElement.text
    property alias font: textElement.font
    property alias fontSize: textElement.font.pixelSize
    property alias color: textElement.color
    property alias textFormat: textElement.textFormat
    property alias horizontalAlignment: textElement.horizontalAlignment
    property alias elide: textElement.elide
    property alias wrapMode: textElement.wrapMode
    property alias verticalAlignment: textElement.verticalAlignment

    Text {
        id: textElement

        anchors.fill: parent
        anchors.margins: 8

        verticalAlignment: Text.AlignVCenter

        font.family: "Source Sans Pro"
        font.pixelSize: 28
        font.weight: Font.Light

        color: "white"
    }
}
