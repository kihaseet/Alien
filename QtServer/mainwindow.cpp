#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _serv=new Server(21277,this);
    _xmlmaker = new xml_maker();
    _game=new game();

    connect(_serv, SIGNAL(addLogToGui(const QString,const QString)), _xmlmaker, SLOT(new_analise(const QString,const QString)));

    connect(_xmlmaker,SIGNAL(newname(QString,QString)),_game,SLOT(register_new_player(QString,QString)));
    connect(_xmlmaker,SIGNAL(namecorrect(QString,QString)),_serv,SLOT(verifyClientName(QString,QString)));
    connect(_xmlmaker,SIGNAL(noVerifyClientName(QString)),_serv,SLOT(noVerifyClientName(QString)));
    connect(_xmlmaker,SIGNAL(sendtoclient(QString,QString)),_serv,SLOT(slotsendToClient(QString,QString)));

    connect(_game,SIGNAL(namecorrect(QString,QString)),_xmlmaker,SLOT(slotnamecorrect(QString,QString)));
    connect(_game,SIGNAL(nonamecorrect(QString)),_xmlmaker,SLOT(nonamecorrect(QString)));
    connect(_game,SIGNAL(sendrolelist2all (QMap <QString,player>,QMap<QString,player>)),
            _xmlmaker,SLOT(updaterolelist(QMap <QString,player>,QMap<QString,player>)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddLogToGui(const QString string)
{
    ui->textBrowser->append(QTime::currentTime().toString()+" "+string);
}
