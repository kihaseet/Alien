#include "lobbywaiting.h"
#include "ui_lobbywaiting.h"

LobbyWaiting::LobbyWaiting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LobbyWaiting)
{
    ui->setupUi(this);
}

LobbyWaiting::~LobbyWaiting()
{
    delete ui;
}
