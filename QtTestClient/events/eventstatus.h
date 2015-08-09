#ifndef EVENTSTATUS_H
#define EVENTSTATUS_H

#include "types/status.h"
#include "ievent.h"

class EventStatus : public IEvent
{
    Status status;
public:
    EventStatus(QString who, Status status);
    virtual QString getDisplayMsg();
};

#endif // EVENTSTATUS_H
