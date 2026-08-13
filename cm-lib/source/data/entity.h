#ifndef ENTITY_H
#define ENTITY_H

#include <map>

#include <QObject>
#include <QScopedPointer>

#include <cm-lib_global.h>
#include <data/datadecorator.h>
#include <data/stringdecorator.h>
#include <data/entitycollection.h>

namespace cm {
namespace data {
class CMLIB_EXPORT Entity : public QObject
{
    Q_OBJECT

public:
    Entity(QObject *parent = nullptr, const QString& key = "");
    Entity(QObject *parent, const QString& key, const QJsonObject& jsonObject);
    virtual ~Entity();

    const QString& key() const;
    const QString& id() const;
    void update(const QJsonObject& jsonObject);
    QJsonObject toJson() const;

signals:
    void childEntitiesChanged();
    void dataDecoratorsChanged();
    void childCollectionsChanged(const QString& collectionKey);

protected:
    Entity* addChild(Entity* entity, const QString& key);
    DataDecorator* addDataItem(DataDecorator* dataDecorator);
    EntityCollectionBase* addChildCollection(EntityCollectionBase* entityCollection);
    void setPrimaryKey(StringDecorator* _primaryKey);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};
}
}


#endif // ENTITY_H
