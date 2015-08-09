#include "eventfactory.h"

EventFactory::EventFactory()
{

}

IEvent EventFactory::Item(QString what, QString who, QString target, ITarget item)
{
    return EventItem(what, who, target, item);
}

IEvent EventFactory::StatusEvent(QString who, Status status)
{
    return EventStatus(who, status);
}

IEvent EventFactory::Duty(QString who)
{
    return EventDuty(who);
}

IEvent EventFactory::Role(QString what, QString who, bool getRole)
{
    return EventRole(who, what, getRole);
}

IEvent EventFactory::Voting(QString who, QString target, bool voteUp)
{
    return EventVoting(who, target, voteUp);
}

