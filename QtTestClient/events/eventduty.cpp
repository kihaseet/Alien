#include "eventduty.h"

EventDuty::EventDuty(QString who) : IEvent("", who, "")
{
}

EventDuty::EventDuty(const EventDuty &e) : IEvent(e.getWhat(), e.getWho(), e.getTarget())
{
}

QString EventDuty::getDisplayMsg() const
{
    return who + " встал на дежурство.";
}
