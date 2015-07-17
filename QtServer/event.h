#ifndef EVENT_H
#define EVENT_H
#include <QtCore>
#include "player.h"

class player;

enum TURN_TYPE {
    TT_NOTHING = -1,
    TT_USE_BADGE = 0,
    TT_USE_ITEM,
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
    TT_UNVOTE,
    TT_REGNAME,
    TT_REGROLE
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


struct TurnObject{
public:
    TURN_TYPE type;
    QQueue<QString> targets;
    QString item;
    
    player* wh;

    static QMap <QString, ITEM> ItemDescr;
    static QMap<QString, ITEM> initColumnNames();
  
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
        if(! (right.targets.isEmpty() || left.targets.isEmpty()))
        {
            foreach (QString name, right.targets)
            {
                if(!left.targets.contains(name))
                {
                    t = false;
                    break;
                }
            }
            if((right.item == "Rotation") && (right.targets.count() != left.targets.count()))
            {
                t = false;
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
             return ItemDescr[left.item] < ItemDescr[right.item];
        }else
            return left.type < right.type;
    }
};

#endif // EVENT_H
