#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _serv=new Server(21277,this);
    _xmlmaker = new xml_maker();
    _game=new game();

    connect(ui->action_3,SIGNAL(triggered()),_game,SLOT(start()));

    connect(_serv, SIGNAL(sendToAnalise(QString,QString)), _xmlmaker, SLOT(new_analise(const QString,const QString)));
    connect(_serv,SIGNAL(addLogToGui(QString,QString)),this,SLOT(onAddLogToGui(QString,QString)));

    connect(_xmlmaker,SIGNAL(newname(QString,QString)),_game,SLOT(register_new_player(QString,QString)));
    connect(_xmlmaker,SIGNAL(registerRolebyPlayer(QString,QString)),_game,SLOT(registerRolebyPlayer(QString,QString)));
    connect(_xmlmaker,SIGNAL(namecorrect(QString,QString)),_serv,SLOT(verifyClientName(QString,QString)));
    connect(_xmlmaker,SIGNAL(noVerifyClientName(QString)),_serv,SLOT(noVerifyClientName(QString)));
    connect(_xmlmaker,SIGNAL(sendtoclient(QString,QString)),_serv,SLOT(slotsendToClient(QString,QString)));
    connect(_xmlmaker,SIGNAL(xml_create(QString,QString,QString,QString,QQueue<QString>)),
            _game,SLOT(make_events(QString,QString,QString,QString,QQueue<QString>)));


    connect(_game,SIGNAL(send_actionlist(player*)),_xmlmaker,SLOT());
    connect(_game,SIGNAL(namecorrect(QString,QString)),_xmlmaker,SLOT(slotnamecorrect(QString,QString)));
    connect(_game,SIGNAL(nonamecorrect(QString)),_xmlmaker,SLOT(nonamecorrect(QString)));
    connect(_game,SIGNAL(sendrolelist2all (QMap <QString,player*>,QList<QString>)),
            _xmlmaker,SLOT(updaterolelist(QMap <QString,player*>,QList<QString>)));
    connect(_game,SIGNAL(rolecorrect(QString)),_xmlmaker,SLOT(rolecorrect(QString)));
    connect(_game,SIGNAL(norolecorrect(QString)),_xmlmaker,SLOT(norolecorrect(QString)));
    connect(_game,SIGNAL(startnewsessionenable()),this,SLOT(newGameSessionStatus()));

    connect(_game,SIGNAL(startday(QQueue<ingame_event*>,QMap<QString,player>,QMap<QString,item>)),
            _xmlmaker,SLOT(nightmare(QQueue<ingame_event*>,QMap<QString,player>,QMap<QString,item>)));


   // connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(updateInventory(QListWidgetItem*)));

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
   // ui->textBrowser_2->clear();
   // ui->textBrowser_2->append(_game->itemlist.value(ss->text())->name);
   // ui->textBrowser_2->append(_game->itemlist.value(ss->text())->note);
}

void MainWindow::updatePlayerlist(QMap<QString,player*>playerlist){
    QStringList play;
    foreach (player* var, playerlist.values()) {
        QString s;
        foreach (QString v, var->rolelist) {
            s.append("["+v+"]");
        }
        play.append(s+var->name);
    }
    ui->playerlist->clear();
    ui->playerlist->addItems(play);
}

void MainWindow::newGameSessionStatus(){

        ui->action_3->setEnabled(true);
}
