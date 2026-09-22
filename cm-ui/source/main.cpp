#include <QGuiApplication>                      // FOR GUI FEATURES
#include <QQmlApplicationEngine>                // FOR QML ENGINE FEATURES AND ENHANCEMENTS
#include <QQmlContext>                          // CONTEXT FUNCTIONALITIES

#include <controllers/mastercontroller.h>       // TO LINK MASTERCONTROLLER

#include <framework/objectfactory.h>

#include <data/intdecorator.h>
#include <data/stringdecorator.h>
#include <data/datetimedecorator.h>
#include <data/enumeratordecorator.h>

#include <data/entity.h>
#include <data/entitycollection.h>

#include <data/dropdown.h>

#include <rss/rsschannel.h>
#include <rss/rssimage.h>
#include <rss/rssitem.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);            // INSTATIATE THE QT GUI APPLICATION CLASS

    qmlRegisterType<cm::controllers::MasterController>("CM",1,0,"MasterController");
    // REGISTER MASTERCONTROLLER AS A QML TYPE TO ACCESS ITS FUNCTIONALITIES OR PROPERTIES IN QML OR SEND AND RECIEVE
    // SIGNALS FROM IT

    // The above line defines a module named "CM" and registers the type MasterController within it.
    // It can be now imported to our QML files like "import CM 1.0" and MasterController can be used
    // just as other components like "Rectange" , "Text" etc.
    // NOTE: TO ACCESS MASTERCONTROLLER IN THIS WAY, WE WOULD END-UP MAKING MULTIPLE INSTANCES OF
    // MASTERCONTROLLER IN OUR PROGRAM WHICH WILL EVENTUALLY CAUSE PROBLEMS. (EXPLAINED FURTHER IN
    // DETAIL BELOW)

    qmlRegisterType<cm::framework::Command>("CM",1,0,"Command");

    qmlRegisterType<cm::data::DateTimeDecorator>("CM",1,0,"DateTimeDecorator");
    qmlRegisterType<cm::data::EnumeratorDecorator>("CM",1,0,"EnumeratorDecorator");
    qmlRegisterType<cm::data::IntDecorator>("CM",1,0,"IntDecorator");
    qmlRegisterType<cm::data::StringDecorator>("CM",1,0,"StringDecorator");

    qmlRegisterType<cm::models::Address>("CM",1,0,"Address");
    qmlRegisterType<cm::models::Contact>("CM",1,0,"Contact");
    qmlRegisterType<cm::models::Appointment>("CM",1,0,"Appointment");
    qmlRegisterType<cm::models::Client>("CM",1,0,"Client");

    qmlRegisterType<cm::models::ClientSearch>("CM",1,0,"ClientSearch");

    qmlRegisterType<cm::rss::RssChannel>("CM",1,0,"RssChannel");
    qmlRegisterType<cm::rss::RssImage>("CM",1,0,"RssImage");
    qmlRegisterType<cm::rss::RssItem>("CM",1,0,"RssItem");

    qmlRegisterUncreatableType<cm::controllers::INavigationController>("CM",1,0,"INavigationController","Interface");
    qmlRegisterUncreatableType<cm::controllers::ICommandController>("CM",1,0,"ICommandController","Interface");

    qmlRegisterType<cm::data::DropDown>("CM", 1, 0, "DropDown");
    qmlRegisterType<cm::data::DropDownValue>("CM", 1, 0, "DropDownValue");

    cm::framework::ObjectFactory objectFactory;
    cm::controllers::MasterController masterController(nullptr,&objectFactory);
    // INSTATIATE MASTERCONTROLLER OBJECT TO BE INJECTED INTO QML CONTEXT TO MAKE IT DIRECTLY ACCESSIBLE

    QQmlApplicationEngine engine;
    // INSTATIATE THE QML ENGINE TO ACCESS ITS FUNCTIONALITIES AND TO INJECT OUR OWN CUSTOM OBJECT AS A QML PROPERTY

    engine.addImportPath("qrc:/");

    engine.rootContext()->setContextProperty("masterController",&masterController);
    // setContextProperty is a method of QQmlContext that binds a C++ object (value)
    // to a property (name) in the QML context. This allows QML code to access and interact
    // with the C++ object directly, such as invoking its methods, accessing its properties, or connecting to its signals.

    const QUrl url(QStringLiteral("qrc:/views/MasterView.qml"));    // MAKING URL OF OUR MASTERVIEW.QML

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);                                               // LOADING OUR MASTERVIEW.QML

    return app.exec();
}





/* If you are registering MasterController as a QML type using qmlRegisterType, you do not need to add
 * an instance of MasterController to the root context using setContextProperty unless you want to share
 * a single instance of MasterController across multiple QML files or components.
 * When you use qmlRegisterType, it allows you to create instances of MasterController directly in your
 * QML files. However, if you need a single instance that should be accessible globally or if you want
 * to set some initial properties on the instance from C++, you might still use setContextProperty.
 * Using "qmlRegisterType"
 *     qmlRegisterType<cm::controllers::MasterController>("CM",1,0,"MasterController");
 * This approach allows you to create instances of MasterController directly in your QML files AS BELOW
 * import QtQuick 2.15
 * import CM 1.0
 * ApplicationWindow {
 *     visible: true
 *         MasterController {
 *                 id: masterController
 *                         // Use the properties and methods of MasterController here
 *         }
 * }
 * Using "setContextProperty"
 * If you need a single, shared instance, you can add MasterController to the root context AS
 *      cm::controllers::MasterController masterController;
 *      qmlRegisterType<cm::controllers::MasterController>("CM", 1, 0, "MasterController");
 *      engine.rootContext()->setContextProperty("masterController", &masterController);
 * IN QML WE CAN NOW USE THIS SHARED INSTANCE AS
 * import QtQuick 2.15
 * import CM 1.0
 * ApplicationWindow {
 *     visible: true
 *         // Use the shared instance of MasterController
 *         Text {
 *              text: masterController.someProperty
 *         }
 * }
 * NOTE:
 * No need to use qmlRegisterType - if you only want to use a single shared instance via setContextProperty.
 * No need to import the module (e.g., import CM 1.0) - if you are only using the shared instance set in the
 * root context with setContextProperty.
 * */
