#include "eventvoting.h"

EventVoting::EventVoting(QString who, QString target, bool VoteUp) : IEvent("", who, target)
{
    this->VoteUp = VoteUp;
}

EventVoting::EventVoting(const EventVoting &e) : IEvent(e.getWhat(), e.getWho(), e.getTarget())
{
    this->VoteUp = e.VoteUp;
}

bool EventVoting::getVoteUp() const
{
    return this->VoteUp;
}

QString EventVoting::getDisplayMsg() const
{
    if (this->VoteUp)
    {
        return who + " проголосовал за " + target;
    }
    else
    {
        return who + " снял голос с " + target;
    }
}
