#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    _serv=new Server(21277,this);
    _xmlmaker = new xml_maker();
    _game=new game();

    connect(ui->action_3,SIGNAL(triggered()),_game,SLOT(start()));
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(UpdateVotelist()));
    connect(ui->playerlist,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(updateInventory(QListWidgetItem*)));

    connect(_serv, SIGNAL(sendToAnalise(QString,QString)), _xmlmaker, SLOT(new_analise(const QString,const QString)));
    connect(_serv,SIGNAL(addLogToGui(QString,QString)),this,SLOT(onAddLogToGui(QString,QString)));
    connect(_serv,SIGNAL(client_disconnected(QString)),_game,SLOT(slot_disconnected(QString)));

    connect(_xmlmaker,SIGNAL(newname(QString,QString)),_game,SLOT(register_new_player(QString,QString)));
    connect(_xmlmaker,SIGNAL(registerRolebyPlayer(QString,QString)),_game,SLOT(registerRolebyPlayer(QString,QString)));
    connect(_xmlmaker,SIGNAL(namecorrect(QString,QString)),_serv,SLOT(verifyClientName(QString,QString)));
    connect(_xmlmaker,SIGNAL(noVerifyClientName(QString)),_serv,SLOT(noVerifyClientName(QString)));
    connect(_xmlmaker,SIGNAL(sendtoclient(QString,QString)),_serv,SLOT(slotsendToClient(QString,QString)));
    connect(_xmlmaker,SIGNAL(xml_create(QString,QString,QString,QString,QQueue<QString>)),
            _game,SLOT(make_events(QString,QString,QString,QString,QQueue<QString>)));
    connect(_xmlmaker,SIGNAL(xml_create_norot(QString,QString,QString,QString)),
            _game,SLOT(make_events(QString,QString,QString,QString)));

    connect(_game,SIGNAL(send_actionlist(player*)),_xmlmaker,SLOT());
    connect(_game,SIGNAL(namecorrect(QString,QString)),_xmlmaker,SLOT(slotnamecorrect(QString,QString)));
    connect(_game,SIGNAL(nonamecorrect(QString)),_xmlmaker,SLOT(nonamecorrect(QString)));
    connect(_game,SIGNAL(sendrolelist2all (QMap <QString,player*>,QList<QString>)),
            _xmlmaker,SLOT(updaterolelist(QMap <QString,player*>,QList<QString>)));
    connect(_game,SIGNAL(rolecorrect(QString)),_xmlmaker,SLOT(rolecorrect(QString)));
    connect(_game,SIGNAL(norolecorrect(QString)),_xmlmaker,SLOT(norolecorrect(QString)));
    connect(_game,SIGNAL(startnewsessionenable(bool)),this,SLOT(newGameSessionStatus(bool)));

    //connect(_game,SIGNAL(startday()),_game,SLOT(day()));
    connect(_game,SIGNAL(GuiUpdatePlayerlist(QMap<QString,player*>)),this,SLOT(updatePlayerlist(QMap<QString,player*>)));
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
    foreach (item* var, _game->playerlist.value(ss->text())->itemlist.values()) {//пока что убраны должности в списке игроков, подумать над обрезанием
        ui->itemlist->addItem(var->name);
    }
    ui->text_info->clear();
    foreach (QString var, _game->playerlist.value(ss->text())->rolelist){
            ui->text_info->append(var);
    }
    ui->text_info->append("HP: "+QString::number(_game->playerlist.value(ss->text())->HP));
    ui->text_info->append("Status: "+QString::number(_game->playerlist.value(ss->text())->status));
    ui->text_info->append("Invasion: "+QString::number(_game->playerlist.value(ss->text())->invasion));
    QPair<QString,QList<QString> > varr;
    foreach (varr, _game->playerlist.value(ss->text())->actionlist) {
        ui->text_info->append("Action: "+varr.first);
        foreach (QString vav,varr.second){
            ui->text_info->append("Action: "+varr.first+" - "+vav);
        }
    }

   // ui->textBrowser_2->clear();
   // ui->textBrowser_2->append(_game->itemlist.value(ss->text())->name);
   // ui->textBrowser_2->append(_game->itemlist.value(ss->text())->note);
}

void MainWindow::updatePlayerlist(QMap<QString,player*>playerlist){
    ui->text_info->clear();
    QStringList play;
    foreach (player* var, playerlist.values()) {
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
