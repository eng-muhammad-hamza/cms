#include "stringdecoratortests.h"

#include <QSignalSpy>

#include <data/entity.h>

namespace cm {
namespace data {
static StringDecoratorTests instance;

StringDecoratorTests::StringDecoratorTests() : TestSuite("StringDecoratorTests") {}

void StringDecoratorTests::constructor_givenNoParameters_setsDefaultProperties() {
    StringDecorator decorator;
    QCOMPARE(decorator.parentEntity(),nullptr);
    QCOMPARE(decorator.key(),QString(""));
    QCOMPARE(decorator.label(),QString(""));
    QCOMPARE(decorator.value(),"");
}

void StringDecoratorTests::constructor_givenParameters_setsProperties() {
    Entity parentEntity;
    StringDecorator decorator(&parentEntity,"TestingKey","TestingLabel","TestingValue");
    QCOMPARE(decorator.parentEntity(),&parentEntity);
    QCOMPARE(decorator.key(),QString("TestingKey"));
    QCOMPARE(decorator.label(),QString("TestingLabel"));
    QCOMPARE(decorator.value(),"TestingValue");
}

void StringDecoratorTests::setValue_givenNewValue_updatesValueAndEmitsSignal() {
    StringDecorator decorator;
    QSignalSpy valueChangedSpy(&decorator,&StringDecorator::valueChanged);
    QCOMPARE(decorator.value(),"");
    decorator.setValue("TestingValue");
    QCOMPARE(decorator.value(),"TestingValue");
    QCOMPARE(valueChangedSpy.count(),1);
}

void StringDecoratorTests::setValue_givenSameValue_takesNoAction() {
    Entity parentEntity;
    StringDecorator decorator(&parentEntity,"TestingKey","TestingLabel","TestingValue");
    QSignalSpy valueChangedSpy(&decorator,&StringDecorator::valueChanged);
    QCOMPARE(decorator.value(),"TestingValue");
    decorator.setValue("TestingValue");
    QCOMPARE(decorator.value(),"TestingValue");
    QCOMPARE(valueChangedSpy.count(),0);
}

void StringDecoratorTests::jsonValue_whenDefaultValue_returnsJson() {
    StringDecorator decorator;
    QCOMPARE(decorator.jsonValue(),QJsonValue(""));
}

void StringDecoratorTests::jsonValue_whenValueSet_returnsJson() {
    StringDecorator decorator;
    decorator.setValue("TestingValue");
    QCOMPARE(decorator.jsonValue(),QJsonValue("TestingValue"));
}

void StringDecoratorTests::update_whenPresentInJson_updatesValue() {
    Entity parentEntity;
    StringDecorator decorator(&parentEntity,"TestingKey","TestingLabel","TestingValue");
    QSignalSpy valueChangedSpy(&decorator,&StringDecorator::valueChanged);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1","Value 1");
    jsonObject.insert("TestingKey","NewTestingValue");
    jsonObject.insert("Testing Key",88);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(),"NewTestingValue");
    QCOMPARE(valueChangedSpy.count(),1);
}

void StringDecoratorTests::update_whenNotPresentInJson_updatesValueToDefault() {
    Entity parentEntity;
    StringDecorator decorator(&parentEntity,"TestingKey","TestingLabel","TestingValue");
    QSignalSpy valueChangedSpy(&decorator,&StringDecorator::valueChanged);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1","Value 1");
    jsonObject.insert("Testing-Key","TestingValue");
    jsonObject.insert("Testing Key",88);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(),"");
    QCOMPARE(valueChangedSpy.count(),1);
}
}
}
