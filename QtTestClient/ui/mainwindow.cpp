#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lobbyWindow = new Lobby(this);
    startWindow = new start(this);
    gameWindow = new Game(this);

//    xmlManager = new xmlmaker();
//    server = new tcpclient(21277);
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(startWindow);
    stackedWidget->addWidget(lobbyWindow);
    stackedWidget->addWidget(gameWindow);
    setCentralWidget(stackedWidget);

    stackedWidget->setCurrentIndex(0);

//    connect(server,SIGNAL(errormess(QString)),startWindow,SLOT(setLabelText(QString)));
//    connect(server,SIGNAL(disconnect()),this,SLOT(Disconnect()));
//    connect(server,SIGNAL(GetData(QString)),xmlManager,SLOT(new_analise(QString)));

//    connect(startWindow,SIGNAL(ConnectClicked(QString)),server,SLOT(slotConnecting(QString)));
//    connect(xmlManager,SIGNAL(send2serv(QString)),server,SLOT(sendData(QString)));
//    connect(xmlManager,SIGNAL(signal_playerlist(QMap<QString,QString>)),lobbyWindow,SLOT(updatePlayerList(QMap<QString,QString>)));
//    connect(xmlManager,SIGNAL(signal_playerlist(QMap<QString,QString>)),this,SLOT(GoLobbyWindow()));
//    connect(xmlManager,SIGNAL(signal_NameCorrect()),lobbyWindow,SLOT(setSelectRoleWindow()));
//    connect(xmlManager,SIGNAL(signal_NoNameCorrect()),lobbyWindow->lobbyRegisterName,SLOT(slot_wrongName()));
//    connect(xmlManager,SIGNAL(signal_RoleCorrect()),lobbyWindow,SLOT(setWaitingWindow()));
//    connect(xmlManager,SIGNAL(signal_NoRoleCorrect()),lobbyWindow->lobbyRegisterRole,SLOT(slot_wrong_role()));

//    connect(lobbyWindow->lobbyRegisterName,SIGNAL(sendNewName(QString,QString)),xmlManager,SLOT(slot_sendNewName(QString,QString)));
//    connect(lobbyWindow->lobbyRegisterRole,SIGNAL(changeRole(QString,QString)),xmlManager,SLOT(slot_sendNewName(QString,QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GoLobbyWindow(){
    if(stackedWidget->currentIndex()==0) stackedWidget->setCurrentIndex(1);
}

void MainWindow::Disconnect(){
    stackedWidget->setCurrentIndex(0);
    startWindow->setLabelText("Disconnect!..");
}

AlienClient MainWindow::client;
