#include "eventduty.h"

EventDuty::EventDuty(QString who) : IEvent("", who, "")
{

}

QString EventDuty::getDisplayMsg()
{
    return who + " ыстал на дежурство.";
}
