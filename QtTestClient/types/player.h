#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QStringList>

#include "itarget.h"
#include "status.h"
#include "playerimage.h"

class Player : public ITarget
{
protected:
    Status status;
    QStringList roles;
    PlayerImage image;
    bool online;
    bool onDuty;
public:
    explicit Player();
    explicit Player(QString name, QStringList roles, PlayerImage image, bool onDuty = false, bool online = true, Status status = Status::UP);

    Status getStatus();
    void setStatus(Status status);
    void setOnline(bool online);
    void setOnDuty(bool onDuty);
    QStringList getRoles();
    void setRoles(QStringList roles);
    bool isOnline();
    bool isOnDuty();
};

#endif // PLAYER_H
