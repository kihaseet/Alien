#include "playerlist.h"
#include "ui_playerlist.h"

PlayerList::PlayerList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerList)
{
    ui->setupUi(this);
}

PlayerList::~PlayerList()
{
    delete ui;
}

void PlayerList::startGame(QMap <QString,QString> playerlist){
    int i=-1;
    int j=0;
    foreach (QString name, playerlist.keys()) {
        PlayerWidget* noob = new PlayerWidget(name,playerlist.value(name),this);
        playlist.insert(name,noob);
        ui->gridLayout->addWidget(noob,++i,j);
        if(i==3) {
            j++;
            i=-1;
        }
    }
}
