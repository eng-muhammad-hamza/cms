#ifndef DATADECORATOR_H
#define DATADECORATOR_H

#include <QObject>
#include <QJsonValue>
#include <QJsonObject>
#include <QScopedPointer>

#include <cm-lib_global.h>

///
/// This Decorator Class is base class to those classes which are made only to enhance our existing types means our
/// Existing type is "QString" but in our program we want our data to be input-verified, sereialized and deserialized
/// into JSON Objects or values to save data into JSON Files which will involve providing a unique key to access that
/// data.
/// NOTE: WE CAN DO ALL OF THESE CAPABILITIES ON HARD BASIS BUT THAT WOULD TAKE ADDITIONAL CODE FOR EACH DATA TYPE
/// AND FOR EACH TIME TO DO THE SAME THING SO THE DECORATOR CLASSES ARE TO MAKE CODE REUSEABLE AND ALSO IF FUTURE CHANGES
/// OCCUR WE ONLY HAVE TO CORRECT OR ENHANCE THESE CLASSES WITHOUT INTERACTING OR WITH A LITTLE INTERACTION WITH
/// THE ORIGINAL MODEL(MAIN DATA) CODE.
///

namespace cm{
namespace data {

class Entity;

class CMLIB_EXPORT DataDecorator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ui_label READ label CONSTANT)
    // This property is to access the label describing the requirement for this type field in the ui means
    // <label> <Input> ==> Name: ________

public:
    DataDecorator(Entity *parent = nullptr, const QString& key = "", const QString& label = "");
    // We declare here the Entity class as our parent. We will be going to an extremely basic class which
    // can be inherited to our all other data classes and it will provide the basic and similar functionalities
    // for all the classes. Thus all these decorated data-members will be a part of our entity class which
    // then eventually become the data-members of all our other data classes

    virtual ~DataDecorator();

    const QString& key() const;
    const QString& label() const;
    Entity* parentEntity();

    virtual QJsonValue jsonValue() const = 0;
    // It is Serializer Function

    virtual void update(const QJsonObject& jsonObject) = 0;
    // It is De-Serializer Function

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
signals:
};
}
}


#endif // DATADECORATOR_H
