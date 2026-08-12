#include "dropdownvalue.h"

namespace cm {
namespace data {

DropDownValue::DropDownValue(QObject *parent, int key, const QString &description)
    : QObject{parent}, key(key), description(description) {}

DropDownValue::~DropDownValue() {}

}
}
