#ifndef EVENT_H
#define EVENT_H
#include "player.h"

class ingame_event:public QObject
{
Q_OBJECT
public:
    player who,whom;
    QString what;
    item useit;
    ingame_event(player wh,player whm,QString wht,item it);
signals:
    void event_useitem();
    void event_ultitem();
    void event_attack();
    void event_infect();
    void event_wait();
    void event_up();
    void event_down();
    void event_vote();
    void event_norecognize();
public slots:
    void do_event();
};

#endif // EVENT_H
