#ifndef TYPES_H
#define TYPES_H
#include "proto/types.pb.h"
#include "proto/client.pb.h"
#include <QString>
#include <QMap>

enum TARGET_TYPE {
    XX_PERSON,
    XX_ITEM,
    XX_ROTATION
};

enum TURN_TYPE {
    TT_DIED = -4,
    TT_DAYTIME = -3,
    TT_NIGHTTIME = -2,//для ведения лога
    TT_NOTHING = -1,
    TT_DUTY = -5,
    TT_USE_ITEM = 0,
    TT_ULT_ITEM = 1,
    TT_USE_BADGE = 2,
    TT_ATTACK = 3,
    TT_INFECT = 4,
    TT_VOTE = 5,
    TT_UNVOTE = 6,
    TT_SKIP = 7,
    TT_UP = 8,
    TT_DOWN = 9,
    TT_ALIEN,
    TT_GETITEM,
    TT_DELITEM,
    TT_REGNAME,
    TT_REGROLE,
    TT_GETROLE,
    TT_DELROLE,
    TT_CORRECT,//для подтверждения действий
    TT_CHARGERED, //для пометки предмета батарейки
    TT_NEEDROTATION,
    TT_HARDRESOLVE,
    TT_HP
};

enum ITEM{
    IT_UNKNOW = -1,
    IT_BADGE = 0,
    IT_INJECTOR = 3,
    IT_SCANNER = 6,
    IT_MOP = 7,
    IT_BATTERY = 5,
    IT_BLASTER = 2,
    IT_NOTEBOOK = 4,
    IT_ROTATION = 1,
    IT_FETUS = 8
};

enum ROLE{
    RT_ALIEN = -2,  //для голосований
    RT_UNKNOWN = -1,
    RT_PASSENGER = 0,
    RT_CAPTAIN = 1,
    RT_ASSISTANT = 101,
    RT_GUNMEN = 3,
    RT_SCIENTIST = 5,
    RT_SIGNALMEN = 6,
    RT_DOCTOR = 2,
    RT_ENGINEER = 4,
    RT_DEP_GUNMEN = 103,
    RT_DEP_SCIENTIST = 105,
    RT_DEP_SIGNALMEN = 106,
    RT_DEP_DOCTOR = 102,
    RT_DEP_ENGINEER = 104
};

struct RegisterObject{
public:
    TURN_TYPE targets;
    ROLE role;
    QString name;
    int ID;

    static QMap <QString, ROLE> RoleDescr;
    static QMap <QString, ROLE> initColumn();

    RegisterObject(int id, TURN_TYPE tar, QString n = QString()){
        ID = id;
        targets = tar;
        name = n;
    }
    RegisterObject(int id, TURN_TYPE tar,::types::Role r){
        ID = id;
        targets = tar;
        role = (ROLE)r;
    }

    RegisterObject(int id, TURN_TYPE tar,ROLE r){
        ID = id;
        targets = tar;
        role = r;
    }
};

struct VoteObject{
public:
    QString who;
    QString whom;
    int status;

    VoteObject(QString wh){
        who = wh;
        whom = wh;
        status = 0;
    }
    friend bool operator == (const VoteObject& left, const VoteObject& right)
    {
        return left.who == right.who;
    }
    VoteObject& operator=(const VoteObject& right){
        /*if (this == &right) {
            return *this;
        }*/
        who = right.who;
        whom = right.whom;
        status = right.status;
        return *this;
    }
};

#endif // TYPES_H
