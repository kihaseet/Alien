#ifndef STATCHANGEHP_H
#define STATCHANGEHP_H

#include "types/currentplayer.h"
#include "statupdate/istatupdate.h"

class StatChangeHP : public IStatUpdate
{
    int HP;
public:
    StatChangeHP(int HP);
    StatChangeHP(const StatChangeHP& s);

    virtual void apply(CurrentPlayer& player) const;
};

#endif // STATCHANGEHP_H
