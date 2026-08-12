#ifndef ENUMERATORDECORATOR_H
#define ENUMERATORDECORATOR_H

#include <map>

#include <QObject>
#include <QJsonValue>
#include <QJsonObject>
#include <QScopedPointer>

#include <cm-lib_global.h>
#include <data/datadecorator.h>

namespace cm {
namespace data {
class CMLIB_EXPORT EnumeratorDecorator : public DataDecorator
{
    Q_OBJECT
    Q_PROPERTY(int ui_value READ value WRITE setValue NOTIFY valueChanged)

    Q_PROPERTY(QString ui_valueDescription READ valueDescription NOTIFY valueChanged)
public:
    EnumeratorDecorator(Entity *parent = nullptr, const QString& key = "", const QString& label = "", const int& value = 0,
                        const std::map<int,QString>& descriptionMapper = std::map<int,QString>());
    ~EnumeratorDecorator();

    EnumeratorDecorator& setValue(const int& value);

    QString valueDescription() const;

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

#endif // ENUMERATORDECORATOR_H
