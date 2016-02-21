#ifndef TYPES_H
#define TYPES_H
#include "proto/types.pb.h"
#include "proto/client.pb.h"
#include <QString>
#include <QMap>

//типы сообщений, привязанных к конкретному абоненту
enum PlayerChangeType {
    HP_CHANGE = 0,
    ALIEN = 1,
    STATUS_CHANGE = 2
};

//типы требований сервера для конкретных клиентских действий
enum RequestType {
    HARD_RESOLVE = 0,   //ожидание решения капитана
    NEED_ROTATION = 1,  //ожидание графика помощника
};

//типы ответов сервера на заявленные клиенские действия
enum ResultType {
    USED_ITEM = 0,
    USE_ACTION = 1
};

//типы серверных голосований
enum VotingType {
    FOR_ROLE = 0,
    FOR_ALIEN = 1
};

enum TimeType {
    NIGHT_TIME = 0,
    DAY_TIME = 1
};

//типы ответов сервера на регистрационные сообщения
enum RegisterStatusType {
    NAME_CORRECT = 0,
    NAME_INCORRECT = 1,
    ROLE_CORRECT = 2,
    ROLE_INCORRECT = 3
};

enum InvetoryChangeType {
    ADD_ITEM = 0,
    CHARGE_ITEM = 1,
    DEL_ITEM = 2,
    RECHARGE_ITEM = 3
};

enum TURN_TYPE {
    TT_DUTY         = -5,
    TT_DIED         = -4,
    TT_DAYTIME      = -3,
    TT_NIGHTTIME    = -2,//для ведения лога
    TT_NOTHING      = -1,

    TT_USE_ITEM     = 0,
    TT_ULT_ITEM     = 1,
    TT_USE_BADGE    = 2,
    TT_ATTACK       = 3,
    TT_INFECT       = 4,
    TT_VOTE         = 5,
    TT_UNVOTE       = 6,
    TT_SKIP         = 7,
    TT_UP           = 8,
    TT_DOWN         = 9,

    TT_REGNAME      = 10,
    TT_REGROLE      = 11,
    TT_ALIEN        = 12,
    TT_GETITEM      = 13,
    TT_DELITEM      = 14,
    TT_GETROLE      = 15,
    TT_DELROLE      = 16,
    TT_CORRECT      = 17,//для подтверждения действий
    TT_CHARGERED    = 18, //для пометки предмета батарейки
    TT_NEEDROTATION = 19,
    TT_HARDRESOLVE  = 20,
    TT_HP           = 21,
    TT_CONNECT      = 22,
    TT_DISCONNECT   = 23

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
    RT_DOCTOR = 2,
    RT_GUNMEN = 3,
    RT_ENGINEER = 4,
    RT_SCIENTIST = 5,
    RT_SIGNALMEN = 6,
    RT_ASSISTANT = 101,
    RT_DEP_DOCTOR = 102,
    RT_DEP_GUNMEN = 103,
    RT_DEP_ENGINEER = 104,
    RT_DEP_SCIENTIST = 105,
    RT_DEP_SIGNALMEN = 106
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
