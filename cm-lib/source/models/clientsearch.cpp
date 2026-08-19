#include "clientsearch.h"
#include <QDebug>

using namespace cm::data;
using namespace cm::controllers;

namespace cm {
namespace models {

class ClientSearch::Implementation {
public:
    ClientSearch* clientSearch{nullptr};
    IDatabaseController* databaseController{nullptr};
    StringDecorator* searchText{nullptr};
    EntityCollection<Client>* searchResults{nullptr};

    Implementation(ClientSearch* _clientSearch, IDatabaseController* _databaseController)
        : clientSearch(_clientSearch), databaseController(_databaseController) {}

};

ClientSearch::ClientSearch(QObject *parent, IDatabaseController *databaseController)
    : Entity(parent,"ClientSearch")
{
    implementation.reset(new Implementation(this,databaseController));
    implementation->searchText = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this,"searchText","Search Text")));
    implementation->searchResults = static_cast<EntityCollection<Client>*>(addChildCollection(new EntityCollection<Client>(this,"searchResults")));

    connect(implementation->searchResults,&EntityCollection<Client>::collectionChanged,this,&ClientSearch::searchResultsChanged);
}

ClientSearch::~ClientSearch() {}

StringDecorator* ClientSearch::searchText() {
    return implementation->searchText;
}

QQmlListProperty<Client> ClientSearch::ui_searchResults() {
    return QQmlListProperty<Client>(this,&implementation->searchResults->derivedEntities());
}

void ClientSearch::search()
{
    qDebug() << "Searching for " << implementation->searchText->value() << "...";

    auto resultArray = implementation->databaseController->find("client",implementation->searchText->value());

    implementation->searchResults->update(resultArray);

    qDebug() << "Found " << implementation->searchResults->baseEntities().size() << " matches";
}

}
}
