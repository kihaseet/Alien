#include "lobby.h"
#include "ui_lobby.h"

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

void Lobby::updatePlayerList(  QMap<QString, PlayerInfo> players){
    ui->listWidget->clear();
    lobbyRegisterRole->updateButtons(players.values());
    foreach (QString name, players.keys()) {
        QString txt;
        (players.value(name).role.isEmpty()) ?
                    txt = name
                : txt = "[" + players.value(name).role.first() + "]: "+name;
        new QListWidgetItem(txt,ui->listWidget,0);
    }
}
