#ifndef VOTE_H
#define VOTE_H

#include "types/player.h"
#include <QMap>
#include <QVector>
#include <QString>

class Vote
{
    QString votingFor;
    Player* currentTarget;
    QStringList targets;
public:
    Vote(QString votingFor, QStringList targets);
    QStringList getTargets();
    QString getVotingFor();
    Player* getCurrentTarget();
};

#endif // VOTE_H
