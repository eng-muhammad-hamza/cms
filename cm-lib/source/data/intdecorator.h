#ifndef INTDECORATOR_H
#define INTDECORATOR_H

#include <QObject>
#include <QJsonValue>
#include <QJsonObject>
#include <QScopedPointer>

#include <cm-lib_global.h>
#include <data/datadecorator.h>

namespace cm {
namespace data {
class CMLIB_EXPORT IntDecorator : public DataDecorator
{
    Q_OBJECT
    Q_PROPERTY(int ui_value READ value WRITE setValue NOTIFY valueChanged)
public:
    IntDecorator(Entity *parent = nullptr, const QString& key = "", const QString& label = "", const int& value = 0);
    ~IntDecorator();

    IntDecorator& setValue(const int& value);

    int value() const;

    QJsonValue jsonValue() const override;

    void update(const QJsonObject &jsonObject) override;

signals:
    void valueChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};
}
}
#endif // INTDECORATOR_H
