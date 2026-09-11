#ifndef DATETIMEDECORATORTESTS_H
#define DATETIMEDECORATORTESTS_H

#include <QTest>

#include <data/datetimedecorator.h>
#include <testsuite.h>

namespace cm {
namespace data {
class DateTimeDecoratorTests : public TestSuite
{
    Q_OBJECT
public:
    DateTimeDecoratorTests();

private slots:
    void constructor_givenNoParameters_setsDefaultProperties();
    void constructor_givenParameters_setsProperties();
    void setValue_givenNewValue_updatesValueAndEmitsSignal();
    void setValue_givenSameValue_takesNoAction();
    void jsonValue_whenDefaultValue_returnsJson();
    void jsonValue_whenValueSet_returnsJson();
    void update_whenPresentInJson_updatesValue();
    void update_whenNotPresentInJson_updatesValueToDefault();
    void toIso8601String_whenValueIsNull_returnsStringNotSet();
    void toIso8601String_whenValueIsNotNull_returnsStringFormatted();
    void toPrettyDateString_whenValueIsNull_returnsStringNotSet();
    void toPrettyDateString_whenValueIsNotNull_returnsStringFormatted();
    void toPrettyTimeString_whenValueIsNull_returnsStringNotSet();
    void toPrettyTimeString_whenValueIsNotNull_returnsStringFormatted();
    void toPrettyString_whenValueIsNull_returnsStringNotSet();
    void toPrettyString_whenValueIsNotNull_returnsStringFormatted();
};
}
}
#endif // DATETIMEDECORATORTESTS_H
