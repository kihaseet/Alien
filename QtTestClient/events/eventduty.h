#ifndef EVENTDUTY_H
#define EVENTDUTY_H

#include "ievent.h"

#include <QString>

class EventDuty : public IEvent
{
public:
    EventDuty(QString who);
    virtual QString getDisplayMsg();
};

#endif // EVENTDUTY_H
