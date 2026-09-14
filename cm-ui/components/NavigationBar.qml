import QtQuick 2.15
import assets 1.0

Item {
    property bool isCollapsed: true
    // Here we are creating a new property of type bool named "isCollapsed" and initialize
    // its value to be true

    anchors{
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }

    width: isCollapsed ? Style.widthNavigationBarCollapsed : Style.heightNavigationBarExpanded
    // Here simple conditional operator ( __ ? __ : __ ) is used

    Rectangle{
        id: navigationBar
        anchors.fill: parent
        color: Style.colourNavigationBarBackground

        Column{
        // This is a component which arranges all its child items in a vericle columnar line

            width: parent.width

            NavigationButton {
            // This is creating an instance of our self-made component "NavigationButton" defined
            // in our self-made module "component"

                description: "Menu"
                iconCharacter: "ellipsis"
                hoverColour: "darkslategrey"
                onNavigationButtonClicked: isCollapsed = !isCollapsed
                // This is an Event Handler Function (similar to Slots) which suggest that "on" recieving
                // "navigationButtonClicked" signal from "this NavigationButton", the "isCollapsed" value
                // will be altered
            }
            NavigationButton {
                description: "Dashboard"
                iconCharacter: "circle-user"
                hoverColour: "darkslategrey"
                onNavigationButtonClicked: masterController.ui_navigationController.goDashboardView()
                // This is an Event Handler Function (similar to Slots) which suggest that "on" recieving
                // "navigationButtonClicked" signal from "this NavigationButton", it will emit another
                // signal "goDashboardView()" from the NavigationController accessing it through shared
                // instance (singleton object) of masterController
            }
            NavigationButton {
                description: "New Client"
                iconCharacter: "user-pen"
                hoverColour: "darkslategrey"
                onNavigationButtonClicked: masterController.ui_navigationController.goCreateClientView()
            }
            NavigationButton {
                description: "Find Client"
                iconCharacter: "magnifying-glass"
                hoverColour: "darkslategrey"
                onNavigationButtonClicked: masterController.ui_navigationController.goFindClientView()
            }
            NavigationButton {
                description: "RSS Feed"
                iconCharacter: "rss"
                hoverColour: "darkslategrey"
                onNavigationButtonClicked: masterController.ui_navigationController.goRssView()
            }
        }
    }
}
