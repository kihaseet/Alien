#ifndef VOTING_H
#define VOTING_H
#include <QtGui>
#include "player.h"

class voting:public QObject
{
    Q_OBJECT
public:
    QString target;
    bool is_over;//true когда голосование уже закончилось
    // QMap <player*,QMap<player*,int>> votelist;//кто голосует
    QMap <QString,QPair<QString,int> > votelist;
    QList<QString> electlist;//против кого голосуют
    QList<QString> winners;


    voting(QList<QString> mapwho, QList<QString> mapwhom, QString target);
    voting();
    bool is_complite();
    void start();
    void calc_votes();
public slots:
    void on_voting(QString who, QString whom);
    void off_voting(QString who);
    void use_notebook(QString who,QString whom,QString useit);
    void ult_notebook(QString who,QString whom,QString useit);
signals:
    void voting_over(QList<QString> v);
    void voting_canseled();
    void cap_decision(QList<QString> w);
};

struct QPairSecondComparer
{
    template<typename T1, typename T2>
    bool operator()(const QPair<T1,T2> & a, const QPair<T1,T2> & b) const
    {
        return a.second > b.second;
    }
};

#endif // VOTING_H
