#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <cm-lib_global.h>

#include <framework/command.h>

#include <controllers/IDatabaseController.h>
#include <controllers/ICommandController.h>
#include <controllers/navigation-controller.h>
#include <models/client.h>
#include <models/clientsearch.h>
#include <networking/IWebRequest.h>

namespace cm {
namespace controllers {

// This class provides functionalities to handle all the commands of our Application

class CMLIB_EXPORT CommandController : public ICommandController
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_createClientViewContextCommands READ ui_createClientViewContextCommands CONSTANT)
    // This is defining the property of type QQmlListProperty<> for our createClientViewContextCommands under the name
    // ui_createClientViewContextCommands which reads the getter function of the same name
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_findClientViewContextCommands READ ui_findClientViewContextCommands CONSTANT)

    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_editClientViewContextCommands READ ui_editClientViewContextCommands CONSTANT)

    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_rssViewContextCommands READ ui_rssViewContextCommands CONSTANT)

public:
    explicit CommandController(QObject *parent = nullptr, IDatabaseController* databaseController = nullptr, models::Client* newClient = nullptr, models::ClientSearch* clientSearch = nullptr, INavigationController* navigationController = nullptr, networking::IWebRequest* webRequest = nullptr);
    ~CommandController();

    QQmlListProperty<framework::Command> ui_createClientViewContextCommands() override;
    // Getter function for createClientViewContextCommands

    QQmlListProperty<framework::Command> ui_findClientViewContextCommands() override;

    QQmlListProperty<framework::Command> ui_editClientViewContextCommands() override;

    QQmlListProperty<framework::Command> ui_rssViewContextCommands() override;

public slots:
    void onCreateClientSaveExecuted() override;
    // This is an event handler which will be called when the signal "createClientSaveExecuted()" is fired
    void onFindClientSearchExecuted() override;
    void onEditClientSaveExecuted() override;
    void onEditClientDeleteExecuted() override;
    void onRssRefreshExecuted() override;
    void setSelectedClient(cm::models::Client* client) override;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
signals:
};
}
}

#endif // COMMANDCONTROLLER_H
