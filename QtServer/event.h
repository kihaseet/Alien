#ifndef EVENT_H
#define EVENT_H
#include "player.h"

class ingame_event:public QObject
{
Q_OBJECT
public:
    QString who,whom;
    QString what;
    QString useit;
    QQueue <QString> rota;
    ingame_event(QString wh, QString whm, QString wht, QString it, QQueue <QString>rot);
    ingame_event(QString wh, QString whm, QString wht, QString it);
signals:
    void event_useitem(QString wh,QString whm,QString usei);
    void event_useitemcap(QString wh,QString whm,QString usei);
    void event_ultitem(QString wh,QString whm,QString usei);
    void event_attack(QString wh,QString whm);
    void event_infect(QString wh,QString whm);
    void event_wait(QString wh);
    void event_up(QString wh);
    void event_down(QString wh);
    void event_vote(QString wh,QString whm);
    void event_unvote(QString wh);
    void event_useitemrot(QList<QString>rota);
    void event_norecognize();
    void event_alien(QString wh);
    void event_getitem(QString who,QString useit,QString whom);
public slots:
    void do_event();
};

#endif // EVENT_H
