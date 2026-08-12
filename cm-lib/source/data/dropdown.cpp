#include "dropdown.h"

namespace cm {
namespace data {

class DropDown::Implementation {
public:
    DropDown* dropDown{nullptr};
    QList<DropDownValue*> values;

    Implementation(DropDown* _dropDown, const std::map<int,QString>& _values)
        : dropDown(_dropDown)
    {
        for(auto pair : _values) {
            values.append(new DropDownValue(dropDown,pair.first,pair.second));
        }
    }
};

DropDown::DropDown(QObject *parent, const std::map<int, QString> &values)
    : QObject(parent)
{
    implementation.reset(new Implementation(this,values));
}

DropDown::~DropDown() {}

QString DropDown::findDescriptionForDropDownValue(int valueKey) const
{
    for (auto value : implementation->values) {
        if (value->key == valueKey) {
            if(!value->description.isEmpty()) {
                return value->description;
            }
            break;
        }
    }
    return "Select >";
}
QQmlListProperty<DropDownValue> DropDown::ui_values()
{
    return QQmlListProperty<DropDownValue>(this, &implementation->values);
}

}}
