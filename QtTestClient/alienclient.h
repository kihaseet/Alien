#ifndef ALIENCLIENT_H
#define ALIENCLIENT_H

#include <QObject>
#include <QMap>
#include <QTcpSocket>
#include <QVector>
#include "xmlprotocol.h"

enum XmlProtocol::SERVER_RESPONSE_TYPE;

class AlienClient : public QObject
{
    Q_OBJECT
public:
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
        QStirng role;
        PLAYER_STATUS status;
        bool onDuty;
    };

    struct CurrectPlayerInfo
    {
        QString name;
        QStirng role;
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


    explicit AlienClient(QObject *parent = 0);
    ~AlienClient();

    bool connect_(QString addr);
    bool register_(QString name);
    bool selectRole(QString name);
    void makeTurn(TurnObject &turn);

private:
    QMap<QString, int> items;
    QMap<QString, PlayerInfo> players;

    tcpclient server_connection;
    XmlProtocol protocol;

    CurrectPlayerInfo currentPlayer;

signals:
    waitLobby();
    updateItems(QMap<QString, int>& updated_items);
    updatePlayers(QMap<QString, PlayerInfo>& updated_players);
    updateActions(QVector<TurnObject> actions);
    updateStat(CurrectPlayerInfo& info);
    updateEvents(Qvector<EventInfo> events);
    startVoting(QString target, QStringList players);
    updateVoting(QMap<QString, QPair<int, QString>> votelist);
    endVoting(QString target, QString result);
    updateInit(INIT_TYPE type);


private slots:
    void GetParsedData(SERVER_RESPONSE_TYPE type, QMap<QString, AlienClient::PlayerInfo>& players);
    void errormess(QString mess);
    void disconnect();


public slots:
};

#endif // ALIENCLIENT_H
