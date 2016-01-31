#include "eventrole.h"

EventRole::EventRole(QString who, QString role, bool getRole) : IEvent("", who, "")
{
    this->role = role;
    this->getRole = getRole;
}

EventRole::EventRole(const EventRole &e) : IEvent(e.getWhat(), e.getWho(), e.getTarget())
{
    this->role = e.role;
    this->getRole = e.getRole;
}

QString EventRole::getRoleUpdate()
{
    return this->role;
}

bool EventRole::gotRole()
{
    return this->getRole;
}

QString EventRole::getDisplayMsg() const
{
    return who + " " + (getRole ? "получил" : "потерял") + " " + role;
}
