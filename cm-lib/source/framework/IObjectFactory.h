#ifndef IOBJECTFACTORY_H
#define IOBJECTFACTORY_H

#include <controllers/ICommandController.h>
#include <controllers/IDatabaseController.h>
#include <controllers/INavigationController.h>
#include <models/client.h>
#include <models/clientsearch.h>
#include <networking/INetworkAccessManager.h>
#include <networking/IWebRequest.h>

namespace cm {
namespace framework {

class IObjectFactory
{
public:
    virtual ~IObjectFactory(){}
    virtual models::Client* createClient(QObject* parent) const = 0;
    virtual models::ClientSearch* createClientSearch(QObject* parent, controllers::IDatabaseController* databaseController) const = 0;
    virtual controllers::ICommandController* createCommandController(QObject* parent, controllers::IDatabaseController* databaseController,
                                                                    controllers::INavigationController* navigationController,
                                                                    models::Client* newClient, models::ClientSearch* clientSearch,
                                                                    networking::IWebRequest* rssWebRequest) const = 0;
    virtual controllers::IDatabaseController* createDatabaseController(QObject* parent) const = 0;
    virtual controllers::INavigationController* createNavigationController(QObject* parent) const = 0;
    virtual networking::INetworkAccessManager* createNetworkAccessManager(QObject* parent) const = 0;
    virtual networking::IWebRequest* createWebRequest(QObject* parent, networking::INetworkAccessManager* networkAccessManager, const QUrl& url) const = 0;
};
}
}

#endif // IOBJECTFACTORY_H
