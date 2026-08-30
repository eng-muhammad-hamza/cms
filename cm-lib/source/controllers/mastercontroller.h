#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>          // FOR QT OBJECT/CORE RELATED FUNCTIONALITIES
#include <QScopedPointer>   // FOR QT SCOPED POINTER BASED FUNCTIONALITES
#include <QString>          // FOR QT STRING BASED FUNCTIONALITIES

#include <cm-lib_global.h>  // FOR CMLIB_EXPORT MACRO DEFINITION

#include <controllers/ICommandController.h>
#include <controllers/INavigationController.h>
#include <controllers/IDatabaseController.h>
#include <framework/IObjectFactory.h>

#include <models/client.h>
#include <models/clientsearch.h>

#include <rss/rsschannel.h>

namespace cm {
namespace controllers {
class CMLIB_EXPORT MasterController : public QObject        // INHERITS FROM QObject -> BASE CLASS OF EVERY QT OBJECT
                                                            // WHICH CAN INTERACT WITH GUI
{
    Q_OBJECT                                            // THIS MACRO'S DECLARATION IS ESSENTIAL TO AVAIL QObject's FEATURES

    Q_PROPERTY(QString ui_welcomeMessage READ welcomeMessage CONSTANT)
    // Setting the Q_PROPERTY for our welcomeMessage member to make it directly assessible in QML

    Q_PROPERTY(cm::controllers::INavigationController* ui_navigationController READ navigationController CONSTANT)
    // In qml we can access the navigation controller as
    // masterController.ui_navigationController.(functions of navigationController)
    // Properties are used to expose data members or member functions to qml.
    // In this case this property exposes the navigationController Getter function to
    // qml as "ui_navigationController" name which gets its data or reads its inner content from
    // the getter function written beside the "READ". As this function is a getter function of
    // navigationController so ui_navigationController actually makes us elligible to operate on the
    // actual navigationController from UI/QML.

    Q_PROPERTY(cm::controllers::ICommandController* ui_commandController READ commandController CONSTANT)

    Q_PROPERTY(cm::models::Client* ui_newClient READ newClient CONSTANT)

    Q_PROPERTY(cm::models::ClientSearch* ui_clientSearch READ clientSearch CONSTANT)

    Q_PROPERTY(cm::controllers::IDatabaseController* ui_databaseController READ databaseController CONSTANT)

    Q_PROPERTY(cm::rss::RssChannel* ui_rssChannel READ rssChannel NOTIFY rssChannelChanged)

public:
    explicit MasterController(QObject *parent = nullptr, framework::IObjectFactory* objectFactory = nullptr);   // Overloaded Constructor - Essential for Assessing Features
    ~MasterController();

    INavigationController* navigationController();           // Getter of NavigationController to access its functionalities

    ICommandController* commandController();

    IDatabaseController* databaseController();

    models::Client* newClient();

    models::ClientSearch* clientSearch();

    rss::RssChannel* rssChannel();

    QString welcomeMessage() const;                         // Getter of data member "welcomeMessage"

public slots:
    void selectClient(cm::models::Client* client);
    void onRssReplyRecieved(int statusCode, QByteArray body);

private:
    class Implementation;                                   // Implementation class to hold all the implementation of this - interface of MasterController
    QScopedPointer<Implementation> implementation;          // Pointer to its own implementation
signals:
    void rssChannelChanged();
};
}
}

/* The above "private class Implementation" is to ensure the Pimpl Idiom establishment which is a design patter specific
 * to cpp. This is just to hide the implementation of a class from the user. In this case "class Implementation" is
 * just prototyped in interface of MasterController but it is implemented in .cpp - Source File separating the inteface
 * completely means the MasterController.h now don't even have its own datamembers now. All the implementation of
 * MasterController is integrated in class Implementation */

/* Q_PROPERTY(<type> <name> READ <getterFunctionName> WRITE <setterFunctionName> NOTIFY <signalFunctionName> <FINAL/CONSTANT/REQUIRED>)
 * THIS IS THE MOST COMMAND SYNTAX OF DEFINING Q_PROPERTY WHICH IS DEFINING THAT THIS PROPERTY IS OF TYPE "<type>"
 * HAVING NAME AS "<name>" AND THIS PROPERTY CAN READ A VALUE SPECIFIED BY THE "GETTER FUNCTION" WHOSE NAME IS SPECIFIED
 * BY THE "READ" FUNCTIONALITY SUCH AS "<getterFunctionName>" AND THIS PROPERTY CAN SET THE SPECIFIED VALUE BY USING
 * "SETTER FUNCTION" WHOSE NAME IS SPECIFIED BY "WRITE" FUNCTIONALITY SUCH AS "<setterFunctionName>" AND THIS
 * FUNCTIONALITY CAN EMIT SIGNAL WHOSE NAME IS SPECIFIED BY "NOTIFY" FUNCTIONALITY AS "<signalFunctionName>".
 * IN SIMPLE WORDS
 * - READ: Specifies the getter function for the property, named "<getterFunctionName>", which returns the property value.
 * - WRITE: Specifies the setter function for the property, named "<setterFunctionName>", which sets the property value.
 * - NOTIFY: Specifies the signal that is emitted when the property's value changes, named "<signalFunctionName>".
 *
 * Additional specifiers:
 * - FINAL: Indicates that this property cannot be overridden in derived classes.
 * - CONSTANT: Indicates that the property's value does not change after initialization, similar to constant members in standard C++ classes.
 * - REQUIRED: Indicates that this property must be overridden in derived classes.
 */

#endif // MASTERCONTROLLER_H
