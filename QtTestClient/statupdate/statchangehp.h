#ifndef STATCHANGEHP_H
#define STATCHANGEHP_H

#include "types/currentplayer.h"
#include "statupdate/istatupdate.h"

class StatChangeHP : public IStatUpdate
{
    int HP;
public:
    StatChangeHP(int HP);

    virtual void apply(CurrentPlayer& player);
};

#endif // STATCHANGEHP_H
