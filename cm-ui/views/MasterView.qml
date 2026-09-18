import QtQuick 2.15
// QtQuick Module Provides Graphical Primitive Types like
// vector2d or Window etc. Have various submodules

import QtQuick.Window 2.15
// This is a submodule of QtQuick which provides window functionalities
// and its related types

import QtQuick.Controls 2.15
// This is a submodule of QtQuick which provides types for
// creating user interfaces

import assets 1.0
// This is our self made module for our assets like Stylings, fonts, pics, logos etc.

import components 1.0
// This is our self made module for our reuseable components like
// navigationButton, navigationBar, etc.

Window {        // Creates a Top Level Window - Main Window/Place of Our Program - Everything
                // that happens in our program is nested within this Window

    width: Style.widthWindow
    height: Style.heightWindow
    visible: true

    title: qsTr("Client Management")
    // This property "title" defines the title of our Main Window which is appered on the top
    // line of Main Window where closing, minimizing etc. controlls are present

    Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml", {contentFrame: contentFrame})
    // This line is defining that our "Component" which is the "Main Window" here and
    // "onCompleted" defining that when it is "Completed the loading" then the thing that
    // happens is that the "StackView - Having Id "contentFrame - defined below" would
    // replace the "initialView - defined below as SplashView" to the "DashboardView"

    Connections{
    // Connections Object creates Connections to the QML Signals
    // It defines a target that will emit signals and Event Handler Functions

        target: masterController.ui_navigationController
        // This is the target which is navigationController, handling navigationBar Functionalities

        function onGoCreateClientView(){
        // This is the Event Handler function (Normal Syntax of Event Handler functions are on<Signal>)
        // which defines that when the signal goCreateClientView() is emitted then the
        // "StackView - Having Id 'contentFrame' - defined Below" would replace the
        // "initialView - defined below as SplashView" to the "CreateClientView"

            contentFrame.replace("qrc:/views/CreateClientView.qml", {contentFrame: contentFrame})
        }
        function onGoDashboardView() {
            contentFrame.replace("qrc:/views/DashboardView.qml", {contentFrame: contentFrame})
        }
        function onGoFindClientView() {
            contentFrame.replace("qrc:/views/FindClientView.qml", {contentFrame: contentFrame})
        }
        function onGoEditClientView(client) {
            contentFrame.replace("qrc:/views/EditClientView.qml", {contentFrame: contentFrame,selectedClient: client})
        }
        function onGoRssView() {
            contentFrame.replace("qrc:/views/RssView.qml", {contentFrame: contentFrame})
        }
    }

    NavigationBar{
    // Creates an Object/Instance of our own self-made new QML Component whose properties are defined
    // in our self-made module "component 1.0"

        id: navigationBar
        // "id" is an important property that allows us to access the respective component/object
        // outside of the object block but within the same QML file.

        // NOTE: TO USE OUR OWN CUSTOM-MADE OBJECTS IN QML, WE MUST REGISTER THEM WITH THE QML ENGINE.
        // THIS CAN BE DONE BY EITHER DEFINING THEM DIRECTLY IN QML OR BY REGISTERING THEIR TYPES
        // AS QML TYPES IN OUR MAIN.CPP FILE. TO REGISTER A TYPE, USE THE FUNCTION qmlRegisterType<TYPE>().
        // ONCE REGISTERED, THESE TYPES WILL BE TREATED AS QML TYPES SIMILAR TO "NavigationBar" OR "Window".
        // THIS REGISTRATION IS NECESSARY FOR TYPES DEFINED IN OUR C++ FILES, COMMONLY REFERRED TO AS CLASSES OR CUSTOM TYPES.

    }

    StackView {
    // StackView is a container that manages a stack of items, where each item can be pushed or popped to
    // navigate between different views. It is often used to implement navigation in applications, where
    // each view in the stack can be a separate screen or component. It is part of the QtQuick.Controls module.

        id: contentFrame
        anchors{
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: navigationBar.right
        }

        clip: true
        // This ensures that any content outside the boundaries of the StackView is clipped, meaning it won’t
        // be visible. This is useful for maintaining a clean visual layout.

        initialItem: SplashView {
            contentFrame: contentFrame
        }

        // This specifies the initial item to be displayed in the StackView. In this case, it points to a QML
        // file located at "qrc:/views/SplashView.qml". When the StackView is first shown, it will load and
        // display the SplashView component.
    }
}
