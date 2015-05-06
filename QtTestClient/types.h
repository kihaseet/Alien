#ifndef TYPES
#define TYPES

#include <QString>
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QPushButton>

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

enum SELECT_TYPE {
    SRT_NAME_CORRECT = 0,
    SRT_ROLE_CORRECT,
    SRT_NAME_INCORRECT,
    SRT_ROLE_INCORRECT,
};

struct EventInfo {
    EVENT_TYPE type;
    QStringList message;
};

struct TurnObject {
    TURN_TYPE type;
    QStringList targets;
    QString item;
    QPushButton* button;
    bool curr;

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

    friend bool operator == (const TurnObject& left, const TurnObject& right)
    {
       return
          left.item == right.item &&
          left.type == right.type;
    }
signals:
    buttonclicked();

};

struct CurrectPlayerInfo
{
    QString name;
    QStringList role;
    PLAYER_STATUS status;
    int health;
    bool infected;
    bool alien;
    bool onDuty;
    bool dead;
};

struct onChangeInfo {
    CurrectPlayerInfo updated_stats;
    QVector<EventInfo> events;
    QVector<TurnObject> avaible_actions;
//    QMap<QString, QStringList> update_list;
};

struct onSelectInfo {
    SELECT_TYPE type;
    QMap<QString, QString> players;
};

struct onInitInfo {
    INIT_TYPE type;

    QString target;
    QStringList data;
};

struct onVoteInfo {
    QMap<QString, QPair<int, QString> > votelist;
};

struct PlayerInfo {
    QString name;
    QStringList role;
    PLAYER_STATUS status;
    bool onDuty;
    bool dead;

    PlayerInfo(QString name, QStringList role, PLAYER_STATUS status)
    {
        this->name = name;
        this->role = role;
        this->status = status;
    }

    PlayerInfo()
    {}
};

#endif // TYPES

