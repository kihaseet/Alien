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
public:
    explicit AlienClient(QObject *parent = 0);
    ~AlienClient();

    bool connect_(QString addr);
    bool register_(QString name);
    bool selectRole(QString name);
    void makeTurn(TurnObject &turn);

private:
    QMap<QString, int> items;
    QMap<QString, PlayerInfo> players;

    tcpclient* server_connection;
    XmlProtocol protocol;

    CurrectPlayerInfo currentPlayer;

signals:
    waitLobby();
    updateItems(QMap<QString, int>& updated_items);
    updatePlayers(QMap<QString, PlayerInfo>& updated_players);
    updateActions(QVector<TurnObject> actions);
    updateStat(CurrectPlayerInfo& info);
    updateEvents(QVector<EventInfo> events);
    startVoting(QString target, QStringList players);
    updateVoting(QMap<QString, QPair<int, QString> > votelist);
    endVoting(QString target, QString result);
    updateInit(INIT_TYPE type);


private slots:
//    void GetParsedData(SERVER_RESPONSE_TYPE type, QMap<QString, PlayerInfo>& players);
    void onChange(onChangeInfo info);
    void onSelect(onSelectInfo info);
    void onInit(onInitInfo info);
    void errormess(QString mess);
    void disconnect();


public slots:
};

#endif // ALIENCLIENT_H
