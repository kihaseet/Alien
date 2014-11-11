#ifndef VOTING_H
#define VOTING_H
#include <QtGui>
#include "player.h"

class voting:public QObject
{
Q_OBJECT
public:
    QString target;
    QMap <player,QMap<player,int>> votelist;
    voting(QList <player> map,QString target);
    bool on_voting(player who,player whom);
    bool is_complite();
    void start();
public slots:
    void on_voting(player who,player whom);
};

#endif // VOTING_H
