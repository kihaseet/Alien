#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    _serv=new Server(21277);
    _xmlmaker = new xml_maker();
    _game=new game();

   // config* conf = new config;
   // ui->ConfigLayout->addWidget(conf);

    connect(ui->action_3,SIGNAL(triggered()),_game,SLOT(start()));
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(UpdateVotelist()));
    connect(ui->playerlist,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(updateInventory(QListWidgetItem*)));
    connect(ui->itemlist,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(updateInventoryInfo(QListWidgetItem*)));


    connect(_serv, SIGNAL(sendToAnalise(int,QString)), _xmlmaker, SLOT(newAnalise(int,QString)));
    connect(_serv,SIGNAL(addLogToGui(QString,QString)),this,SLOT(onAddLogToGui(QString,QString)));
    connect(_serv,SIGNAL(client_disconnected(int)),_game,SLOT(slot_disconnected(int)));
    connect(_serv,SIGNAL(client_connected()),_game,SLOT(slotSendRolelist()));

    connect(_xmlmaker,SIGNAL(sigRegisterCreate(RegisterObject)),_game,SLOT(registerNewPlayer(RegisterObject)));
    connect(_xmlmaker,SIGNAL(sigSendToClient(int,QString)),_serv,SLOT(slotsendToClient(int,QString)));
    connect(_xmlmaker,SIGNAL(sigSendToAll(QString)),_serv,SLOT(send2all(QString)));
    connect(_xmlmaker,SIGNAL(sigTurnCreate(int,TurnObject)),
            _game,SLOT(make_events(int,TurnObject)));

    connect(_game,SIGNAL(startGame(QList<player*>)),_xmlmaker,SLOT(slotStartGame(QList<player*>)));
    connect(_game,SIGNAL(namecorrect(int,bool)),_xmlmaker,SLOT(slotNameCorrect(int,bool)));
    connect(_game,SIGNAL(sendrolelist2all (QList <player*>)),_xmlmaker,SLOT(updaterolelist(QList <player*>)));
    connect(_game,SIGNAL(rolecorrect(int,bool)),_xmlmaker,SLOT(slotRoleCorrect(int,bool)));
    connect(_game,SIGNAL(startnewsessionenable(bool)),this,SLOT(newGameSessionStatus(bool)));

    connect(_game,SIGNAL(startPhase(int,bool)),_xmlmaker,SLOT(slotStartPhase(bool,int)));
    connect(_game,SIGNAL(startvote(ROLE,QList<QString>)),_xmlmaker,SLOT(slotStartVoting(ROLE,QList<QString>)));
    connect(_game,SIGNAL(endvote(ROLE,QString,QString)),_xmlmaker,SLOT(slotEndVoting(ROLE,QString,QString)));

    connect(_game,SIGNAL(send_votelist(QList<VoteObject*>)),_xmlmaker,SLOT(slotSendVoteList(QList<VoteObject*>)));
    connect(_game,SIGNAL(send_changes(TurnObject)),_xmlmaker,SLOT(slotSendTurn(TurnObject)));
    connect(_game,SIGNAL(send_stat(TurnObject)),_xmlmaker,SLOT(slotSendStat(TurnObject)));

    connect(_game,SIGNAL(GuiUpdatePlayerlist(QList<player*>)),this,SLOT(updatePlayerlist(QList<player*>)));
    connect(_game,SIGNAL(GuiUpdateVotelist()),this,SLOT(UpdateVotelist()));
    connect(_game,SIGNAL(GuiMess2Log(QString,QString)),this,SLOT(onAddLogToGui(QString,QString)));
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
    foreach (ITEM var, _game->playerlist->value(ss->text())->itemlist) {//пока что убраны должности в списке игроков, подумать над обрезанием
        ui->itemlist->addItem(TurnObject::ItemDescr.key(var));
    }
    ui->text_info->clear();
    foreach (ROLE var, _game->playerlist->value(ss->text())->rolelist){
            ui->text_info->append(RegisterObject::RoleDescr.key(var));
    }
    ui->text_info->append("HP: "+QString::number(_game->playerlist->value(ss->text())->HP));
    if(_game->playerlist->value(ss->text())->healthy==false)ui->text_info->append("В биованне");
    ui->text_info->append("Status: "+QString::number(_game->playerlist->value(ss->text())->status));
    ui->text_info->append("Invasion: "+QString::number(_game->playerlist->value(ss->text())->invasion));

    foreach (TurnObject varr, _game->playerlist->value(ss->text())->actionlist) {
        ui->text_info->append("Action: "+TurnObject::TurnDescr.key(varr.type) + " "+TurnObject::ItemDescr.key(varr.item));
        foreach (QString vav,varr.targets){
           //ui->text_info->append("Action: "+TurnObject::TurnDescr.key(varr.type) + " - "+vav);
        }
    }
}

void MainWindow::updateInventoryInfo(QListWidgetItem* ss){
    ui->text_info->clear();
    foreach (item* var, _game->itemlist) {
        if(ss->text()==var->getHandle()){
             ui->text_info->append(var->getHandle());
             ui->text_info->append(var->note);
             if(var->getID() != IT_ROTATION)ui->text_info->append("Заряд: "+QString::number(var->getPower()));
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
        foreach (ROLE v, var->rolelist) {
            //s.append("["+v.left(3)+"]");
        }
        play.append(var->name);
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
    foreach (VoteObject* var, _game->_currvoting->votelist) {
        ui->text_log->append(var->who+": "+var->whom+" ("
                              +QString::number(var->status)+")");
    }
}
