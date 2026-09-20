import QtQuick 2.15
import QtQuick.Controls 2.2
import CM 1.0
import assets 1.0
import components 1.0

Item {
    id: editClientView
    property QtObject contentFrame

    property Client selectedClient
    Component.onCompleted: masterController.ui_commandController.setSelectedClient(selectedClient)

    Rectangle {
        anchors.fill: parent
        color: Style.colourBackground
    }

    ScrollView{
        id: scrollView
        anchors{
            left: parent.left
            top: parent.top
            right: parent.right
            bottom: commandBar.top
            margins: Style.sizeScreenMargin
        }
        clip: true
        Column{
            width: scrollView.width
            spacing: Style.sizeScreenMargin
            Panel {
                headerText: "Professional Details"
                contentComponent:
                    Column{
                    spacing: Style.sizeControlSpacing
                    StringEditorSingleLine{
                        stringDecorator: selectedClient.ui_reference
                        anchors{
                            left: parent.left
                            right: parent.right
                        }
                    }
                    StringEditorSingleLine{
                        stringDecorator: selectedClient.ui_name
                        anchors{
                            left: parent.left
                            right: parent.right
                        }
                    }
                }
            }
            AddressEditor{
                address: selectedClient.ui_billingAddress
                headerText: "Billing Address"
            }
            AddressEditor{
                address: selectedClient.ui_supplyAddress
                headerText: "Supply Address"
            }
            ContactEditor {
                contentFrame: editClientView.contentFrame
                width: scrollView.width
                client: selectedClient
                headerText: "Contact Details"
            }
        }
    }

    CommandBar{
        id: commandBar
        commandList: masterController.ui_commandController.ui_editClientViewContextCommands
    }
}
