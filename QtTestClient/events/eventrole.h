#ifndef EVENTROLE_H
#define EVENTROLE_H

#include "ievent.h"

#include <QString>
#include <QStringList>

class EventRole : public IEvent
{
    QString role;
    bool getRole;
public:
    EventRole(QString who, QString role, bool getRole);
    virtual QString getDisplayMsg();
};

#endif // EVENTROLE_H
