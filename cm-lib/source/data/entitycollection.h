#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H

#include <QObject>
#include <QJsonValue>
#include <QJsonArray>

#include <cm-lib_global.h>

namespace cm {
namespace data {
class Entity;

///
/// Note: We want to make entity-collection class as a template class but we also want that class to provide the
/// QObject functionalities. The classes DIRECTLY INHERITING FROM QObject can't be TEMPLATED so we indirectly
/// inherit our original entity-collection class from our EntityCollectionObject class which inturn inherit
///

class CMLIB_EXPORT EntityCollectionObject : public QObject {
    Q_OBJECT
public:
    EntityCollectionObject(QObject* _parent = nullptr) : QObject(_parent) {}
    virtual ~EntityCollectionObject() {}
signals:
    void collectionChanged();
};

///
/// We have two requirements. Firstly, the UI needs a QList of derived types (for example,
/// Client*) so that it can access all the properties specific to a client and display all the data.
/// Secondly, our Entity class needs a vector of base types (Entity*) so that it can iterate its collections
/// without caring exactly which type it is dealing with. The way we achieve this is to declare two template
/// methods but delay defining them until later. derivedEntities() will be used when the consumer wants a
/// collection of the derived type, while baseEntities() will be used when the consumer just wants access to
/// the base interface.
///

class EntityCollectionBase : public EntityCollectionObject {
    QString key;
public:
    EntityCollectionBase(QObject* parent = nullptr, const QString& _key = "")
        : EntityCollectionObject(parent), key(_key) {}
    virtual ~EntityCollectionBase() {}
    QString getKey() const {return key;}

    virtual void clear() = 0;
    virtual void update(const QJsonArray& jsonArray) = 0;
    virtual std::vector<Entity*> baseEntities() = 0;

    template<class T>
    QList<T*>& derivedEntities();

    template<class T>
    T* addEntity(T* entity);
};

template<typename T>
class EntityCollection : public EntityCollectionBase {
    QList<T*> collection;
public:
    EntityCollection(QObject* parent = nullptr, const QString& key = "")
        : EntityCollectionBase(parent,key) {}

    ~EntityCollection() {}

    void clear() override {
        for(auto entity : collection) {
            entity->deleteLater();
        }
        collection.clear();
    }

    void update(const QJsonArray &jsonArray) override {
        clear();
        for(const QJsonValue& jsonValue : jsonArray) {
            addEntity(new T(this,jsonValue.toObject()));
        }
    }

    std::vector<Entity*> baseEntities() override {
        std::vector<Entity*> returnValue;
        for(T* entity : collection) {
            returnValue.push_back(entity);
        }
        return returnValue;
    }

    QList<T*>& derivedEntities() {return collection;}

    T* addEntity(T* entity) {
        if(!collection.contains(entity)) {
            collection.append(entity);
            EntityCollection::collectionChanged();
        }
        return entity;
    }
};

template<class T>
QList<T*>& EntityCollectionBase::derivedEntities() {
    return dynamic_cast<const EntityCollection<T>&>(*this).derivedEntities();
}

template<class T>
T* EntityCollectionBase::addEntity(T* entity) {
    return dynamic_cast<const EntityCollection<T>&>(*this).addEntity(entity);
}

}

}

#endif // ENTITYCOLLECTION_H
