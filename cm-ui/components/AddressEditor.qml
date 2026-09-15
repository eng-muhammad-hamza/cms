import QtQuick 2.15
import CM 1.0
import assets 1.0

Panel {
    property Address address

    contentComponent:
        Column{
        id: column
        spacing: Style.sizeControlSpacing
        StringEditorSingleLine{
            stringDecorator: address.ui_building
            anchors{
                right: parent.right
                left: parent.left
            }
        }
        StringEditorSingleLine{
            stringDecorator: address.ui_street
            anchors{
                right: parent.right
                left: parent.left
            }
        }
        StringEditorSingleLine{
            stringDecorator: address.ui_city
            anchors{
                right: parent.right
                left: parent.left
            }
        }
        StringEditorSingleLine{
            stringDecorator: address.ui_postcode
            anchors{
                right: parent.right
                left: parent.left
            }
        }
    }
}
