#include "appointment.h"

using namespace cm::data;

namespace cm {
namespace models {

Appointment::Appointment(QObject *parent)
    : Entity{parent}
{
    appointee = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this,"appointee","Appointee")));
    notes = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this,"notes","Additional Notes")));
    startDate = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this,"startDate","Start Date")));
    endDate = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this,"endDate","End Date")));
}

Appointment::Appointment(QObject *parent, const QJsonObject &json)
    : Appointment(parent)
{
    update(json);
}

QString Appointment::fullAppointment() const {
    return appointee->value() + " has appointment in between " + startDate->toIso8601String() + " - " +
           endDate->toIso8601String() + "\nAdditional Notes - " + notes->value();
}

}
}
