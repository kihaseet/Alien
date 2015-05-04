#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    _serv=new Server(21277,this);
    _xmlmaker = new xml_maker();
    _game=new game();

   // config* conf = new config;
   // ui->ConfigLayout->addWidget(conf);

    connect(ui->action_3,SIGNAL(triggered()),_game,SLOT(start()));
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(UpdateVotelist()));
    connect(ui->playerlist,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(updateInventory(QListWidgetItem*)));
    connect(ui->itemlist,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(updateInventoryInfo(QListWidgetItem*)));


    connect(_serv, SIGNAL(sendToAnalise(int,QString)), _xmlmaker, SLOT(new_analise(int,const QString)));
    connect(_serv,SIGNAL(addLogToGui(QString,QString)),this,SLOT(onAddLogToGui(QString,QString)));
    connect(_serv,SIGNAL(client_disconnected(int)),_game,SLOT(slot_disconnected(int)));
    connect(_serv,SIGNAL(client_connected()),_game,SLOT(slotSendRolelist()));

    connect(_xmlmaker,SIGNAL(newname(int,QString,QString)),_game,SLOT(register_new_player(int,QString,QString)));
    connect(_xmlmaker,SIGNAL(registerRolebyPlayer(int,QString)),_game,SLOT(registerRolebyPlayer(int,QString)));
   // connect(_xmlmaker,SIGNAL(noVerifyClientName(QString)),_serv,SLOT(noVerifyClientName(int)));
    connect(_xmlmaker,SIGNAL(sendtoclient(int,QString)),_serv,SLOT(slotsendToClient(int,QString)));
    connect(_xmlmaker,SIGNAL(send_to_all(QString)),_serv,SLOT(send2all(QString)));
    connect(_xmlmaker,SIGNAL(xml_create(int,QString,QString,QString,QQueue<QString>)),
            _game,SLOT(make_events(int,QString,QString,QString,QQueue<QString>)));
    connect(_xmlmaker,SIGNAL(xml_create_norot(int,QString,QString,QString)),
            _game,SLOT(make_events(int,QString,QString,QString)));

    connect(_game,SIGNAL(send_actionlist(player*)),_xmlmaker,SLOT());
    connect(_game,SIGNAL(namecorrect(int)),_xmlmaker,SLOT(slotnamecorrect(int)));
    connect(_game,SIGNAL(nonamecorrect(int)),_xmlmaker,SLOT(nonamecorrect(int)));
    connect(_game,SIGNAL(sendrolelist2all (QList <player*>)),_xmlmaker,SLOT(updaterolelist(QList <player*>)));
    connect(_game,SIGNAL(rolecorrect(int)),_xmlmaker,SLOT(rolecorrect(int)));
    connect(_game,SIGNAL(norolecorrect(int)),_xmlmaker,SLOT(norolecorrect(int)));
    connect(_game,SIGNAL(startnewsessionenable(bool)),this,SLOT(newGameSessionStatus(bool)));

    //connect(_game,SIGNAL(startday()),_game,SLOT(day()));
    connect(_game,SIGNAL(GuiUpdatePlayerlist(QList<player*>)),this,SLOT(updatePlayerlist(QList<player*>)));
    connect(_game,SIGNAL(GuiUpdateVotelist(QMap <QString,QPair<QString,int> >)),this,SLOT(UpdateVotelist(QMap <QString,QPair<QString,int> >)));
    connect(_game,SIGNAL(GuiMess2Log(QString,QString)),this,SLOT(onAddLogToGui(QString,QString)));

    connect(_game,SIGNAL(send_nightmare(QQueue<ingame_event*>,QMap<QString,player*>)),
            _xmlmaker,SLOT(nightmare(QQueue<ingame_event*>,QMap<QString,player*>)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddLogToGui(QString name,QString string)
{
    ui->text_log->append(QTime::currentTime().toString()+" "+name+" "+string);
}

void MainWindow::updateInventory(QListWidgetItem* ss){
    ui->itemlist->clear();
    foreach (item* var, _game->playerlist->value(ss->text())->itemlist.values()) {//пока что убраны должности в списке игроков, подумать над обрезанием
        ui->itemlist->addItem(var->name);
    }
    ui->text_info->clear();
    foreach (QString var, _game->playerlist->value(ss->text())->rolelist){
            ui->text_info->append(var);
    }
    ui->text_info->append("HP: "+QString::number(_game->playerlist->value(ss->text())->HP));
    if(_game->playerlist->value(ss->text())->healthy==false)ui->text_info->append("В биованне");
    ui->text_info->append("Status: "+QString::number(_game->playerlist->value(ss->text())->status));
    ui->text_info->append("Invasion: "+QString::number(_game->playerlist->value(ss->text())->invasion));
    QPair<QString,QList<QString> > varr;
    foreach (varr, _game->playerlist->value(ss->text())->actionlist) {
        ui->text_info->append("Action: "+varr.first);
        foreach (QString vav,varr.second){
            ui->text_info->append("Action: "+varr.first+" - "+vav);
        }
    }
}

void MainWindow::updateInventoryInfo(QListWidgetItem* ss){
    ui->text_info->clear();
    foreach (item* var, _game->itemlist) {
        if(ss->text()==var->name){
             ui->text_info->append(var->name);
             ui->text_info->append(var->note);
             if(var->handle!="Rotation")ui->text_info->append("Заряд: "+QString::number(var->power));
             else foreach (QString vvar, _game->nightrotation) {
                  ui->text_info->append(vvar);
             }
        }
    }
}

void MainWindow::updatePlayerlist(QList <player*> playerlist){
    ui->text_info->clear();
    QStringList play;
    foreach (player* var, playerlist) {
        QString s;
        foreach (QString v, var->rolelist) {
            //s.append("["+v.left(3)+"]");
        }
        play.append(s+var->name);
    }
    ui->playerlist->clear();
    ui->playerlist->addItems(play);
}

void MainWindow::newGameSessionStatus(bool check){
    if(check) onAddLogToGui("Game","Можно начинать игру");
        ui->action_3->setEnabled(check);
        ui->action_2->setEnabled(!check);
}

void MainWindow::UpdateVotelist(){
    ui->text_info->clear();
    ui->text_log->append("Голосование:");
    //QPair<QString,int> var;
    foreach (QString var, _game->_currvoting->votelist.keys()) {
        ui->text_log->append(var+": "+_game->_currvoting->votelist.value(var).first+" ("
                              +QString::number(_game->_currvoting->votelist.value(var).second)+")");
    }
}
