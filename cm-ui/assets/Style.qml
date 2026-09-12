pragma Singleton
import QtQuick 2.15

Item {

    /*  "PROPERTY ALIAS" is a way of providing alias names of inner block/element properties.
      If These alias names are not defined then we CAN'T OR CAN NEVER BE ABLE TO INTERACT WITH ANY
      OF THE INNER BLOCK/ELEMENT PROPERTIES
        By defining this property alias, we can play with the referred property at any place where
    this module is defined*/

    property alias fontAwesome: fontAwesomeLoader.name

    // Below all are readonly properties means they can only be used in our qml code but can't be modified
    // Normal Syntax to define these properties are
    // readonly property <type_of_Property> <Name_of_Property> : <Value_of_the_Property>
    // NOTE: AS THESE PROPERTIES ARE ONLY TO BE READ SO THEY MUST CONTAIN A VALUE
    // WE CAN'T IGNORE INITIALIZING THEM
    // THEY ARE SIMILAR IN QML AS GLOBAL CONSTANTS IN CPP

    readonly property real widthWindow: 1366
    readonly property real heightWindow: 768

    readonly property real widthWindowReference: 1366
    readonly property real heightWindowReference: 768

    function hscale(size) {
    return Math.round(size * (widthWindow / widthWindowReference))
    }
    function vscale(size) {
    return Math.round(size * (heightWindow / heightWindowReference))
    }
    function tscale(size) {
    return Math.round((hscale(size) + vscale(size)) / 2)
    }

    readonly property color colourBackground: "#efefef"

    readonly property color colourNavigationBarBackground: "black"
    readonly property color colourNavigationBarfont: "white"
    readonly property color colourNavigationBarIcon: "white"
    readonly property int pixelSizeNavigationBarIcon: 20

    readonly property real widthNavigationButtonIcon: hscale(30)
    readonly property real heightNavigationButtonIcon: widthNavigationButtonIcon
    readonly property real widthNavigationButtonDescription: hscale(80)
    readonly property real heightNavigationButtonDescription: heightNavigationButtonIcon
    readonly property real widthNavigationButton: widthNavigationButtonIcon + widthNavigationButtonDescription
    readonly property real heightNavigationButton: Math.max(heightNavigationButtonIcon, heightNavigationButtonDescription)

    readonly property real widthNavigationBarCollapsed: widthNavigationButtonIcon
    readonly property real heightNavigationBarExpanded: widthNavigationButton

    readonly property color colourCommandBarBackground: "#cecece"
    readonly property color colourCommandBarFont: "#131313"
    readonly property color colourCommandBarFontDisabled: "#636363"

    readonly property int pixelSizeCommandBarIcon: tscale(25)
    readonly property int pixelSizeCommandBarText: tscale(10)

    readonly property real widthCommandButton: hscale(50)
    readonly property real heightCommandButton: widthCommandButton
    readonly property real heightCommandBar: heightCommandButton

    readonly property real sizeScreenMargin: tscale(20)

    readonly property color colourDataControlsBackground: "white"
    readonly property color colourDataControlsFont: "black"

    readonly property int pixelSizeDataControls: tscale(18)

    readonly property real widthDataControls: hscale(400)
    readonly property real heightDataControls: vscale(40)

    readonly property real sizeControlSpacing: tscale(10)

    readonly property color colourPanelBackground: "white"
    readonly property color colourPanelBackgroundHover: "#ececec"
    readonly property color colourPanelHeaderBackground: "black"
    readonly property color colourPanelHeaderFont: "white"
    readonly property color colourPanelFont: "black"

    readonly property int pixelSizePanelHeader: tscale(18)

    readonly property real heightPanelHeader: vscale(30)

    readonly property real sizeShadowOffset: tscale(5)

    readonly property color colourShadow: "#dedede"

    readonly property color colourItemBackground: "#fefefe"
    readonly property color colourItemBackgroundHover: "#efefef"
    readonly property color colorItemBorder: "#efefef"
    readonly property color colorItemDateFont: "#636363"
    readonly property color colorItemTitleFont: "#131313"
    readonly property real sizeItemMargin: tscale(5)

    readonly property color colourDataSelectorBackground: "#131313"
    readonly property color colourDataControlsBackgroundSelected: "#f36f24"
    readonly property color colourDataSelectorFont: "#ffffff"
    readonly property int sizeDataControlsRadius: tscale(5)

    readonly property real widthFormButton: 240
    readonly property real heightFormButton: 60
    readonly property color colourFormButtonBackground: "#f36f24"
    readonly property color colourFormButtonFont: "#ffffff"
    readonly property int pixelSizeFormButtonIcon: 32
    readonly property int pixelSizeFormButtonText: 22
    readonly property int sizeFormButtonRadius: 5

    FontLoader{
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.ttf"
    }
}
