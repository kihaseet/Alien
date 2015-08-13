#ifndef VOTE_H
#define VOTE_H

#include "types/player.h"
#include <QMap>
#include <QVector>
#include <QString>

class Vote
{
    QString votingFor;
    QString currentTarget;
    QStringList targets;
public:
    Vote(QString votingFor, QStringList targets);
    QStringList getTargets();
    QString getVotingFor();
    QString getCurrentTarget();
    void setCurrentTarget(QString name);
};

#endif // VOTE_H
