#include "intdecorator.h"

#include <QVariant>

namespace cm {
namespace data {

class IntDecorator::Implementation {
public:
    IntDecorator* intDecorator{nullptr};
    int value;

    Implementation(IntDecorator* _intDecorator, const int& _value)
        : intDecorator(_intDecorator), value(_value) {}
};

IntDecorator::IntDecorator(Entity *parent, const QString &key, const QString &label, const int &value)
    : DataDecorator(parent,key,label)
{
    implementation.reset(new Implementation(this,value));
}

IntDecorator::~IntDecorator() {}

int IntDecorator::value() const {return implementation->value;}

IntDecorator& IntDecorator::setValue(const int &value)
{
    if(value != implementation->value){
        // We can Add Verification Mechanism Here
        implementation->value = value;
        emit valueChanged();
        // emitting signal
    }
    return *this;
}

QJsonValue IntDecorator::jsonValue() const {
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void IntDecorator::update(const QJsonObject &jsonObject) {
    if(jsonObject.contains(key())) {
        setValue(jsonObject.value(key()).toInt());
    } else {
        setValue(0);
    }
}

}
}
