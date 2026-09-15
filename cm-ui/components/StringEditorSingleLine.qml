import QtQuick 2.15
import CM 1.0
import assets 1.0

Item {
    property StringDecorator stringDecorator

    height: width > textLabel.width + textValue.width ? Style.heightDataControls : Style.heightDataControls*2

    Flow{
        anchors.fill: parent
        Rectangle{
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourPanelBackground
            Text{
                id: textLabel
                anchors{
                    fill: parent
                    margins: Style.heightCommandButton / 4
                }
                text: stringDecorator.ui_label
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }
        Rectangle{
            id: background
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourDataControlsBackground
            border{
                width: 1
                color: Style.colourDataControlsFont
            }
            TextInput{
                id: textValue
                anchors{
                    fill: parent
                    margins: Style.heightDataControls / 4
                }
                text: stringDecorator.ui_value
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }
        Binding{
            target: stringDecorator
            property: "ui_value"
            value: textValue.text
        }
        /*The Binding component establishes a dependency between the properties of two different
          objects; in our case, the TextInput control called textValue and the StringDecorator
          instance called stringDecorator. The target property defines the object we want to
          update, the property is the Q_PROPERTY we want to set, and value is the value we want
          to set it to. This is a key element that gives us true two-way binding. Without this, we will
          be able to view the value from the StringDecorator, but any changes we make in the UI
          will not update the value.*/
    }
}
