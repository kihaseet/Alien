#ifndef EVENTITEM_H
#define EVENTITEM_H

#include "types/itarget.h"
#include "ievent.h"

#include <QString>


class EventItem : public IEvent
{
    ITarget item;
public:
    EventItem(QString what, QString who, QString target, ITarget item);
    virtual QString getDisplayMsg();
};

#endif // EVENTITEM_H
