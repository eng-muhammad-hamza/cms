#ifndef CLIENTTESTS_H
#define CLIENTTESTS_H

#include <QTest>
#include <QJsonObject>

#include <models/client.h>

#include <testsuite.h>

namespace cm {
namespace models {
class ClientTests : public TestSuite {
    Q_OBJECT
public:
    ClientTests();

private slots:
    void constructor_givenParent_setsParentAndDefaultProperties();
    void constructor_givenParentAndJsonObject_setsParentAndProperties();
    void toJson_withDefaultProperties_constructsJson();
    void toJson_withSetProperties_constructsJson();
    void update_givenJsonObject_updatesProperties();
    void update_givenEmptyJsonObject_updatesPropertiesToDefault();
    void id_givenPrimaryKeyWithNoValue_returnsUuid();
    void id_givenPrimaryKeyWithValue_returnsPrimaryKey();

private:
    void verifyBillingAddress(const QJsonObject& jsonObject);
    void verifyDefaultBillingAddress(const QJsonObject& jsonObject);
    void verifyBillingAddress(Address* address);
    void verifyDefaultBillingAddress(Address* address);
    void verifySupplyAddress(const QJsonObject& jsonObject);
    void verifyDefaultSupplyAddress(const QJsonObject& jsonObject);
    void verifySupplyAddress(Address* address);
    void verifyDefaultSupplyAddress(Address* address);
    void verifyAppointments(const QJsonObject& jsonObject);
    void verifyDefaultAppointments(const QJsonObject& jsonObject);
    void verifyAppointments(const QList<Appointment*>& appointments);
    void verifyDefaultAppointments(const QList<Appointment*>& appointments);
    void verifyContacts(const QJsonObject& jsonObject);
    void verifyDefaultContacts(const QJsonObject& jsonObject);
    void verifyContacts(const QList<Contact*>& contacts);
    void verifyDefaultContacts(const QList<Contact*>& contacts);

    QByteArray jsonByteArray = R"(
    {
        "reference" : "CM0001",
        "name" : "Mr. Testing Boy",
        "billingAddress" : {
            "building" : "H No 67/1",
            "street" : "St No 1 Yhaya Colony Ghorey Shah Road",
            "city" : "Lahore",
            "postcode" : "54900"
        },
        "supplyAddress" : {
            "building" : "H No 69/1",
            "street" : "St No 2 Yhaya Colony Ghorey Shah Road",
            "city" : "Lahore",
            "postcode" : "54903"
        },
        "appointments" : [
        {
            "startDate" : "2024-07-28T17:35:00",
            "endDate" : "2024-07-28T21:30:00",
            "appointee" : "Superman",
            "notes" : "Test Appointment 1"
        },
        {
            "startDate" : "2024-07-28T21:35:00",
            "endDate" : "2024-07-28T23:30:00",
            "appointee" : "Wolverine",
            "notes" : "Test Appointment 2"
        }
        ],
        "contacts" : [
        {
            "contactType" : 2,
            "address" : "noone@gmail.com"
        },
        {
            "contactType" : 1,
            "address" : "+923304343065"
        }
        ]
    })";
};
}
}

#endif // CLIENTTESTS_H
