#include "contact.h"

using namespace cm::data;

namespace cm {
namespace models {

std::map<int,QString> Contact::contactTypeMapper{
    {eContactType::UNKNOWN,""}
    ,{eContactType::TELEPHONE,"Telephone"}
    ,{eContactType::EMAIL,"Email"}
    ,{eContactType::FAX,"Fax"}
};

Contact::Contact(QObject *parent)
    : Entity{parent,"contact"}
{
    contactType = static_cast<EnumeratorDecorator*>(addDataItem(new EnumeratorDecorator(this,"contactType","Contact Type",0,contactTypeMapper)));
    address = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this,"address","Address")));
    contactTypeDropDown = new DropDown(this,contactTypeMapper);
}

Contact::Contact(QObject *parent, const QJsonObject &json)
    : Contact(parent)
{
    update(json);
}

QString Contact::fullContactDetails() const {
    return "Contact Type: " + contactType->valueDescription() + ", Respective No. " + address->value();
}

}
}
