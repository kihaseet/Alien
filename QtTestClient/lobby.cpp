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

void Lobby::setSelectRoleWindow(){
    stackedWidget->setCurrentIndex(1);
}

void Lobby::setWaitingWindow(){
    stackedWidget->setCurrentIndex(2);
}

void Lobby::updatePlayerList(QMap<QString, QString> player){
    ui->listWidget->clear();
    lobbyRegisterRole->updateButtons(player.values());
    foreach (QString name, player.keys()) {
        new QListWidgetItem(player.value(name)+": "+name,ui->listWidget,0);
    }
}
