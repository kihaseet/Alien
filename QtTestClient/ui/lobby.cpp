#include "lobby.h"
#include "ui_lobby.h"
#include <QDebug>

Lobby::Lobby(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lobby)
{
    ui->setupUi(this);

    lobbyRegisterName = new LobbyRegisterName(this);
    lobbyRegisterRole = new LobbyRegisterRole(this);
    lobbyWaiting = new LobbyWaiting(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(lobbyRegisterName);
    stackedWidget->addWidget(lobbyRegisterRole);
    stackedWidget->addWidget(lobbyWaiting);

    ui->horizontalLayout->addWidget(stackedWidget);
    stackedWidget->setCurrentIndex(0);

    ui->listWidget->setAcceptDrops(true);
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);
}

void Lobby::resetLobby()
{
    stackedWidget->setCurrentIndex(0);
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::setSelectWindow(SELECT_TYPE status){  //изменяем
    switch (status)
    {
    case SRT_NAME_CORRECT:
        stackedWidget->setCurrentIndex(1);
        break;
    case SRT_NAME_INCORRECT:
        lobbyRegisterName->slot_wrongName();
        break;
    case SRT_ROLE_CORRECT:
        stackedWidget->setCurrentIndex(2);
        break;
    case SRT_ROLE_INCORRECT:
        lobbyRegisterRole->slot_wrong_role();
        break;
    }
}

void Lobby::updatePlayerList(  QMap<QString, QString> players){
    ui->listWidget->clear();
    lobbyRegisterRole->updateButtons(players.values());
    foreach (QString name, players.keys()) {
        QString txt;
        (players.value(name)=="") ?
                    txt = name
                : txt = "[" + players.value(name) + "]: "+name;
        new QListWidgetItem(txt,ui->listWidget,0);
    }

}
