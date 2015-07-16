#ifndef EVENT_H
#define EVENT_H
#include <QtCore>
#include "player.h"

class player;

enum TURN_TYPE {
    TT_NOTHING = -1,
    TT_USE_ITEM = 0,
    TT_ULT_ITEM,
    TT_ATTACK,
    TT_INFECT,
    TT_SKIP,
    TT_ALIEN,
    TT_UP,
    TT_DOWN,
    TT_GETITEM,
    TT_DELITEM,
    TT_VOTE,
    TT_UNVOTE
};

enum ITEM{
    IT_BADGE = 0,
    IT_INJECTOR,
    IT_SCANNER,
    IT_MOP,
    IT_BATTERY,
    IT_BLASTER,
    IT_NOTEBOOK,
    IT_ROTATION,
    IT_FETUS
};

class ingame_event:public QObject
{
Q_OBJECT
public:
    QString who,whom;
    QString what;
    QString useit;
    QQueue <QString> rota;
    player* wh;
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



struct TurnObject:public QObject {
Q_OBJECT
public:
    TURN_TYPE type;
    QQueue<QString> targets;
    QString item;
    
    player* wh;
  
    TurnObject(TURN_TYPE type, 
               QStringList targets = QStringList(), 
               QString item = QString())
    {
        this->item = item;
        this->targets = targets;
        this->type = type;
    }

    TurnObject(TURN_TYPE type, QString item)
    {
        this->item = item;
        this->type = type;
    }
    
    TurnObject()
    {
        item = "";
        targets = QStringList();
        type = TT_SKIP;
    }

    friend bool operator == (const TurnObject& left, const TurnObject& right)
    {
        bool t = true;
        if(!right.targets.isEmpty()){
            foreach (QString name, right.targets) {
                if(!left.targets.contains(name)){
                    t=false;
                    break;
                }
            }
        }
       return
          left.item == right.item &&
          left.type == right.type &&
          t;
    }
    friend bool operator < (const TurnObject& left, const TurnObject& right)
    {
        if((left.type == TT_USE_ITEM && right.type == TT_USE_ITEM)||(left.type == TT_ULT_ITEM && right.type == TT_ULT_ITEM)){
             return left.item < right.item;
        }else return left.type < right.type;
    }
    
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
