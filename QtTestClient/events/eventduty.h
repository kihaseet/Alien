#ifndef EVENTDUTY_H
#define EVENTDUTY_H

#include "ievent.h"

#include <QString>

class EventDuty : public IEvent
{
public:
    EventDuty(QString who);
    EventDuty(const EventDuty& e);
    virtual QString getDisplayMsg() const;
};

#endif // EVENTDUTY_H
