#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _serv=new Server(21277,this);
    _xmlmaker = new xml_maker();
    _game=new game();

    connect(ui->action_3,SIGNAL(triggered()),_game,SLOT(start()));

    connect(_serv, SIGNAL(addLogToGui(const QString,const QString)), _xmlmaker, SLOT(new_analise(const QString,const QString)));

    connect(_xmlmaker,SIGNAL(newname(QString,QString)),_game,SLOT(register_new_player(QString,QString)));
    connect(_xmlmaker,SIGNAL(registerRolebyPlayer(QString,QString)),_game,SLOT(registerRolebyPlayer(QString,QString));
    connect(_xmlmaker,SIGNAL(namecorrect(QString,QString)),_serv,SLOT(verifyClientName(QString,QString)));
    connect(_xmlmaker,SIGNAL(noVerifyClientName(QString)),_serv,SLOT(noVerifyClientName(QString)));
    connect(_xmlmaker,SIGNAL(sendtoclient(QString,QString)),_serv,SLOT(slotsendToClient(QString,QString)));
    connect(_xmlmaker,SIGNAL(xml_create(QString,QString,QString,QString,QQueue<QString>)),
            _game,SLOT(make_events(QString,QString,QString,QString,QQueue<QString>)));


    connect(_game,SIGNAL(send_actionlist(player*)),_xmlmaker,SLOT());
    connect(_game,SIGNAL(namecorrect(QString,QString)),_xmlmaker,SLOT(slotnamecorrect(QString,QString)));
    connect(_game,SIGNAL(nonamecorrect(QString)),_xmlmaker,SLOT(nonamecorrect(QString)));
    connect(_game,SIGNAL(sendrolelist2all (QMap <QString,player>,QMap<QString,player>)),
            _xmlmaker,SLOT(updaterolelist(QMap <QString,player>,QMap<QString,player>)));
    connect(_game,SIGNAL(rolecorrect(QString)),_xmlmaker,SLOT(rolecorrect(QString)));
    connect(_game,SIGNAL(norolecorrect(QString)),_xmlmaker,SLOT(norolecorrect(QString)));
    connect(_game,SIGNAL(startnewsessionenable(bool)),this,SLOT(newGameSessionStatus(bool)));

    connect(_game,SIGNAL(startday(QQueue<ingame_event*>,QMap<QString,player>,QMap<QString,item>)),
            _xmlmaker,SLOT(nightmare(QQueue<ingame_event*>,QMap<QString,player>,QMap<QString,item>)));




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddLogToGui(const QString string)
{
    ui->textBrowser->append(QTime::currentTime().toString()+" "+string);
}

void MainWindow::newGameSessionStatus(bool check){
    if(check)
        ui->action_3->setEnabled();
    else ui->action_3->setDisabled();
}
