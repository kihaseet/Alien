#ifndef TYPES
#define TYPES

#include <QString>
#include <QStringList>

enum TURN_TYPE {
    TT_USE_ITEM = 0,
    TT_ULT_ITEM,
    TT_VOTE,
    TT_UNVOTE,
    TT_ATTACK,
    TT_INFECT,
    TT_DOWN,
    TT_UP,
    TT_SKIP
};

enum EVENT_TYPE {
    ET_DIED = 0,
    ET_USED_ITEM,
    ET_ULT_ITEM,
    ET_UPPED,
    ET_DOWNED,
    ET_SETTED_ROLE,
    ET_REMOVED_ROLE,
    ET_DUTIED,
    ET_MESSAGE
};

enum PLAYER_STATUS {
    PS_UP = 0,
    PS_DOWN,
    PS_DEAD
};

enum INIT_TYPE {
    IT_DAYTIME = 0,
    IT_NIGHTTIME,
    IT_VOTING_FOR_ROLE,
    IT_VOTING_FOR_ALIEN,
    IT_ENDVOTING_FOR_ROLE,
    IT_ENDVOTING_FOR_ALIEN
};

struct VotingInfo {

};

struct EventInfo {
    EVENT_TYPE type;
    QStringList message;
};

struct PlayerInfo {
    QString name;
    QString role;
    PLAYER_STATUS status;
    bool onDuty;

    PlayerInfo(QString name, QString role, PLAYER_STATUS status)
    {
        this->name = name;
        this->role = role;
        this->status = status;
    }
};

struct CurrectPlayerInfo
{
    QString name;
    QString role;
    PLAYER_STATUS status;
    int health;
    bool infected;
    bool alien;
    bool onDuty;
};

struct TurnObject {
    TURN_TYPE type;
    QStringList targets;
    QString item;

    TurnObject(TURN_TYPE type, QStringList targets, QString item)
    {
        this->item = item;
        this->targets = targets;
        this->type = type;
    }

    TurnObject()
    {
        item = "";
        targets = QStringList();
        type = TT_SKIP;
    }
};

enum SERVER_RESPONSE_TYPE {
    SRT_NAME_CORRECT = 0,
    SRT_ROLE_CORRECT,
    SRT_NAME_INCORRECT,
    SRT_ROLE_INCORRECT,
    SRT_LIST
};

#endif // TYPES

