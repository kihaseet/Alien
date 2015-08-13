#include "events/ievent.h"

IEvent::IEvent(QString what, QString who, QString target)
{
    this->what = what;
    this->who = who;
    this->target = target;
}

IEvent::IEvent(IEvent &e)
{
    this->who = e.getWho();
    this->what = e.getWhat();
    this->target = e.getTarget();
}

