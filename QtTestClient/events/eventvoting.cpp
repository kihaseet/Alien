#include "eventvoting.h"

EventVoting::EventVoting(QString who, QString target, bool VoteUp) : IEvent("", who, target)
{
    this->VoteUp = VoteUp;
}

QString EventVoting::getDisplayMsg()
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
