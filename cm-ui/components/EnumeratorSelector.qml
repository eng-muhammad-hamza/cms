import QtQuick 2.9
import QtQuick.Controls 2.2
import CM 1.0
import assets 1.0

Item {
    id: enumeratorSelectorRoot
    property DropDown dropDown
    property EnumeratorDecorator enumeratorDecorator
    property QtObject contentFrame
    property int selectedValue
    property bool popupVisible: false

    height: width > textLabel.width + textAnswer.width ? Style.heightDataControls : Style.heightDataControls * 2

    Flow {
        anchors.fill: parent
        Rectangle {
            width: Style.widthDataControls
            height: Style.heightDataControls
            Text {
                id: textLabel
                anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                }
                text: enumeratorDecorator.ui_label
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }
        Rectangle {
            id: buttonAnswer
            width: Style.widthDataControls
            height: Style.heightDataControls
            radius: Style.sizeDataControlsRadius
            enabled: dropDown ? dropDown.ui_values.length > 0 : false
            color: Style.colourDataSelectorBackground
            Text {
                id: textAnswer
                anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                }
                text: dropDown.findDescriptionForDropDownValue(enumeratorDecorator.ui_value)
                color: Style.colourDataSelectorFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    popupVisible = !popupVisible
                }
            }
        }
    }

    Popup {
        id: popup
        visible: popupVisible
        width: parent.width
        height: menu.implicitHeight
        onVisibleChanged: popupVisible = visible

        Column {
            id: menu
            width: parent.width
            Repeater {
                id: repeaterAnswers
                model: dropDown.ui_values
                delegate: Rectangle {
                    property bool isSelected: modelData.ui_key === enumeratorDecorator.ui_value
                    width: parent.width
                    height: Style.heightDataControls
                    radius: Style.sizeDataControlsRadius
                    color: isSelected ? Style.colourDataControlsBackgroundSelected : Style.colourDataSelectorBackground

                    Text {
                        anchors {
                            fill: parent
                            margins: Style.heightDataControls / 4
                        }
                        text: modelData.ui_description
                        color: Style.colourDataSelectorFont
                        font.pixelSize: Style.pixelSizeDataControls
                        verticalAlignment: Qt.AlignVCenter
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            enumeratorDecorator.ui_value = modelData.ui_key
                            popupVisible = false
                        }
                    }
                }
            }
        }
    }
}


// import QtQuick 2.9
// import QtQuick.Controls 2.2
// import CM 1.0
// import assets 1.0

// Item {
//     id: enumeratorSelectorRoot
//     property QtObject contentFrame

//     property DropDown dropDown
//     property EnumeratorDecorator enumeratorDecorator
//     height: width > textLabel.width + textAnswer.width ?
//                 Style.heightDataControls : Style.heightDataControls * 2
//     Flow {
//         anchors.fill: parent
//         Rectangle {
//             width: Style.widthDataControls
//             height: Style.heightDataControls
//             Text {
//                 id: textLabel
//                 anchors {
//                     fill: parent
//                     margins: Style.heightDataControls / 4
//                 }
//                 text: enumeratorDecorator.ui_label
//                 color: Style.colourDataControlsFont
//                 font.pixelSize: Style.pixelSizeDataControls
//                 verticalAlignment: Qt.AlignVCenter
//             }
//         }
//         Rectangle {
//             id: buttonAnswer
//             width: Style.widthDataControls
//             height: Style.heightDataControls
//             radius: Style.sizeDataControlsRadius
//             enabled: dropDown ? dropDown.ui_values.length > 0 : false
//             color: Style.colourDataSelectorBackground
//             Text {
//                 id: textAnswer
//                 anchors {
//                     fill: parent
//                     margins: Style.heightDataControls / 4
//                 }
//                 text:
//                     dropDown.findDescriptionForDropDownValue(enumeratorDecorator.ui_value)
//                 color: Style.colourDataSelectorFont
//                 font.pixelSize: Style.pixelSizeDataControls
//                 verticalAlignment: Qt.AlignVCenter
//             }
//             MouseArea {
//                 anchors.fill: parent
//                 onClicked:
//                     contentFrame.push("qrc:/components/EnumeratorSelectorView.qml",
//                                       {dropDown: enumeratorSelectorRoot.dropDown,
//                                           enumeratorDecorator: enumeratorSelectorRoot.enumeratorDecorator, contentFrame: enumeratorSelectorRoot.contentFrame})
//             }
//         }
//     }
// }
