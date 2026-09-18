import QtQuick 2.15
import QtQuick.Window 2.15
import assets 1.0

Item {
    id: dashboardView
    property QtObject contentFrame

    Rectangle {
        anchors.fill: parent
        color: "#e4e4e4"
        AnimatedImage {
                id: logo
                source: "qrc:/assets/logo.gif"
                anchors.centerIn: parent

                MouseArea {
                    anchors.fill: parent
                    onClicked: logo.playing = !logo.playing
                }
        }
    }
}
