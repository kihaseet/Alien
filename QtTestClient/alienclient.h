#ifndef ALIENCLIENT_H
#define ALIENCLIENT_H

#include "types.h"
#include <QObject>
#include <QMap>
#include <QTcpSocket>
#include <QVector>
#include "xmlprotocol.h"

class AlienClient : public QObject
{
    Q_OBJECT
private:
    explicit AlienClient(QObject *parent = 0);
    ~AlienClient();
    AlienClient(const AlienClient& root);
    AlienClient& operator=(const AlienClient&);
public:
    static  AlienClient& Instance(){
        static AlienClient theSingleInstance;
        return theSingleInstance;
    }

    bool connect_(const QString addr);
    bool register_(QString name);
    bool selectRole(QString name);
    void makeTurn(TurnObject &turn);
    tcpclient* server_connection;
    QMap<QString, PlayerInfo> players;

private:
    QMap<QString, int> items;

    XmlProtocol protocol;

    CurrectPlayerInfo currentPlayer;

signals:
    void registerStatus(SELECT_TYPE status);
    void updateItems(QMap<QString, int>& updated_items);
    void updatePlayers(QMap<QString, QString> updated_players);
    void updateActions(QVector<TurnObject> actions);
    void updateStat(CurrectPlayerInfo& info);
    void updateEvents(QVector<EventInfo> events);
    void startVoting(QString target, QStringList playerss);
    void updateVoting(QMap<QString, QPair<int, QString> > votelist);
    void endVoting(QString target, QString name, QString result);
    void updateInit(INIT_TYPE type);


private slots:
    //    void GetParsedData(SERVER_RESPONSE_TYPE type, QMap<QString, PlayerInfo>& players);
    void onChange(onChangeInfo info);
    void onSelect(onSelectInfo info);
    void onInit(onInitInfo info);
    void onVote(onVoteInfo info);
    void errormess(QString mess);
    void disconnect();


public slots:
};

#define ALIENCLIENT AlienClient::Instance()
#endif // ALIENCLIENT_H
