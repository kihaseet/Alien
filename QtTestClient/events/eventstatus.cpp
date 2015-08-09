#include "eventstatus.h"

EventStatus::EventStatus(QString who, Status status) : IEvent("", who, "")
{
    this->status = status;
}

QString EventStatus::getDisplayMsg()
{
    return who + " " + StatusProcess::statusToString(this->status);
}
