import QtQuick 2.15
import QtQuick.Controls 2.2
import CM 1.0
import assets 1.0
import components 1.0

Item {
    id: createClientView
    property QtObject contentFrame

    property Client newClient: masterController.ui_newClient

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
                        stringDecorator: newClient.ui_reference
                        anchors{
                            left: parent.left
                            right: parent.right
                        }
                    }
                    StringEditorSingleLine{
                        stringDecorator: newClient.ui_name
                        anchors{
                            left: parent.left
                            right: parent.right
                        }
                    }
                }
            }
            AddressEditor{
                address: newClient.ui_billingAddress
                headerText: "Billing Address"
            }
            AddressEditor{
                address: newClient.ui_supplyAddress
                headerText: "Supply Address"
            }
            ContactEditor {
                contentFrame: createClientView.contentFrame
                width: scrollView.width
                client: newClient
                headerText: "Contact Details"
            }
        }
    }

    CommandBar{
    // Create an instance of our own self-made component "CommandBar" defined in our "components module"

        id: commandBar

        commandList: masterController.ui_commandController.ui_createClientViewContextCommands
        // "commandList" is the alias name of the property of commandBar - originally known as
        // "commandRepeater.model"
        // Here we are defining that "commandList" is equal to or contains the ui_createClientViewContextCommands
        // Here masterController is our singleton shared property providing functionalities for our MasterController
        // It gets the commandController through the property name "ui_commandController" which reads the getter function
        // for commandController.
        // Then we get access to the QQmlListProperty (which in turn give access to QList of Command*) through
        // the property name ui_createClientViewContextCommands which reads the getter function of similar name
        // and return an object of QQmlListProperty (which has our main QList containing our Data)
    }
}
