#ifndef EVENTVOTING_H
#define EVENTVOTING_H

#include "types/status.h"
#include "ievent.h"

class EventVoting : public IEvent
{
    bool VoteUp;
    QString result;
public:
    EventVoting(QString who, QString target, bool VoteUp);
    virtual QString getDisplayMsg();
};

#endif // EVENTVOTING_H
