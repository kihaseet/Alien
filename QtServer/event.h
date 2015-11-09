#ifndef EVENT_H
#define EVENT_H
#include <QtCore>
#include "player.h"
#include "types.h"

class player;

struct TurnObject{
public:
    TURN_TYPE type;
    QQueue<QString> targets;
    ITEM item;
    
    player* wh;

    static QMap <QString, ITEM> ItemDescr;
    static QMap <QString, TURN_TYPE> TurnDescr;
    static QMap <ROLE, ITEM> RoleItem;
    static QMap<QString, ITEM> initColumnNames();
    static QMap<QString, TURN_TYPE> initColumnT();
    static QMap<ROLE, ITEM> initColumnRT();

    TurnObject(TURN_TYPE type,
               QStringList targets = QQueue<QString>(),
               ITEM item = IT_UNKNOW)
    {
        this->item = item;
        this->targets.append(targets);
        this->type = type;
    }

    TurnObject(TURN_TYPE type,
               QString targets,
               ITEM item = IT_UNKNOW)
    {
        this->item = item;
        this->targets.append(targets);
        this->type = type;
    }

    TurnObject(TURN_TYPE type, ITEM item)
    {
        this->item = item;
        this->type = type;
    }

    TurnObject()
    {
        item = IT_UNKNOW;
        targets = QQueue<QString>();
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
            if((right.item == IT_ROTATION && left.item == IT_ROTATION) &&
                    (right.targets.count() != left.targets.count()))
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

        if((left.type == TT_USE_ITEM && right.type == TT_USE_ITEM) ||
                (left.type == TT_ULT_ITEM && right.type == TT_ULT_ITEM))
        {
            return left.item < right.item;
        }else
            return left.type < right.type;
    }

};

#endif // EVENT_H
