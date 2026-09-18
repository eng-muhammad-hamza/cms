import QtQuick 2.15
import assets 1.0

Item {
// A basic visual element that can contain other visual elements. It does not have any
// visible appearance itself but provides the foundation for other items to be placed.

    id: splashView
    property QtObject contentFrame

    Rectangle {
    // A visual element that draws a rectangle. It is often used as a container and can be styled
    // with color, border, and other visual properties.

        anchors.fill: parent
        color: Style.colourBackground

        Text {
            id: welcomeText
            anchors.centerIn: parent

            text: qsTr("SplashView")
            // This sets the text displayed by the Text element to "SplashView". The qsTr function
            // is used to mark the text for translation, allowing for internationalization of your application.
        }
    }
}
