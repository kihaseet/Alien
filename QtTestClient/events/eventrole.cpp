#include "eventrole.h"

EventRole::EventRole(QString who, QString role, bool getRole) : IEvent("", who, "")
{
    this->role = role;
    this->getRole = getRole;
}

QString EventRole::getDisplayMsg()
{
    return who + " " + (getRole ? "получил" : "потерял") + " " + role;
}
