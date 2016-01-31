#include "vote.h"

Vote::Vote(QString votingFor, QStringList targets)
{
    this->votingFor = votingFor;
    this->targets = targets;
}

QStringList Vote::getTargets()
{
    return this->targets;
}

QString Vote::getVotingFor()
{
    return this->votingFor;
}

QString Vote::getCurrentTarget()
{
    return this->currentTarget;
}

void Vote::setCurrentTarget(QString name)
{
    this->currentTarget = name;
}
