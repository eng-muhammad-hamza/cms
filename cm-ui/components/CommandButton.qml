import QtQuick 2.15

import CM 1.0
// Here we are importing our self-made module but this module is created through hard-coding in cpp
// within the main.cpp. It is filled with our required components using functions like qmlRegisterType<>

import assets 1.0

Item {
    property Command command
    // Here we are creating a property of type "Command - defined in module CM". Property name is "command"
    // NOTE: WE ARE NOT INITIALIZING OR ASSIGNING ANY INITIAL VALUE TO THIS PROPERTY (HERE ATLEAST)

    width: Style.widthCommandButton
    height: Style.heightCommandButton

    Rectangle{
        id: backgroud
        anchors.fill: parent
        color: Style.colourCommandBarBackground
        Text{
            id: textIcon
            anchors{
                centerIn: parent
                verticalCenterOffset: -10
            }
            font{
                family: Style.fontAwesome
                pixelSize: Style.pixelSizeCommandBarIcon
            }
            color: command.ui_canExecute ? Style.colourCommandBarFont : Style.colourCommandBarFontDisabled
            text: command.ui_iconCharacter
            horizontalAlignment: Text.AlignHCenter
        }
        Text{
            id: textDescription
            anchors{
                top: textIcon.bottom
                bottom: parent.bottom
                right: parent.right
                left: parent.left
            }
            font.pixelSize: Style.pixelSizeCommandBarText
            color: command.ui_canExecute ? Style.colourCommandBarFont : Style.colourCommandBarFontDisabled
            text: command.ui_description
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onEntered: backgroud.state = "hover"
            onExited: backgroud.state = ""
            onClicked: if(command.ui_canExecute) { command.executed() }
            // Here we are defining that when the moused button is clicked in this area then we check
            // whether "ui_canExecute" property of "command" is true or not. If it is true then we are
            // emitting the signal "executed()" of the specific "command"
        }
        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: backgroud
                    color: Qt.darker(Style.colourCommandBarBackground)
                    // "Qt.darker()" function is used to darken the color presented as argument
                }
            }
        ]
    }
}
