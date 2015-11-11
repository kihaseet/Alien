#include "eventstatus.h"

EventStatus::EventStatus(QString who, Status status) : IEvent("", who, "")
{
    this->status = status;
}

EventStatus::EventStatus(const EventStatus &e) : IEvent(e.getWhat(), e.getWho(), e.getTarget())
{
    this->status = e.status;
}

QString EventStatus::getDisplayMsg() const
{
    return who + " " + StatusProcess::statusToString(this->status);
}
