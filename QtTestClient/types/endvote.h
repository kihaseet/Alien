#ifndef ENDVOTE_H
#define ENDVOTE_H

#include "types/player.h"
#include <QVector>
#include <QString>

class EndVote
{
    QString votingFor;
    QString result;
    QString target;
public:
    EndVote(QString votingFor, QString result, QString target);
    QString getDisplayMsg();
};

#endif // ENDVOTE_H
