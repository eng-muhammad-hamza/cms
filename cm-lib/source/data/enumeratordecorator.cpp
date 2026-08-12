#include "enumeratordecorator.h"

#include <QVariant>

namespace cm {
namespace data {

class EnumeratorDecorator::Implementation {
public:
    EnumeratorDecorator* enumeratorDecorator{nullptr};
    int value;
    std::map<int,QString> descriptionMapper;

    Implementation(EnumeratorDecorator* _enumeratorDecorator, const int& _value, const std::map<int,QString>& _descriptionMapper)
        : enumeratorDecorator(_enumeratorDecorator), value(_value), descriptionMapper(_descriptionMapper) {}
};

EnumeratorDecorator::EnumeratorDecorator(Entity *parent, const QString &key, const QString &label, const int &value, const std::map<int,QString>& descriptionMapper)
    : DataDecorator(parent,key,label)
{
    implementation.reset(new Implementation(this,value,descriptionMapper));
}

EnumeratorDecorator::~EnumeratorDecorator() {}

int EnumeratorDecorator::value() const {return implementation->value;}

QString EnumeratorDecorator::valueDescription() const {
    if(implementation->descriptionMapper.find(implementation->value) != implementation->descriptionMapper.end()) {
        return implementation->descriptionMapper.at(implementation->value);
    } else {
        return {};
    }
}

EnumeratorDecorator& EnumeratorDecorator::setValue(const int &value)
{
    if(value != implementation->value){
        // We can Add Verification Mechanism Here
        implementation->value = value;
        emit valueChanged();
        // emitting signal
    }
    return *this;
}

QJsonValue EnumeratorDecorator::jsonValue() const {
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void EnumeratorDecorator::update(const QJsonObject &jsonObject) {
    if(jsonObject.contains(key())) {
        setValue(jsonObject.value(key()).toInt());
    } else {
        setValue(0);
    }
}

}
}
