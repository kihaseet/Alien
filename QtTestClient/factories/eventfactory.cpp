#include "eventfactory.h"

EventFactory::EventFactory()
{

}

EventItem EventFactory::Item(QString what, QString who, QString target, ITarget item)
{
    return EventItem(what, who, target, item);
}

EventStatus EventFactory::StatusEvent(QString who, Status status)
{
    return EventStatus(who, status);
}

EventDuty EventFactory::Duty(QString who)
{
    return EventDuty(who);
}

EventRole EventFactory::Role(QString what, QString who, bool getRole)
{
    return EventRole(who, what, getRole);
}

EventVoting EventFactory::Voting(QString who, QString target, bool voteUp)
{
    return EventVoting(who, target, voteUp);
}

