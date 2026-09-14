import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import assets 1.0

Item {

    /* "PROPERTY ALIAS" is a way of providing alias names of inner block/element properties.

      If These alias names are not defined then we CAN'T OR CAN NEVER BE ABLE TO INTERACT WITH ANY
      OF THE INNER BLOCK/ELEMENT PROPERTIES

        By defining this property alias, we can play with the referred property at any place where
    this module is defined

    Normal Syntax of defining the property alias is as follows
    property alias <alisNameFortheProperty> : <originalProperty>

    Whenever we use the aliasName we would use the referred originalProperty and if we change the value
    or assign a value to the aliasName then the respective referred originalProperty will also be changed
    */

    property alias iconCharacter: textIcon.text
    /* "iconCharacter" is an alias name for the "text" property of "Text block" having id -> textIcon
        "textIcon.text" shows that we are referring to the text property of a block having
        id -> textIcon */

    property alias description: textDescription.text
    /* "description" is an alias name for the "text" property of "Text block" having id -> textDescription
        "textDescription.text" shows that we are referring to the text property of a block having
        id -> textDescription */

    signal navigationButtonClicked()
    // We are defining a signal here which can be emitted by our this component named "NavigationButton"
    // We are only defining here a signal function prototype as we do in our cpp QObject inherited classes
    // The emission of this signal or the conditions of emission of this signal will be explicitly handled
    // somewhere else.

    property color hoverColour: Style.colourNavigationBarBackground
    /* This is a regular property definition. It defines a new property of a specific type for the QML element.

      Normal Syntax of defining a new property is
      property <type_of_Property> <name_of_Property> : <initial_value_assigned_to_Property>
      ==> the syntax beyond " : ... " is optional and it is used to assign initial value to our property

      Now if we use this property anywhere in the QML before assigning it another value, its initial
      value will be used. To assign this property another value we can do it normally as
            hoverColour : "darkgrey"
      */

    width: parent.width
    height: Style.heightNavigationButton

    Rectangle{
        id: background
        anchors.fill: parent
        color: Style.colourNavigationBarBackground

        Row{
        // This is a component which arranges all its child items in a horizontal row line

            Text {
                id: textIcon

                width: Style.widthNavigationButtonIcon
                height: Style.heightNavigationButtonIcon

                font{
                // Defines the font component and is frequently used to operate on different properties
                // of font at once

                    family: Style.fontAwesome
                    // This property is used to set the family of the font which comes from the
                    // Style module's property fontAwesome

                    pixelSize: Style.pixelSizeNavigationBarIcon
                    // This property is used to set the size of the font
                }
                color: Style.colourNavigationBarIcon
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Text{
                id: textDescription
                width: Style.widthNavigationButtonDescription
                height: Style.heightNavigationButtonDescription
                color: Style.colourNavigationBarfont
                verticalAlignment: Text.AlignVCenter
                text: "Setting this!"  //This Property can also be neglected to write because property alias can be declared without it
            }
        }

        MouseArea{
        // This component is used to define an area where mouse can interact.
        // In this specific case we are filling this area to our parent rectangle mean our whole NavigationButton
        // will be able to interact with mouse

            anchors.fill: parent

            cursorShape: Qt.PointingHandCursor
            // This is defining the shape of cursor/pointer when our mouse comes to this specific area

            hoverEnabled: true
            // This enables the hover related effects/states and allow us to see these effects/states

            onEntered: background.state = "hover"
            // This is defining that if our mouse comes into this area then the state of id "background"
            // changes from normal to "hover named state which is defined below".

            // NOTE: HERE "background" is the id of "parent Rectangle". AND IT IS DEFINING THAT
            // THE "hover" STATE OF RECTANGLE WILL BE USED

            onExited: background.state = ""   // Empty state-name is for the normal state
            // This is defining that if our mouse comes out of this area then the state of id "background"
            // changes to normal

            onClicked: navigationButtonClicked()
            // This is defining that when we click our mouse button in this area then the signal
            // "navigationButtonClicker()" will be emitted
        }

        states: [
        // "states" is an array element which holds all the states for this particular "Rectangle" which
        // is actually our Navigation Button.

        // Note: Normal State has empty name: ""

        // Each inner "State" can define multiple propertyChanges under one specific name

            State {
            // "State" defines one of the multiple states of the Rectangle / NavigationButton

                name: "hover"
                // Defines name of this state. It is this name which is used to refer to this state
                // elsewhere in the Rectangle

                PropertyChanges {
                // This "PropertyChanges" block holds the specific changes to the different properties of a specific
                // block element referred to as target

                // NOTE: EACH PropertyChanges Block can handle only one Element/Component Properties. But these block can
                // be declared multiple types to handle different Element's property changes under a single state name
                // "hover" in this case

                    target: background
                    // "target" defines which Element's/Component's properties will change.
                    // NOTE: TARGET REFERS TO THE ID
                    // Here "background" is presented as target which is the id of Rectangle and it is showing that
                    // all the below property changes will be happened to the similar properties of Rectangle

                    color: hoverColour
                    // It defines that the color of the id "background" means Rectangle will become the "hoverColour"
                }
                PropertyChanges {
                // This block defines another changes to the specific Element/Component for the same state named "hover"

                    target: textIcon
                    // Now the target element is the "Text Block Element having id 'textIcon'"

                    color: "yellow"
                }
            }
        ]
    }
}
