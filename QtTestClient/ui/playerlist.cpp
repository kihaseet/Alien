#include "playerlist.h"
#include "ui_playerlist.h"

PlayerList::PlayerList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerList)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
}

PlayerList::~PlayerList()
{
    delete ui;
}

void PlayerList::startGame(QMap<QString, PlayerInfo> playerlist){

    foreach(QString noob, playlist.keys())
    {
        ui->gridLayout->removeWidget(playlist[noob]);
        // MEMORY LEAK???
        delete playlist[noob];
        playlist.remove(noob);
    }

    int i=-1;
    int j=0;
    foreach (QString name, playerlist.keys()) {
        PlayerWidget* noob = new PlayerWidget(name,playerlist[name].role.first(),this);
        playlist.insert(name,noob);
        //ui->gridLayout->addWidget(noob,j,++i);
        noob->setGeometry(110*(++i), 110*j, 110, 110);
        qDebug() << noob->pos().x() << " : " << noob->pos().y();
        if(i==3) {
            j++;
            i=-1;
        }
    }
}
