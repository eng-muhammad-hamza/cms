#include "clienttests.h"

#include <QString>
#include <QtTest>

#include <QJsonArray>
#include <QJsonDocument>

#include <models/client.h>

using namespace cm::models;

namespace cm {
namespace models {

static ClientTests instance;

ClientTests::ClientTests() : TestSuite("ClientTests") {}

void ClientTests::constructor_givenParent_setsParentAndDefaultProperties() {
    Client client(this);
    QCOMPARE(client.parent(),this);
    QCOMPARE(client.reference->value(),QString(""));
    QCOMPARE(client.name->value(),QString(""));

    verifyDefaultBillingAddress(client.billingAddress);
    verifyDefaultSupplyAddress(client.supplyAddress);
    verifyDefaultAppointments(client.appointments->derivedEntities());
    verifyDefaultContacts(client.contacts->derivedEntities());
}

void ClientTests::constructor_givenParentAndJsonObject_setsParentAndProperties() {
    Client client(this,QJsonDocument::fromJson(jsonByteArray).object());
    QCOMPARE(client.parent(),this);
    QCOMPARE(client.reference->value(),QString("CM0001"));
    QCOMPARE(client.name->value(),QString("Mr. Testing Boy"));

    verifyBillingAddress(client.billingAddress);
    verifySupplyAddress(client.supplyAddress);
    verifyAppointments(client.appointments->derivedEntities());
    verifyContacts(client.contacts->derivedEntities());
}

void ClientTests::toJson_withDefaultProperties_constructsJson() {
    Client client(this);
    QJsonDocument jsonDoc(client.toJson());
    QVERIFY(jsonDoc.isObject());
    QJsonObject jsonObject = jsonDoc.object();
    QVERIFY(jsonObject.contains("reference"));
    QCOMPARE(jsonObject.value("reference").toString(),QString(""));
    QVERIFY(jsonObject.contains("name"));
    QCOMPARE(jsonObject.value("name").toString(),QString(""));
    verifyDefaultBillingAddress(jsonObject);
    verifyDefaultSupplyAddress(jsonObject);
    verifyDefaultAppointments(jsonObject);
    verifyDefaultContacts(jsonObject);
}

void ClientTests::toJson_withSetProperties_constructsJson() {
    Client client(this,QJsonDocument::fromJson(jsonByteArray).object());
    QCOMPARE(client.parent(),this);
    QCOMPARE(client.reference->value(),QString("CM0001"));
    QCOMPARE(client.name->value(),QString("Mr. Testing Boy"));

    verifyBillingAddress(client.billingAddress);
    verifySupplyAddress(client.supplyAddress);
    verifyAppointments(client.appointments->derivedEntities());
    verifyContacts(client.contacts->derivedEntities());

    QJsonDocument jsonDoc(client.toJson());
    QVERIFY(jsonDoc.isObject());
    QJsonObject jsonObject = jsonDoc.object();
    QVERIFY(jsonObject.contains("reference"));
    QCOMPARE(jsonObject.value("reference").toString(),QString("CM0001"));
    QVERIFY(jsonObject.contains("name"));
    QCOMPARE(jsonObject.value("name").toString(),QString("Mr. Testing Boy"));
    verifyBillingAddress(jsonObject);
    verifySupplyAddress(jsonObject);
    verifyAppointments(jsonObject);
    verifyContacts(jsonObject);
}

void ClientTests::update_givenEmptyJsonObject_updatesPropertiesToDefault() {
    Client client(this,QJsonDocument::fromJson(jsonByteArray).object());
    QCOMPARE(client.parent(),this);
    QCOMPARE(client.reference->value(),QString("CM0001"));
    QCOMPARE(client.name->value(),QString("Mr. Testing Boy"));

    verifyBillingAddress(client.billingAddress);
    verifySupplyAddress(client.supplyAddress);
    verifyAppointments(client.appointments->derivedEntities());
    verifyContacts(client.contacts->derivedEntities());

    client.update(QJsonObject());
    QCOMPARE(client.reference->value(),QString(""));
    QCOMPARE(client.name->value(),QString(""));

    verifyDefaultBillingAddress(client.billingAddress);
    verifyDefaultSupplyAddress(client.supplyAddress);
    verifyDefaultAppointments(client.appointments->derivedEntities());
    verifyDefaultContacts(client.contacts->derivedEntities());
}

void ClientTests::update_givenJsonObject_updatesProperties() {
    Client client(this);
    client.update(QJsonDocument::fromJson(jsonByteArray).object());
    QCOMPARE(client.reference->value(),QString("CM0001"));
    QCOMPARE(client.name->value(),QString("Mr. Testing Boy"));

    verifyBillingAddress(client.billingAddress);
    verifySupplyAddress(client.supplyAddress);
    verifyAppointments(client.appointments->derivedEntities());
    verifyContacts(client.contacts->derivedEntities());
}

void ClientTests::id_givenPrimaryKeyWithNoValue_returnsUuid() {
    Client client(this);

    QCOMPARE(client.id().left(1),QString("{"));
    QCOMPARE(client.id().mid(9,1),QString("-"));
    QCOMPARE(client.id().mid(14,1),QString("-"));
    QCOMPARE(client.id().mid(19,1),QString("-"));
    QCOMPARE(client.id().mid(24,1),QString("-"));
    QCOMPARE(client.id().right(1),QString("}"));

    QVERIFY(QRegularExpression("\\{.{8}-(.{4})-(.{4})-(.{4})-(.{12})\\}").match(client.id()).hasMatch());
}

void ClientTests::id_givenPrimaryKeyWithValue_returnsPrimaryKey() {
    Client client(this,QJsonDocument::fromJson(jsonByteArray).object());
    QCOMPARE(client.reference->value(),QString("CM0001"));
    QCOMPARE(client.id(),client.reference->value());
}

void ClientTests::verifyDefaultBillingAddress(Address *address) {
    QVERIFY(address != nullptr);
    QCOMPARE(address->building->value(),QString(""));
    QCOMPARE(address->street->value(),QString(""));
    QCOMPARE(address->city->value(),QString(""));
    QCOMPARE(address->postcode->value(),QString(""));
}

void ClientTests::verifyDefaultSupplyAddress(Address *address) {
    QVERIFY(address != nullptr);
    QCOMPARE(address->building->value(),QString(""));
    QCOMPARE(address->street->value(),QString(""));
    QCOMPARE(address->city->value(),QString(""));
    QCOMPARE(address->postcode->value(),QString(""));
}

void ClientTests::verifyDefaultContacts(const QList<Contact *> &contacts) {
    QCOMPARE(contacts.size(),0);
}

void ClientTests::verifyDefaultAppointments(const QList<Appointment *> &appointments) {
    QCOMPARE(appointments.size(),0);
}

void ClientTests::verifyDefaultBillingAddress(const QJsonObject &jsonObject) {
    QVERIFY(jsonObject.contains("billingAddress"));
    QJsonObject billing_address = jsonObject.value("billingAddress").toObject();
    QVERIFY(billing_address.contains("building"));
    QCOMPARE(billing_address.value("building").toString(), QString(""));
    QVERIFY(billing_address.contains("street"));
    QCOMPARE(billing_address.value("street").toString(), QString(""));
    QVERIFY(billing_address.contains("city"));
    QCOMPARE(billing_address.value("city").toString(), QString(""));
    QVERIFY(billing_address.contains("postcode"));
    QCOMPARE(billing_address.value("postcode").toString(), QString(""));
}

void ClientTests::verifyDefaultSupplyAddress(const QJsonObject &jsonObject) {
    QVERIFY(jsonObject.contains("supplyAddress"));
    QJsonObject billing_address = jsonObject.value("supplyAddress").toObject();
    QVERIFY(billing_address.contains("building"));
    QCOMPARE(billing_address.value("building").toString(), QString(""));
    QVERIFY(billing_address.contains("street"));
    QCOMPARE(billing_address.value("street").toString(), QString(""));
    QVERIFY(billing_address.contains("city"));
    QCOMPARE(billing_address.value("city").toString(), QString(""));
    QVERIFY(billing_address.contains("postcode"));
    QCOMPARE(billing_address.value("postcode").toString(), QString(""));
}

void ClientTests::verifyDefaultAppointments(const QJsonObject &jsonObject) {
    QVERIFY(jsonObject.contains("appointments"));
    QJsonArray json_appointments = jsonObject.value("appointments").toArray();
    QCOMPARE(json_appointments.size(),0);
}

void ClientTests::verifyDefaultContacts(const QJsonObject &jsonObject) {
    QVERIFY(jsonObject.contains("contacts"));
    QJsonArray json_contacts = jsonObject.value("contacts").toArray();
    QCOMPARE(json_contacts.size(),0);
}

void ClientTests::verifyBillingAddress(Address *address) {
    QVERIFY(address != nullptr);
    QCOMPARE(address->building->value(),QString("H No 67/1"));
    QCOMPARE(address->street->value(),QString("St No 1 Yhaya Colony Ghorey Shah Road"));
    QCOMPARE(address->city->value(),QString("Lahore"));
    QCOMPARE(address->postcode->value(),QString("54900"));
}

void ClientTests::verifySupplyAddress(Address *address) {
    QVERIFY(address != nullptr);
    QCOMPARE(address->building->value(),QString("H No 69/1"));
    QCOMPARE(address->street->value(),QString("St No 2 Yhaya Colony Ghorey Shah Road"));
    QCOMPARE(address->city->value(),QString("Lahore"));
    QCOMPARE(address->postcode->value(),QString("54903"));
}

void ClientTests::verifyAppointments(const QList<Appointment *> &appointments) {
    QCOMPARE(appointments.size(),2);
    QCOMPARE(appointments.at(0)->startDate->value(),QDateTime(QDate(2024,7,28),QTime(17,35)));
    QCOMPARE(appointments.at(0)->endDate->value(),QDateTime(QDate(2024,7,28),QTime(21,30)));
    QCOMPARE(appointments.at(0)->appointee->value(),QString("Superman"));
    QCOMPARE(appointments.at(0)->notes->value(),QString("Test Appointment 1"));

    QCOMPARE(appointments.at(1)->startDate->value(),QDateTime(QDate(2024,7,28),QTime(21,35)));
    QCOMPARE(appointments.at(1)->endDate->value(),QDateTime(QDate(2024,7,28),QTime(23,30)));
    QCOMPARE(appointments.at(1)->appointee->value(),QString("Wolverine"));
    QCOMPARE(appointments.at(1)->notes->value(),QString("Test Appointment 2"));
}

void ClientTests::verifyContacts(const QList<Contact *> &contacts) {
    QCOMPARE(contacts.size(),2);
    QCOMPARE(contacts.at(0)->contactType->value(),static_cast<int>(Contact::eContactType::EMAIL));
    QCOMPARE(contacts.at(0)->address->value(),QString("noone@gmail.com"));

    QCOMPARE(contacts.at(1)->contactType->value(),static_cast<int>(Contact::eContactType::TELEPHONE));
    QCOMPARE(contacts.at(1)->address->value(),QString("+923304343065"));
}

void ClientTests::verifyBillingAddress(const QJsonObject &jsonObject) {
    QVERIFY(jsonObject.contains("billingAddress"));
    QJsonObject billing_address = jsonObject.value("billingAddress").toObject();
    QVERIFY(billing_address.contains("building"));
    QCOMPARE(billing_address.value("building").toString(), QString("H No 67/1"));
    QVERIFY(billing_address.contains("street"));
    QCOMPARE(billing_address.value("street").toString(), QString("St No 1 Yhaya Colony Ghorey Shah Road"));
    QVERIFY(billing_address.contains("city"));
    QCOMPARE(billing_address.value("city").toString(), QString("Lahore"));
    QVERIFY(billing_address.contains("postcode"));
    QCOMPARE(billing_address.value("postcode").toString(), QString("54900"));
}

void ClientTests::verifySupplyAddress(const QJsonObject &jsonObject) {
    QVERIFY(jsonObject.contains("supplyAddress"));
    QJsonObject billing_address = jsonObject.value("supplyAddress").toObject();
    QVERIFY(billing_address.contains("building"));
    QCOMPARE(billing_address.value("building").toString(), QString("H No 69/1"));
    QVERIFY(billing_address.contains("street"));
    QCOMPARE(billing_address.value("street").toString(), QString("St No 2 Yhaya Colony Ghorey Shah Road"));
    QVERIFY(billing_address.contains("city"));
    QCOMPARE(billing_address.value("city").toString(), QString("Lahore"));
    QVERIFY(billing_address.contains("postcode"));
    QCOMPARE(billing_address.value("postcode").toString(), QString("54903"));
}

void ClientTests::verifyAppointments(const QJsonObject &jsonObject) {
    QVERIFY(jsonObject.contains("appointments"));
    QJsonArray json_appointments = jsonObject.value("appointments").toArray();
    QCOMPARE(json_appointments.size(),2);
    QVERIFY(json_appointments.at(0).isObject());
    QVERIFY(json_appointments.at(1).isObject());

    QJsonObject appointment1 = json_appointments.at(0).toObject();
    QVERIFY(appointment1.contains("startDate"));
    QCOMPARE(appointment1.value("startDate").toString(), QString("2024-07-28T17:35:00"));
    QVERIFY(appointment1.contains("endDate"));
    QCOMPARE(appointment1.value("endDate").toString(), QString("2024-07-28T21:30:00"));
    QVERIFY(appointment1.contains("appointee"));
    QCOMPARE(appointment1.value("appointee").toString(), QString("Superman"));
    QVERIFY(appointment1.contains("notes"));
    QCOMPARE(appointment1.value("notes").toString(), QString("Test Appointment 1"));

    QJsonObject appointment2 = json_appointments.at(1).toObject();
    QVERIFY(appointment2.contains("startDate"));
    QCOMPARE(appointment2.value("startDate").toString(), QString("2024-07-28T21:35:00"));
    QVERIFY(appointment2.contains("endDate"));
    QCOMPARE(appointment2.value("endDate").toString(), QString("2024-07-28T23:30:00"));
    QVERIFY(appointment2.contains("appointee"));
    QCOMPARE(appointment2.value("appointee").toString(), QString("Wolverine"));
    QVERIFY(appointment2.contains("notes"));
    QCOMPARE(appointment2.value("notes").toString(), QString("Test Appointment 2"));
}

void ClientTests::verifyContacts(const QJsonObject &jsonObject) {
    QVERIFY(jsonObject.contains("contacts"));
    QJsonArray json_contacts = jsonObject.value("contacts").toArray();
    QCOMPARE(json_contacts.size(),2);
    QVERIFY(json_contacts.at(0).isObject());
    QVERIFY(json_contacts.at(1).isObject());

    QJsonObject contact1 = json_contacts.at(0).toObject();
    QVERIFY(contact1.contains("contactType"));
    QCOMPARE(contact1.value("contactType").toInt(), static_cast<int>(Contact::eContactType::EMAIL));
    QVERIFY(contact1.contains("address"));
    QCOMPARE(contact1.value("address").toString(), QString("noone@gmail.com"));

    QJsonObject contact2 = json_contacts.at(1).toObject();
    QVERIFY(contact2.contains("contactType"));
    QCOMPARE(contact2.value("contactType").toInt(), static_cast<int>(Contact::eContactType::TELEPHONE));
    QVERIFY(contact2.contains("address"));
    QCOMPARE(contact2.value("address").toString(), QString("+923304343065"));
}
}
}
