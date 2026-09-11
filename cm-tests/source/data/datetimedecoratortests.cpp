#include "datetimedecoratortests.h"

#include <QSignalSpy>

#include <data/entity.h>

namespace cm {
namespace data {
static DateTimeDecoratorTests instance;

DateTimeDecoratorTests::DateTimeDecoratorTests() : TestSuite("DateTimeDecoratorTests") {}

void DateTimeDecoratorTests::constructor_givenNoParameters_setsDefaultProperties() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.parentEntity(),nullptr);
    QCOMPARE(decorator.key(),QString(""));
    QCOMPARE(decorator.label(),QString(""));
    QCOMPARE(decorator.value(),QDateTime());
}

void DateTimeDecoratorTests::constructor_givenParameters_setsProperties() {
    Entity parentEntity;
    QDateTime testDateTime = QDateTime::currentDateTime();
    DateTimeDecorator decorator(&parentEntity, "TestingKey", "TestingLabel", testDateTime);
    QCOMPARE(decorator.parentEntity(), &parentEntity);
    QCOMPARE(decorator.key(), QString("TestingKey"));
    QCOMPARE(decorator.label(), QString("TestingLabel"));
    QCOMPARE(decorator.value(), testDateTime);
}


void DateTimeDecoratorTests::setValue_givenNewValue_updatesValueAndEmitsSignal() {
    DateTimeDecorator decorator;
    QDateTime testDateTime = QDateTime::currentDateTime();
    QSignalSpy valueChangedSpy(&decorator,&DateTimeDecorator::valueChanged);
    QCOMPARE(decorator.value(),QDateTime());
    decorator.setValue(testDateTime);
    QCOMPARE(decorator.value(),testDateTime);
    QCOMPARE(valueChangedSpy.count(),1);
}

void DateTimeDecoratorTests::setValue_givenSameValue_takesNoAction() {
    Entity parentEntity;
    QDateTime testDateTime = QDateTime::currentDateTime();
    DateTimeDecorator decorator(&parentEntity,"TestingKey","TestingLabel",testDateTime);
    QSignalSpy valueChangedSpy(&decorator,&DateTimeDecorator::valueChanged);
    QCOMPARE(decorator.value(),testDateTime);
    decorator.setValue(testDateTime);
    QCOMPARE(decorator.value(),testDateTime);
    QCOMPARE(valueChangedSpy.count(),0);
}

void DateTimeDecoratorTests::jsonValue_whenDefaultValue_returnsJson() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.jsonValue(),QJsonValue(QDateTime().toString(Qt::ISODate)));
}

void DateTimeDecoratorTests::jsonValue_whenValueSet_returnsJson() {
    DateTimeDecorator decorator;
    QDateTime testDateTime = QDateTime::currentDateTime();
    decorator.setValue(testDateTime);
    QCOMPARE(decorator.jsonValue(),QJsonValue(testDateTime.toString(Qt::ISODate)));
}

void DateTimeDecoratorTests::update_whenPresentInJson_updatesValue() {
    Entity parentEntity;
    DateTimeDecorator decorator(&parentEntity,"TestingKey","TestingLabel",QDateTime::currentDateTime());
    QSignalSpy valueChangedSpy(&decorator,&DateTimeDecorator::valueChanged);
    QJsonObject jsonObject;
    QDateTime testDateTime = QDateTime::currentDateTime();
    jsonObject.insert("Key 1","Value 1");
    jsonObject.insert("TestingKey",QJsonValue(testDateTime.toString(Qt::ISODate)));
    jsonObject.insert("Testing Key",88);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value().toString(Qt::ISODate),testDateTime.toString(Qt::ISODate));
    QCOMPARE(valueChangedSpy.count(),1);
}

void DateTimeDecoratorTests::update_whenNotPresentInJson_updatesValueToDefault() {
    Entity parentEntity;
    DateTimeDecorator decorator(&parentEntity,"TestingKey","TestingLabel",QDateTime::currentDateTime());
    QSignalSpy valueChangedSpy(&decorator,&DateTimeDecorator::valueChanged);
    QJsonObject jsonObject;
    jsonObject.insert("Key 1","Value 1");
    jsonObject.insert("Testing-Key","TestingValue");
    jsonObject.insert("Testing Key",88);
    decorator.update(jsonObject);
    QCOMPARE(decorator.value(),QDateTime());
    QCOMPARE(valueChangedSpy.count(),1);
}

void DateTimeDecoratorTests::toIso8601String_whenValueIsNotNull_returnsStringFormatted() {
    Entity parentEntity;
    QDateTime testDateTime = QDateTime::currentDateTime();
    DateTimeDecorator decorator(&parentEntity,"TestingKey","TestingLabel",testDateTime);
    QCOMPARE(decorator.toIso8601String(),testDateTime.toString(Qt::ISODate));
}

void DateTimeDecoratorTests::toIso8601String_whenValueIsNull_returnsStringNotSet() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.toIso8601String(),"Not Set");
}

void DateTimeDecoratorTests::toPrettyDateString_whenValueIsNotNull_returnsStringFormatted() {
    Entity parentEntity;
    QDateTime testDateTime = QDateTime::currentDateTime();
    DateTimeDecorator decorator(&parentEntity,"TestingKey","TestingLabel",testDateTime);
    QCOMPARE(decorator.toPrettyDateString(),testDateTime.toString("d MMM yyyy"));
}

void DateTimeDecoratorTests::toPrettyDateString_whenValueIsNull_returnsStringNotSet() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.toPrettyDateString(),"Not Set");
}

void DateTimeDecoratorTests::toPrettyString_whenValueIsNotNull_returnsStringFormatted() {
    Entity parentEntity;
    QDateTime testDateTime = QDateTime::currentDateTime();
    DateTimeDecorator decorator(&parentEntity,"TestingKey","TestingLabel",testDateTime);
    QCOMPARE(decorator.toPrettyString(),testDateTime.toString("ddd d MMM yyyy @ HH:mm:ss"));
}

void DateTimeDecoratorTests::toPrettyString_whenValueIsNull_returnsStringNotSet() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.toPrettyString(),"Not Set");
}

void DateTimeDecoratorTests::toPrettyTimeString_whenValueIsNotNull_returnsStringFormatted() {
    Entity parentEntity;
    QDateTime testDateTime = QDateTime::currentDateTime();
    DateTimeDecorator decorator(&parentEntity,"TestingKey","TestingLabel",testDateTime);
    QCOMPARE(decorator.toPrettyTimeString(),testDateTime.toString("hh:mm ap"));
}

void DateTimeDecoratorTests::toPrettyTimeString_whenValueIsNull_returnsStringNotSet() {
    DateTimeDecorator decorator;
    QCOMPARE(decorator.toPrettyTimeString(),"Not Set");
}
}
}
