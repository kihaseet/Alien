#ifndef STATALIEN_H
#define STATALIEN_H

#include "istatupdate.h"

class StatAlien : public IStatUpdate
{
public:
    StatAlien();
    StatAlien(const StatAlien& s) {};

    virtual void apply(CurrentPlayer& player) const;
};

#endif // STATALIEN_H
