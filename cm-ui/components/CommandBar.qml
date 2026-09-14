import QtQuick 2.15
import assets 1.0

Item {
    property alias commandList: commandRepeater.model
    // Providing alias name for the "model" property of the "Repeater" Component/Element
    // having id "commandRepeater"

    anchors{
        left: parent.left
        right: parent.right
        bottom: parent.bottom
    }

    height: Style.heightCommandBar

    Rectangle{
        anchors.fill: parent
        color: Style.colourCommandBarBackground
        Row{
            anchors{
                top: parent.top
                bottom: parent.bottom
                right: parent.right
            }
            Repeater{
            // It repeatedly instantiates a number of "ITEM-BASED" Components using a
            // provided Model.
            // It is used to create a large number of SIMILAR ITEMS. It is typically used for creating lists
            // or grids of similar items.
            // Repeater has "model" and "delegate:" properties.
            // model: Specifies the data model used to generate items. The model can be a simple integer
            // (indicating the number of items), an array, a JavaScript object, or a QML data model (like QQmlListProperty).
            // It defines the source of Data. Each item in the model will correspond to an instance of the delegate component.
            // delegate: Defines the component that will be instantiated for each item in the model. Each instance is created
            // using this template. modelData is a special context property available inside the delegate, representing the
            // data for the current item.

            // For each item in the model, the Repeater creates an instance of the delegate component. These instances
            // are managed by the Repeater and can be accessed and manipulated as needed.

                id: commandRepeater
                delegate: CommandButton{
                    command: modelData
                }
                // The above "delegate:" block is defining that for every element in model an instance of CommandButton
                // will be created.
                // Here, in this program, the property "commandList" is giving us the QQmlListProperty<Command> which is
                // provided from one of our Views(.qml). This Property contains QList<Command*> of our Custom Commands
                // Thus for each custom Command, a CommandButton will be created and its "command" property will be
                // assigned the data of that particular custom Command as value. The Rest is done by the Mechanism
                // implemented for CommandButton within CommandButton.qml
            }
        }
    }
}
