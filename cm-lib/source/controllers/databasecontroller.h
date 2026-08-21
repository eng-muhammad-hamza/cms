#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QScopedPointer>

#include <controllers/IDatabaseController.h>

#include <cm-lib_global.h>

namespace cm {
namespace controllers {

class CMLIB_EXPORT DatabaseController : public IDatabaseController
{
    Q_OBJECT
public:
    explicit DatabaseController(QObject *parent = nullptr);
    ~DatabaseController();

    bool createRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const override;
    bool deleteRow(const QString& tableName, const QString& id) const override;
    QJsonArray find(const QString& tableName, const QString& searchText) const override;
    QJsonObject readRow(const QString& tableName, const QString& id) const override;
    bool updateRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const override;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // DATABASECONTROLLER_H
