#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QStackedWidget>
#include <QMap>
#include "lobbyregistername.h"
#include "lobbyregisterrole.h"
#include "lobbywaiting.h"
#include "types.h"

namespace Ui {
class Lobby;
}

class Lobby : public QWidget
{
    Q_OBJECT

public:
    explicit Lobby(QWidget *parent = 0);
    ~Lobby();

   // QMap <QString,QString>* players;
    LobbyRegisterName* lobbyRegisterName;
    LobbyRegisterRole* lobbyRegisterRole;
    LobbyWaiting* lobbyWaiting;

public slots:
    void updatePlayerList(QMap<QString, QString> players);
    void setSelectWindow(SELECT_TYPE status);

private:
    Ui::Lobby *ui;
    QStackedWidget *stackedWidget;
};

#endif // LOBBY_H
