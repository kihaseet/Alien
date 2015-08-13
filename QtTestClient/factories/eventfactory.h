#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H

#include "events/ievent.h"
#include "events/eventduty.h"
#include "events/eventitem.h"
#include "events/eventrole.h"
#include "events/eventstatus.h"
#include "events/eventvoting.h"
#include "types/itarget.h"
#include "types/status.h"

#include <QString>
#include <QStringList>

class EventFactory
{
public:
    EventFactory();
    static EventItem Item(QString what, QString who, QString target, ITarget item);
    static EventStatus StatusEvent(QString who, Status status);
    static EventDuty Duty(QString who);
    static EventRole Role(QString what, QString who, bool getRole);
    static EventVoting Voting(QString who, QString target, bool voteUp);
};

#endif // EVENTFACTORY_H
