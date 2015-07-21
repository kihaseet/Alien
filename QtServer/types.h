#ifndef TYPES_H
#define TYPES_H
#include <QString>
#include <QMap>

enum TURN_TYPE {
    TT_DIED = -4,
    TT_DAYTIME = -3,
    TT_NIGHTTIME = -2,//для ведения лога
    TT_NOTHING = -1,
    TT_DUTY = 0,
    TT_USE_BADGE = 1,
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
    TT_REGROLE,
    TT_GETROLE,
    TT_DELROLE,
    TT_CORRECT,//для подтверждения действий
    TT_HP
};

enum ITEM{
    IT_UNKNOW = -1,
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

enum ROLE{
    RT_ALIEN = -2,  //для голосований
    RT_UNKNOWN = -1,
    RT_PASSENGER = 0,
    RT_CAPTAIN,
    RT_ASSISTANT,
    RT_GUNMEN,
    RT_SCIENTIST,
    RT_SIGNALMEN,
    RT_DOCTOR,
    RT_ENGINEER,
    RT_DEP_GUNMEN,
    RT_DEP_SCIENTIST,
    RT_DEP_SIGNALMEN,
    RT_DEP_DOCTOR,
    RT_DEP_ENGINEER
};

struct RegisterObject{
public:
    ROLE role;
    QString name;
    int ID;

    static QMap <QString, ROLE> RoleDescr;
    static QMap <QString, ROLE> initColumn();

    RegisterObject(int id,QString n = QString()){
        ID = id;
        name = n;
    }
    RegisterObject(int id, ROLE r = RT_UNKNOWN){
        ID = id;
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
        return left.who == right.who &&
                left.whom == right.whom &&
                left.status == right.status;
    }
    VoteObject& operator=(const VoteObject& right){
        if (this == &right) {
            return *this;
        }
        who = right.who;
        whom = right.whom;
        status = right.status;
        return *this;
    }
};

#endif // TYPES_H
