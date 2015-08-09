#ifndef ISTATUPDATE_H
#define ISTATUPDATE_H

#include "types/currentplayer.h"

class IStatUpdate
{
public:
    IStatUpdate();

    virtual void apply(CurrentPlayer&);
};

#endif // ISTATUPDATE_H
