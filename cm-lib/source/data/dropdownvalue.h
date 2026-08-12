#ifndef DROPDOWNVALUE_H
#define DROPDOWNVALUE_H

#include <QObject>
#include <cm-lib_global.h>

namespace cm {
namespace data {

class CMLIB_EXPORT DropDownValue : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int ui_key MEMBER key CONSTANT)
    Q_PROPERTY(QString ui_description MEMBER description CONSTANT)
public:
    explicit DropDownValue(QObject *parent = nullptr, int key = 0, const QString& description = "");
    ~DropDownValue();

    int key{0};
    QString description{""};
};

}
}
#endif // DROPDOWNVALUE_H
