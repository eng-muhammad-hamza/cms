#include "intdecoratortests.h"

#include <QSignalSpy>

#include <data/entity.h>

namespace cm {
namespace data {
static IntDecoratorTests instance;

IntDecoratorTests::IntDecoratorTests() : TestSuite("IntDecoratorTests") {}

void IntDecoratorTests::constructor_givenNoParameters_setsDefaultProperties() {
    IntDecorator decorator;
    QCOMPARE(decorator.parentEntity(),nullptr);
    QCOMPARE(decorator.key(),QString(""));
    QCOMPARE(decorator.label(),QString(""));
    QCOMPARE(decorator.value(),0);
}

void IntDecoratorTests::constructor_givenParameters_setsProperties() {
    Entity parentEntity;
    IntDecorator decorator(&parentEntity,"TestingKey","TestingLabel",99);
    QCOMPARE(decorator.parentEntity(),&parentEntity);
    QCOMPARE(decorator.key(),QString("TestingKey"));
    QCOMPARE(decorator.label(),QString("TestingLabel"));
    QCOMPARE(decorator.value(),99);
}

void IntDecoratorTests::setValue_givenNewValue_updatesValueAndEmitsSignal() {
    IntDecorator decorator;
    QSignalSpy valueChangedSpy(&decorator,&IntDecorator::valueChanged);
    QCOMPARE(decorator.value(),0);
    decorator.setValue(99);
    QCOMPARE(decorator.value(),99);
    QCOMPARE(valueChangedSpy.count(),1);
}

void IntDecoratorTests::setValue_givenSameValue_takesNoAction() {
    Entity parentEntity;
    IntDecorator decorator(&parentEntity,"TestingKey","TestingLabel",99);
    QSignalSpy valueChangedSpy(&decorator,&IntDecorator::valueChanged);
    QCOMPARE(decorator.value(),99);
    decorator.setValue(99);
    QCOMPARE(decorator.value(),99);
    QCOMPARE(valueChangedSpy.count(),0);
}

void IntDecoratorTests::jsonValue_whenDefaultValue_returnsJson() {
    IntDecorator decorator;
    QCOMPARE(decorator.jsonValue(),QJsonValue(0));
}

void IntDecoratorTests::jsonValue_whenValueSet_returnsJson() {
    IntDecorator decorator;
    decorator.setValue(99);
    QCOMPARE(decorator.jsonValue(),QJsonValue(99));
}

void IntDecoratorTests::update_whenPresentInJson_updatesValue() {
    Entity parentEntity;
    IntDecorator decorator(&parentEntity,"TestingKey","TestingLabel",99);
    QSignalSpy valueChangedSpy(&decorator,&IntDecorator::valueChanged);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1","Value 1");
    jsonObject.insert("TestingKey",148);
    jsonObject.insert("Testing Key",88);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(),148);
    QCOMPARE(valueChangedSpy.count(),1);
}

void IntDecoratorTests::update_whenNotPresentInJson_updatesValueToDefault() {
    Entity parentEntity;
    IntDecorator decorator(&parentEntity,"TestingKey","TestingLabel",99);
    QSignalSpy valueChangedSpy(&decorator,&IntDecorator::valueChanged);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1","Value 1");
    jsonObject.insert("Testing-Key",148);
    jsonObject.insert("Testing Key",88);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(),0);
    QCOMPARE(valueChangedSpy.count(),1);
}
}
}
