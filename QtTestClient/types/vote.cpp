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

Player *Vote::getCurrentTarget()
{
    return this->currentTarget;
}
