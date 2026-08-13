#include "entity.h"

#include <QUuid>

namespace cm{
namespace data{

class Entity::Implementation{
public:
    Entity* entity{nullptr};
    QString key;
    QString id;
    StringDecorator* primaryKey{nullptr};
    std::map<QString,Entity*> childEntities;
    std::map<QString,DataDecorator*> dataDecorators;
    std::map<QString,EntityCollectionBase*> childCollections;

    Implementation(Entity* _entity, const QString& _key)
        : entity(_entity), key(_key), id(QUuid::createUuid().toString()) {}
};

Entity::Entity(QObject *parent, const QString &key)
    : QObject(parent) {
    implementation.reset(new Implementation(this,key));
}

Entity::Entity(QObject *parent, const QString &key, const QJsonObject &jsonObject)
    : Entity(parent,key) {
    update(jsonObject);
}

Entity::~Entity() {}

const QString& Entity::key() const {return implementation->key;}

const QString& Entity::id() const {
    if(implementation->primaryKey != nullptr && !implementation->primaryKey->value().isEmpty()) {
        return implementation->primaryKey->value();
    }
    return implementation->id;
}

Entity* Entity::addChild(Entity *entity, const QString &key) {
    if(implementation->childEntities.find(key) == std::end(implementation->childEntities)) {
        implementation->childEntities[key] = entity;
        emit childEntitiesChanged();
    }
    return entity;
}

DataDecorator* Entity::addDataItem(DataDecorator *dataDecorator) {
    if(implementation->dataDecorators.find(dataDecorator->key()) == std::end(implementation->dataDecorators)) {
        implementation->dataDecorators[dataDecorator->key()] = dataDecorator;
        emit dataDecoratorsChanged();
    }
    return dataDecorator;
}

void Entity::setPrimaryKey(StringDecorator *_primaryKey) {
    implementation->primaryKey = _primaryKey;
}

QJsonObject Entity::toJson() const {
    QJsonObject jsonObject;
    jsonObject.insert("id",implementation->id);
    for(std::pair<QString,DataDecorator*> dataDecoratorPair : implementation->dataDecorators) {
        jsonObject.insert(dataDecoratorPair.first,dataDecoratorPair.second->jsonValue());
    }
    for(std::pair<QString,Entity*> childEntityPair : implementation->childEntities) {
        jsonObject.insert(childEntityPair.first,childEntityPair.second->toJson());
    }
    for(std::pair<QString,EntityCollectionBase*> childCollectionPair : implementation->childCollections) {
        QJsonArray jsonArray;
        for(Entity* entity : childCollectionPair.second->baseEntities()) {
            jsonArray.append(entity->toJson());
        }
        jsonObject.insert(childCollectionPair.first,jsonArray);
    }
    return jsonObject;
}

void Entity::update(const QJsonObject &jsonObject){
    if(jsonObject.contains("id")) {
        implementation->id = jsonObject.value("id").toString();
    }
    for(std::pair<QString,DataDecorator*> dataDecoratorPair : implementation->dataDecorators) {
        dataDecoratorPair.second->update(jsonObject);
    }
    for(std::pair<QString,Entity*> childEntityPair : implementation->childEntities) {
        childEntityPair.second->update(jsonObject.value(childEntityPair.first).toObject());
    }
    for(std::pair<QString,EntityCollectionBase*> childCollectionPair : implementation->childCollections) {
        childCollectionPair.second->update(jsonObject.value(childCollectionPair.first).toArray());
    }
}

EntityCollectionBase* Entity::addChildCollection(EntityCollectionBase *entityCollection) {
    if(implementation->childCollections.find(entityCollection->getKey()) == std::end(implementation->childCollections)) {
        implementation->childCollections[entityCollection->getKey()] = entityCollection;
        emit childCollectionsChanged(entityCollection->getKey());
    }
    return entityCollection;
}

}
}

