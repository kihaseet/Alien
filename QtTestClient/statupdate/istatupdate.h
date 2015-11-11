#ifndef ISTATUPDATE_H
#define ISTATUPDATE_H

#include <QObject>
#include "types/currentplayer.h"

class IStatUpdate : public QObject
{
    Q_OBJECT
public:
    IStatUpdate();
    IStatUpdate(const IStatUpdate& s) {};

    virtual void apply(CurrentPlayer&) const;
};

#endif // ISTATUPDATE_H
