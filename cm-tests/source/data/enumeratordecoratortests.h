#ifndef ENUMERATORDECORATORTESTS_H
#define ENUMERATORDECORATORTESTS_H

#include <QTest>

#include <data/enumeratordecorator.h>
#include <testsuite.h>

namespace cm {
namespace data {
class EnumeratorDecoratorTests : public TestSuite
{
    Q_OBJECT
public:
    EnumeratorDecoratorTests();

private slots:
    void constructor_givenNoParameters_setsDefaultProperties();
    void constructor_givenParameters_setsProperties();
    void setValue_givenNewValue_updatesValueAndEmitsSignal();
    void setValue_givenSameValue_takesNoAction();
    void jsonValue_whenDefaultValue_returnsJson();
    void jsonValue_whenValueSet_returnsJson();
    void update_whenPresentInJson_updatesValue();
    void update_whenNotPresentInJson_updatesValueToDefault();

private:

    enum eTestType {
        UNKNOWN = 0,VALUE2,VALUE3,VALUE4
    };

    const std::map<int,QString> eTestMap{
        {static_cast<int>(eTestType::UNKNOWN),""},
        {static_cast<int>(eTestType::VALUE2),"Value 2"},
        {static_cast<int>(eTestType::VALUE3),"Value 3"},
        {static_cast<int>(eTestType::VALUE4),"Value 4"}
    };
};
}
}
#endif // ENUMERATORDECORATORTESTS_H
