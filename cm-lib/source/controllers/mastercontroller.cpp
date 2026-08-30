#include "mastercontroller.h"

#include <networking/networkaccessmanager.h>
#include <networking/webrequest.h>

namespace cm {
namespace controllers {

class MasterController::Implementation
{
public:
    Implementation(MasterController* _masterController, framework::IObjectFactory* _objectFactory)
        : masterController(_masterController), objectFactory(_objectFactory) {
        databaseController = objectFactory->createDatabaseController(masterController);
        navigationController = objectFactory->createNavigationController(masterController);
        newClient = objectFactory->createClient(masterController);
        clientSearch = objectFactory->createClientSearch(masterController,databaseController);
        networkAccessManager = objectFactory->createNetworkAccessManager(masterController);
        webRequest = objectFactory->createWebRequest(masterController,networkAccessManager,QUrl("http://feeds.bbci.co.uk/news/rss.xml?edition=uk"));
        QObject::connect(webRequest,&networking::WebRequest::requestComplete,masterController,&MasterController::onRssReplyRecieved);
        commandController = objectFactory->createCommandController(masterController,databaseController,navigationController,newClient,clientSearch,webRequest);
    }

    MasterController* masterController{nullptr};
    framework::IObjectFactory* objectFactory{nullptr};
    IDatabaseController* databaseController{nullptr};
    INavigationController* navigationController{nullptr};
    models::Client* newClient{nullptr};
    models::ClientSearch* clientSearch{nullptr};
    networking::INetworkAccessManager* networkAccessManager{nullptr};
    networking::IWebRequest* webRequest{nullptr};
    ICommandController* commandController{nullptr};
    rss::RssChannel* rssChannel{nullptr};
    QString welcomeMessage{"Hello Boy!"};
};

MasterController::MasterController(QObject *parent, framework::IObjectFactory *objectFactory)
    : QObject(parent) {
    implementation.reset(new Implementation(this,objectFactory));
}

INavigationController* MasterController::navigationController() {
    return implementation->navigationController;
}

ICommandController* MasterController::commandController() {
    return implementation->commandController;
}

IDatabaseController* MasterController::databaseController() {
    return implementation->databaseController;
}

models::Client* MasterController::newClient() {
    return implementation->newClient;
}

models::ClientSearch* MasterController::clientSearch() {
    return implementation->clientSearch;
}

rss::RssChannel* MasterController::rssChannel() {
    return implementation->rssChannel;
}

QString MasterController::welcomeMessage() const {
    return implementation->welcomeMessage;
}

MasterController::~MasterController() {}

void MasterController::selectClient(models::Client *client) {
    emit implementation->navigationController->goEditClientView(client);
}

void MasterController::onRssReplyRecieved(int statusCode, QByteArray body) {
    qDebug() << "Recieved Rss Response Code " << statusCode << ": ";
    qDebug() << body;

    if(implementation->rssChannel) {
        implementation->rssChannel->deleteLater();
        implementation->rssChannel = nullptr;
        emit rssChannelChanged();
    }
    implementation->rssChannel = rss::RssChannel::fromXml(body, this);
    emit rssChannelChanged();
}
}
}
