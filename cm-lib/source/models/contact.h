#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>

#include <cm-lib_global.h>
#include <data/stringdecorator.h>
#include <data/datetimedecorator.h>
#include <data/enumeratordecorator.h>
#include <data/entity.h>
#include <data/dropdown.h>

namespace cm {
namespace models {

class CMLIB_EXPORT Contact : public data::Entity
{
    Q_OBJECT

    Q_PROPERTY(data::StringDecorator* ui_address MEMBER address CONSTANT)
    Q_PROPERTY(data::EnumeratorDecorator* ui_contactType MEMBER contactType CONSTANT)
    Q_PROPERTY(cm::data::DropDown* ui_contactTypeDropDown MEMBER contactTypeDropDown CONSTANT)

    Q_PROPERTY(QString ui_fullContactDetails READ fullContactDetails CONSTANT)

public:
    enum eContactType {
        UNKNOWN = 0, TELEPHONE, EMAIL, FAX
    };

    explicit Contact(QObject *parent = nullptr);
    Contact(QObject *parent, const QJsonObject& json);

    static std::map<int,QString> contactTypeMapper;

    data::EnumeratorDecorator* contactType{nullptr};
    data::StringDecorator* address{nullptr};
    data::DropDown* contactTypeDropDown{nullptr};

    QString fullContactDetails() const;

signals:
};

}
}


#endif // CONTACT_H
