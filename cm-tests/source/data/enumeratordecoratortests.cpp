#include "enumeratordecoratortests.h"
#include <QSignalSpy>
#include <data/entity.h>
#include <QDebug>

namespace cm {
namespace data {

static EnumeratorDecoratorTests instance;

EnumeratorDecoratorTests::EnumeratorDecoratorTests() : TestSuite("EnumeratorDecoratorTests") {}

void EnumeratorDecoratorTests::constructor_givenNoParameters_setsDefaultProperties() {
    EnumeratorDecorator decorator;
    QCOMPARE(decorator.parentEntity(), nullptr);
    QCOMPARE(decorator.key(), QString(""));
    QCOMPARE(decorator.label(), QString(""));
    QCOMPARE(decorator.value(), static_cast<int>(eTestType::UNKNOWN));
    QCOMPARE(decorator.valueDescription(), QString());
}

// void EnumeratorDecoratorTests::constructor_givenParameters_setsProperties() {
//     Entity parentEntity;
//     EnumeratorDecorator decorator(&parentEntity, "TestingKey", "TestingLabel", 1, eTestMap);
//     QCOMPARE(decorator.parentEntity(), &parentEntity);
//     QCOMPARE(decorator.key(), QString("TestingKey"));
//     QCOMPARE(decorator.label(), QString("TestingLabel"));
//     QCOMPARE(decorator.value(), 1);
//     QCOMPARE(decorator.valueDescription(), QString("Value 2"));
// }

void EnumeratorDecoratorTests::constructor_givenParameters_setsProperties() {
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity,"TestingKey","TestingLabel",static_cast<int>(eTestType::VALUE2),eTestMap);
    QCOMPARE(decorator.parentEntity(),&parentEntity);
    QCOMPARE(decorator.key(),QString("TestingKey"));
    QCOMPARE(decorator.label(),QString("TestingLabel"));
    QCOMPARE(decorator.value(),static_cast<int>(eTestType::VALUE2));
    QCOMPARE(decorator.valueDescription(),QString("Value 2"));
}

// void EnumeratorDecoratorTests::setValue_givenNewValue_updatesValueAndEmitsSignal() {
//     EnumeratorDecorator decorator(nullptr, "TestingKey", "TestingLabel", 0, eTestMap);
//     QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);
//     QCOMPARE(decorator.value(), 0);

//     qDebug() << "Initial value description: " << decorator.valueDescription();
//     decorator.setValue(1);
//     qDebug() << "New value: " << decorator.value();
//     qDebug() << "New value description: " << decorator.valueDescription();

//     QCOMPARE(decorator.value(), 1);
//     QCOMPARE(decorator.valueDescription(), QString("Value 2"));
//     QCOMPARE(valueChangedSpy.count(), 1);
// }

void EnumeratorDecoratorTests::setValue_givenNewValue_updatesValueAndEmitsSignal() {
    EnumeratorDecorator decorator(nullptr, "TestingKey", "TestingLabel", static_cast<int>(eTestType::UNKNOWN), eTestMap);
    QSignalSpy valueChangedSpy(&decorator,&EnumeratorDecorator::valueChanged);
    QCOMPARE(decorator.value(),static_cast<int>(eTestType::UNKNOWN));
    decorator.setValue(static_cast<int>(eTestType::VALUE2));
    QCOMPARE(decorator.value(),static_cast<int>(eTestType::VALUE2));
    QCOMPARE(decorator.valueDescription(),QString("Value 2"));
    QCOMPARE(valueChangedSpy.count(),1);
}

// void EnumeratorDecoratorTests::setValue_givenSameValue_takesNoAction() {
//     Entity parentEntity;
//     EnumeratorDecorator decorator(&parentEntity, "TestingKey", "TestingLabel", 1, eTestMap);
//     QSignalSpy valueChangedSpy(&decorator, &EnumeratorDecorator::valueChanged);
//     QCOMPARE(decorator.value(), 1);

//     qDebug() << "Initial value description: " << decorator.valueDescription();
//     decorator.setValue(1);
//     qDebug() << "Value after setValue(1): " << decorator.value();
//     qDebug() << "Value description after setValue(1): " << decorator.valueDescription();

//     QCOMPARE(decorator.value(), 1);
//     QCOMPARE(decorator.valueDescription(), QString("Value 2"));
//     QCOMPARE(valueChangedSpy.count(), 0);
// }

void EnumeratorDecoratorTests::setValue_givenSameValue_takesNoAction() {
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity,"TestingKey","TestingLabel",static_cast<int>(eTestType::VALUE2),eTestMap);
    QSignalSpy valueChangedSpy(&decorator,&EnumeratorDecorator::valueChanged);
    QCOMPARE(decorator.value(),static_cast<int>(eTestType::VALUE2));
    decorator.setValue(static_cast<int>(eTestType::VALUE2));
    QCOMPARE(decorator.value(),static_cast<int>(eTestType::VALUE2));
    QCOMPARE(decorator.valueDescription(),QString("Value 2"));
    QCOMPARE(valueChangedSpy.count(),0);
}

void EnumeratorDecoratorTests::jsonValue_whenDefaultValue_returnsJson() {
    EnumeratorDecorator decorator;
    QCOMPARE(decorator.jsonValue(),QJsonValue(static_cast<int>(eTestType::UNKNOWN)));
}

void EnumeratorDecoratorTests::jsonValue_whenValueSet_returnsJson() {
    EnumeratorDecorator decorator;
    decorator.setValue(2);
    QCOMPARE(decorator.jsonValue(), QJsonValue(static_cast<int>(eTestType::VALUE3)));
}

void EnumeratorDecoratorTests::update_whenPresentInJson_updatesValue() {
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity,"TestingKey","TestingLabel",static_cast<int>(eTestType::VALUE2),eTestMap);
    QSignalSpy valueChangedSpy(&decorator,&EnumeratorDecorator::valueChanged);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1","Value 1");
    jsonObject.insert("TestingKey",static_cast<int>(eTestType::VALUE3));
    jsonObject.insert("Testing Key",88);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(),static_cast<int>(eTestType::VALUE3));
    QCOMPARE(decorator.valueDescription(),QString("Value 3"));
    QCOMPARE(valueChangedSpy.count(),1);
}

void EnumeratorDecoratorTests::update_whenNotPresentInJson_updatesValueToDefault() {
    Entity parentEntity;
    EnumeratorDecorator decorator(&parentEntity,"TestingKey","TestingLabel",static_cast<int>(eTestType::VALUE2),eTestMap);
    QSignalSpy valueChangedSpy(&decorator,&EnumeratorDecorator::valueChanged);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1","Value 1");
    jsonObject.insert("Testing-Key",2);
    jsonObject.insert("Testing Key",88);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(),static_cast<int>(eTestType::UNKNOWN));
    QCOMPARE(decorator.valueDescription(),QString(""));
    QCOMPARE(valueChangedSpy.count(),1);
}

}
}
