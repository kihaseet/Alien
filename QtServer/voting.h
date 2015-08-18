#ifndef VOTING_H
#define VOTING_H
#include <QtGui>

#include "player.h"
#include "types.h"

class voting:public QObject
{
    Q_OBJECT
private:
    QString noteName;   //голос ноутбука
public:
    ROLE targets;
    bool is_over;//true когда голосование уже закончилось
    QList <VoteObject*> votelist;
    QList<QString> electlist;//против кого голосуют
    QList<QString> winners;



    voting(QList<QString> mapwhom, ROLE tar);
    voting();
    bool is_complite();
    bool is_vote(QString who);
    void start();
    void calc_votes();
    void send_voting_over(QList<QString> v);
    void on_voting(QString who, QString whom);
    void off_voting(QString who);

    void setNoteName(QString n);
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
