#ifndef DROPDOWN_H
#define DROPDOWN_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <cm-lib_global.h>
#include <data/dropdownvalue.h>

namespace cm {
namespace data {

class CMLIB_EXPORT DropDown : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<DropDownValue> ui_values READ ui_values CONSTANT)
public:
    explicit DropDown(QObject *parent = nullptr, const std::map<int,QString>& values = std::map<int,QString>());
    ~DropDown();

    QQmlListProperty<DropDownValue> ui_values();
public slots:
    QString findDescriptionForDropDownValue(int valueKey) const;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}
#endif // DROPDOWN_H
