#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <QObject>

#include <cm-lib_global.h>
#include <data/stringdecorator.h>
#include <data/datetimedecorator.h>
#include <data/entity.h>

namespace cm {
namespace models {

class CMLIB_EXPORT Appointment : public data::Entity
{
    Q_OBJECT

    Q_PROPERTY(data::StringDecorator* ui_appointee MEMBER appointee CONSTANT)
    Q_PROPERTY(data::StringDecorator* ui_notes MEMBER notes CONSTANT)
    Q_PROPERTY(data::DateTimeDecorator* ui_startDate MEMBER startDate CONSTANT)
    Q_PROPERTY(data::DateTimeDecorator* ui_endDate MEMBER endDate CONSTANT)

    Q_PROPERTY(QString ui_fullAppointment READ fullAppointment CONSTANT)
public:
    explicit Appointment(QObject *parent = nullptr);
    Appointment(QObject *parent, const QJsonObject& json);

    data::StringDecorator* appointee{nullptr};
    data::StringDecorator* notes{nullptr};
    data::DateTimeDecorator* startDate{nullptr};
    data::DateTimeDecorator* endDate{nullptr};

    QString fullAppointment() const;
};

}
}

#endif // APPOINTMENT_H
