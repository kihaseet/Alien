#ifndef STATALIEN_H
#define STATALIEN_H

#include "istatupdate.h"

class StatAlien : public IStatUpdate
{
public:
    StatAlien();

    virtual void apply(CurrentPlayer& player);
};

#endif // STATALIEN_H
