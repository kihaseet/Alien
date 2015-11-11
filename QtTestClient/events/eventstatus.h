#ifndef EVENTSTATUS_H
#define EVENTSTATUS_H

#include "types/status.h"
#include "ievent.h"

class EventStatus : public IEvent
{
    Status status;
public:
    EventStatus(QString who, Status status);
    EventStatus(const EventStatus& e);
    virtual QString getDisplayMsg() const;
};

#endif // EVENTSTATUS_H
