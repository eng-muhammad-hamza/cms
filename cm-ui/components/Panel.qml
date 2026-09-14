import QtQuick 2.15
import assets 1.0

Item {
    implicitWidth: parent.width
    implicitHeight: headerBackground.height + contentLoader.implicitHeight + (Style.sizeControlSpacing*2)

    property alias headerText: title.text
    property alias contentComponent: contentLoader.sourceComponent

    Rectangle{
        id: shadow
        width: parent.width
        height: parent.height
        x: Style.sizeShadowOffset
        y: Style.sizeShadowOffset
        color: Style.colourShadow
    }
    Rectangle{
        id: headerBackground
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: Style.heightPanelHeader
        color: Style.colourPanelHeaderBackground

        Text{
            id: title
            text: "SET ME!"
            anchors{
                fill: parent
                margins: Style.heightDataControls/4
            }
            color: Style.colourPanelHeaderFont
            font.pixelSize: Style.pixelSizePanelHeader
            verticalAlignment: Qt.AlignVCenter
        }

    }
    Rectangle{
        id: contentBackground
        anchors{
            top: headerBackground.bottom
            right: parent.right
            left: parent.left
            bottom: parent.bottom
        }
        color: Style.colourPanelBackground

        Loader{
            id: contentLoader
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
                margins: Style.sizeControlSpacing
            }
        }
    }

}
