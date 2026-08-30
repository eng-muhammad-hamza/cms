#include "commandcontroller.h"

#include <QList>
#include <QDebug>

using namespace cm::framework;

namespace cm {
namespace controllers {

class CommandController::Implementation{
public:
    CommandController* commandController{nullptr};
    IDatabaseController* databaseController{nullptr};
    models::Client* newClient{nullptr};
    models::Client* selectedClient{nullptr};
    models::ClientSearch* clientSearch{nullptr};
    INavigationController* navigationController{nullptr};
    networking::IWebRequest* webRequest{nullptr};
    QList<Command*> createClientViewContextCommands;
    QList<Command*> findClientViewContextCommands;
    QList<Command*> editClientViewContextCommands;
    QList<Command*> rssViewContextCommands;

    Implementation(CommandController* _commandController, IDatabaseController* _databaseController, models::Client* _newClient, models::ClientSearch* _clientSearch, INavigationController* _navigationController, networking::IWebRequest* _webRequest)
        : commandController(_commandController), databaseController(_databaseController), newClient(_newClient), clientSearch(_clientSearch), navigationController(_navigationController), webRequest(_webRequest)
    {
        Command* createClientSaveCommand{new Command(commandController,QString("floppy-disk"),"Save")};
        // Creating a Command Explicitly here for saving action

        Command* findClientSearchCommand(new Command(commandController,QString("search"),"Search"));

        Command* editClientSaveCommand{new Command(commandController,QString("floppy-disk"),"Save")};

        Command* editClientDeleteCommand{new Command(commandController,QString("trash"),"Delete")};

        Command* rssRefreshCommand{new Command(commandController,QString("rotate"),"Refresh")};

        QObject::connect(createClientSaveCommand,&Command::executed,commandController,&CommandController::onCreateClientSaveExecuted);
        // "createClientSaveCommand" is an object of "Command" which will emit/send the signal named "executed" so is sender
        // & "commandController" is a pointed object of "CommandController" which will recieve the signal so called reciever
        // & commandController will call/execute the function/method/slot(EventHandler) to response to the signal

        QObject::connect(findClientSearchCommand,&Command::executed,commandController,&CommandController::onFindClientSearchExecuted);

        QObject::connect(editClientSaveCommand,&Command::executed,commandController,&CommandController::onEditClientSaveExecuted);

        QObject::connect(editClientDeleteCommand,&Command::executed,commandController,&CommandController::onEditClientDeleteExecuted);

        QObject::connect(rssRefreshCommand,&Command::executed,commandController,&CommandController::onRssRefreshExecuted);

        createClientViewContextCommands.append(createClientSaveCommand);
        // Adding the command into QList of Command* type

        findClientViewContextCommands.append(findClientSearchCommand);

        editClientViewContextCommands.append(editClientSaveCommand);
        editClientViewContextCommands.append(editClientDeleteCommand);

        rssViewContextCommands.append(rssRefreshCommand);

        // NOTE: UNTIL NOW WE ARE ONLY HANDLING THE COMMANDS FOR OUR "CreateClientView"
    }
};

CommandController::CommandController(QObject *parent, IDatabaseController *databaseController, models::Client *newClient, models::ClientSearch* clientSearch, INavigationController* navigationController,networking::IWebRequest* webRequest)
    : ICommandController(parent) {
    implementation.reset(new Implementation(this,databaseController,newClient,clientSearch,navigationController,webRequest));
}

CommandController::~CommandController() = default;

QQmlListProperty<Command> CommandController::ui_createClientViewContextCommands() {
    return QQmlListProperty<Command>(this,&implementation->createClientViewContextCommands);
    // The above is converting QList<Command*> object to QQmlListProperty<Command> object using one of its various
    // constructors which is defined as
    // QQmlListProperty<Command>(QObject* parent, QList<Command*> *obj);
}

QQmlListProperty<Command> CommandController::ui_findClientViewContextCommands() {
    return QQmlListProperty<Command>(this,&implementation->findClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_editClientViewContextCommands() {
    return QQmlListProperty<Command>(this,&implementation->editClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_rssViewContextCommands() {
    return QQmlListProperty<Command>(this,&implementation->rssViewContextCommands);
}

void CommandController::onCreateClientSaveExecuted() {
// This is the event handler function.
// Till now it is only showing message in the console that the save command executed

    qDebug() << "Save Command Executed!\n";

    implementation->databaseController->createRow(implementation->newClient->key(),implementation->newClient->id(),implementation->newClient->toJson());

    qDebug() << "New Client Saved.";

    implementation->clientSearch->searchText()->setValue(implementation->newClient->id());
    implementation->clientSearch->search();
    emit implementation->navigationController->goFindClientView();
    implementation->newClient = nullptr;
}

void CommandController::onFindClientSearchExecuted() {

    qDebug() << "Search Command Executed!\n";

    implementation->clientSearch->search();
}

void CommandController::onEditClientSaveExecuted() {

    qDebug() << "Save Command Executed!\n";

    implementation->databaseController->updateRow(implementation->selectedClient->key(),implementation->selectedClient->id(),implementation->selectedClient->toJson());

    emit implementation->navigationController->goDashboardView();

    implementation->selectedClient = nullptr;

    implementation->clientSearch->search();

    qDebug() << "Updated Client Saved.";

}

void CommandController::onEditClientDeleteExecuted() {

    qDebug() << "Delete Command Executed!\n";

    implementation->databaseController->deleteRow(implementation->selectedClient->key(),implementation->selectedClient->id());

    emit implementation->navigationController->goDashboardView();

    implementation->selectedClient = nullptr;

    implementation->clientSearch->search();

    qDebug() << "Client Deleted.";

}

void CommandController::onRssRefreshExecuted() {

    qDebug() << "Refresh Command Executed!\n";

    implementation->webRequest->execute();
}

void CommandController::setSelectedClient(models::Client *client) {
    implementation->selectedClient = client;
}

}
}
