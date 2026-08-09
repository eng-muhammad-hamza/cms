#include "stringdecorator.h"

#include <QVariant>

namespace cm {
namespace data {

class StringDecorator::Implementation {
public:
    StringDecorator* stringDecorator{nullptr};
    QString value;

    Implementation(StringDecorator* _stringDecorator, const QString& _value)
        : stringDecorator(_stringDecorator), value(_value) {}
};

StringDecorator::StringDecorator(Entity *parent, const QString &key, const QString &label, const QString &value)
    : DataDecorator(parent,key,label)
{
    implementation.reset(new Implementation(this,value));
}

StringDecorator::~StringDecorator() {}

const QString& StringDecorator::value() const {return implementation->value;}

StringDecorator& StringDecorator::setValue(const QString &value)
{
    if(value != implementation->value){
        // We can Add Verification Mechanism Here
        implementation->value = value;
        emit valueChanged();
        // emitting signal
    }
    return *this;
}

QJsonValue StringDecorator::jsonValue() const {
    return QJsonValue::fromVariant(QVariant(implementation->value));
    // "fromVariant" converts a QVariant Value to the appropriate QJsonValue.
    // We Did this so that in GUI Applications we actually don't know how user will interact with
    // the system and what input will he enter or something related so we are completely depending
    // on runtime
}

void StringDecorator::update(const QJsonObject &jsonObject) {
    if(jsonObject.contains(key())) {
        setValue(jsonObject.value(key()).toString());
        // Here .value() function returns QJsonValue which have .toString() function to convert it
        // to string
    } else {
        setValue("");
    }
}

}
}

///
/// QVariant is a class provided by the Qt framework that acts as a container for any type of data.
/// It is a union-like class that can store values of different types, which can be retrieved later
/// by converting it back to the original type. This makes QVariant highly versatile and useful in
/// scenarios where the data type is not known in advance or can change dynamically.
/// A QVariant object can be created and assigned a value of any supported type.
/// QVariant v1 = 42;              // Stores an integer
/// QVariant v2 = 3.14;            // Stores a double
/// QVariant v3 = "Hello, World!"; // Stores a QString
/// QVariant v4 = QByteArray("Some binary data"); // Stores a QByteArray
/// Uses:
/// In applications where the type of data may vary, such as in model/view frameworks, QVariant provides
/// a way to handle data dynamically without knowing the type beforehand.
/// QVariant is commonly used in databases and settings storage (e.g., QSettings) to store values of
/// various types in a single container.
/// QVariant facilitates the passing of arguments between signals and slots, especially when the argument
/// types are not known in advance.
///
/// NOTE: QVARIANT CANT CONTAIN MULTIPLE TYPES OF DATA AT ONCE.
/// A QVariant object itself can only hold one type of data at a time. It is essentially a wrapper around
/// a single value that can be of any type supported by QVariant, but not multiple types simultaneously.
/// However, you can work around this limitation by using a QVariant to store containers (like QVariantList
/// or QVariantMap) that themselves hold multiple values of potentially different types. BUT THIS CAN BE
/// ACHEIVED BY THE FOLLOWINGS:
/// 1. Using QVariantList: QVariantList is essentially a QList<QVariant>, meaning it can hold multiple
/// QVariant objects, each potentially containing a different type of data.
///
/// #include <QVariant>
/// #include <QList>
/// #include <QDebug>
/// int main() {
///     QVariantList list;
///     list.append(QVariant(42));              // int
///     list.append(QVariant(3.14));            // double
///     list.append(QVariant("Hello, World!")); // QString
///     for (const QVariant &v : list) {
///         if (v.canConvert<int>()) {
///             qDebug() << "int:" << v.toInt();
///         } else if (v.canConvert<double>()) {
///             qDebug() << "double:" << v.toDouble();
///         } else if (v.canConvert<QString>()) {
///             qDebug() << "QString:" << v.toString();
///         }
///     }
/// }
///
/// 2. Using QVariantMap
/// QVariantMap is a QMap<QString, QVariant>, allowing you to associate keys with values that can be of different types.
///
/// #include <QVariant>
/// #include <QMap>
/// #include <QDebug>
/// int main() {
///     QVariantMap map;
///     map.insert("integer", QVariant(42));              // int
///     map.insert("double", QVariant(3.14));             // double
///     map.insert("string", QVariant("Hello, World!"));  // QString
///     foreach (const QString &key, map.keys()) {
///         QVariant value = map.value(key);
///         if (value.canConvert<int>()) {
///             qDebug() << key << "is int:" << value.toInt();
///         } else if (value.canConvert<double>()) {
///             qDebug() << key << "is double:" << value.toDouble();
///         } else if (value.canConvert<QString>()) {
///             qDebug() << key << "is QString:" << value.toString();
///         }
///     }
/// }
///
/// 3. Storing and Retrieving Custom Types
/// You can also store custom types in QVariant by registering them with the Qt meta-object system using
/// Q_DECLARE_METATYPE and qRegisterMetaType.
///
/// #include <QVariant>
/// #include <QDebug>
/// #include <QMetaType>
///    //Define a custom type
/// struct MyCustomType {
///     int id;
///     QString name;
/// };
///    // Register the custom type
/// Q_DECLARE_METATYPE(MyCustomType)
/// int main() {
///     qRegisterMetaType<MyCustomType>("MyCustomType");
///     MyCustomType customValue = { 1, "Custom Data" };
///     QVariant variant = QVariant::fromValue(customValue);
///     if (variant.canConvert<MyCustomType>()) {
///         MyCustomType retrievedValue = variant.value<MyCustomType>();
///         qDebug() << "Custom type id:" << retrievedValue.id;
///         qDebug() << "Custom type name:" << retrievedValue.name;
///     }
/// }
///

