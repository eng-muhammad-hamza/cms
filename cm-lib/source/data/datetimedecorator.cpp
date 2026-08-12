#include "datetimedecorator.h"

#include <QVariant>

namespace cm {
namespace data {

class DateTimeDecorator::Implementation {
public:
    DateTimeDecorator* dateTimeDecorator{nullptr};
    QDateTime value;

    Implementation(DateTimeDecorator* _dateTimeDecorator, const QDateTime& _value)
        : dateTimeDecorator(_dateTimeDecorator), value(_value) {}
};

DateTimeDecorator::DateTimeDecorator(Entity *parent, const QString &key, const QString &label, const QDateTime &value)
    : DataDecorator(parent,key,label)
{
    implementation.reset(new Implementation(this,value));
}

DateTimeDecorator::~DateTimeDecorator() {}

const QDateTime& DateTimeDecorator::value() const {return implementation->value;}

DateTimeDecorator& DateTimeDecorator::setValue(const QDateTime &value)
{
    if(value != implementation->value){
        // We can Add Verification Mechanism Here
        implementation->value = value;
        emit valueChanged();
        // emitting signal
    }
    return *this;
}

QJsonValue DateTimeDecorator::jsonValue() const {
    return QJsonValue::fromVariant(QVariant(implementation->value.toString(Qt::ISODate)));
}

void DateTimeDecorator::update(const QJsonObject &jsonObject) {
    if (jsonObject.contains(key())) {
        QJsonValue jsonValue = jsonObject.value(key());
        if (jsonValue.isString()) {
            QDateTime dateTime = QDateTime::fromString(jsonValue.toString(),Qt::ISODate);
            setValue(dateTime);
        }
    } else {
        setValue(QDateTime());
    }
}

QString DateTimeDecorator::toIso8601String() const {
    if(implementation->value.isNull()){
        return "Not Set";
    } else {
        return implementation->value.toString(Qt::ISODate);
    }
}

QString DateTimeDecorator::toPrettyDateString() const {
    if(implementation->value.isNull()){
        return "Not Set";
    } else {
        return implementation->value.toString("d MMM yyyy");
    }
}

QString DateTimeDecorator::toPrettyTimeString() const {
    if(implementation->value.isNull()){
        return "Not Set";
    } else {
        return implementation->value.toString("hh:mm ap");
    }
}

QString DateTimeDecorator::toPrettyString() const {
    if(implementation->value.isNull()){
        return "Not Set";
    } else {
        return implementation->value.toString("ddd d MMM yyyy @ HH:mm:ss");
    }
}

}
}
