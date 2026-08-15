#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <functional>

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <cm-lib_global.h>

namespace cm {
namespace framework {

// This class Provides the basic structure for a command in our commandBar. Here We have considered that
// A command will be represented as a button in our QML/UI which will eventually have an ICON - REPRESENTING
// THE PURPOSE OF THE COMMAND VISUALLY, a DESCRIPTION - DEFINING WHAT THE COMMAND IS FOR, and a check
// WHETHER THE COMMAND IS EXECUTABLE OR NOT

// NOTE: HERE WE ARE CREATING A SPECIALIZED TYPE TO BE USED IN QML BY REGISTERING IT AS QML TYPE. IT IS BECAUSE
// INSTEAD OF MANNUALLY MAKING COMMAND BUTTON PROPERITES IN QML LIKE WE DID IN CASE OF NAVIGATION BUTTON
// WE CAN USE THIS COMMAND REGISTERED TYPE TO EASILY CREATE THE COMMAND BUTTONS

class CMLIB_EXPORT Command : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_iconCharacter READ iconCharacter CONSTANT)
    Q_PROPERTY(QString ui_description READ description CONSTANT)
    Q_PROPERTY(bool ui_canExecute READ canExecute NOTIFY canExecuteChanged)
public:
    explicit Command(QObject *parent = nullptr,
                     const QString& iconCharacter = "",
                     const QString& description = "",
                     std::function<bool()> canExecute = [](){return true;});
    ~Command();
    const QString& iconCharacter() const;
    const QString& description() const;
    bool canExecute() const;
signals:
    void canExecuteChanged();
    void executed();
private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};
}
}

#endif // COMMAND_H
