#include "endvote.h"

EndVote::EndVote(QString votingFor, QString result, QString target)
{
    this->votingFor = votingFor;
    this->result = result;
    this->target = target;
}

QString EndVote::getDisplayMsg()
{
    QString ret;

    if (this->result != "")
    {
        ret = target + " - " + result;
    }
    else
    {
        ret = "Прервано.";
    }

    return "Голосование на " + votingFor + " завершено. " + ret;
}
