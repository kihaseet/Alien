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

    connect(client.server_connection,SIGNAL(errormess(QString)),startWindow,SLOT(setLabelText(QString)));
    connect(client.server_connection,SIGNAL(sig_disconnect()),this,SLOT(Disconnect()));
    connect(&client,SIGNAL(updatePlayers(QMap<QString,PlayerInfo>&)),this,SLOT(GoLobbyWindow()));

    connect(&client,SIGNAL(registerStatus(SELECT_TYPE)),lobbyWindow,SLOT(setSelectWindow(SELECT_TYPE)));
    connect(&client,SIGNAL(updatePlayers(QMap<QString,PlayerInfo>&)),lobbyWindow,SLOT(updatePlayerList(QMap<QString,PlayerInfo>)));

    connect(&client,SIGNAL(updateInit(INIT_TYPE)),gameWindow,SLOT(UpdateInit(INIT_TYPE)));
    connect(&client,SIGNAL(updateActions(QVector<TurnObject>)),gameWindow,SLOT(updateActions(QVector<TurnObject>)));
    connect(&client,SIGNAL(updateEvents(QVector<EventInfo>)),gameWindow,SLOT(UpdateEvents(QVector<EventInfo>)));
    connect(&client,SIGNAL(startVoting(QString,QStringList)),gameWindow,SLOT(StartVoting(QString,QStringList)));
    connect(&client,SIGNAL(updateVoting(QMap<QString,QPair<int,QString> >)),gameWindow,SLOT(UpdateVoting(QMap<QString,QPair<int,QString> >)));
    connect(&client,SIGNAL(endVoting(QString,QString,QString)),gameWindow,SLOT(EndVoting(QString,QString,QString)));
    connect(&client,SIGNAL(updateItems(QMap<QString,int>&)),gameWindow,SLOT(UpdateItems(QMap<QString,int>&)));
    connect(&client,SIGNAL(updateStat(CurrectPlayerInfo&)),gameWindow,SLOT(UpdateStat(CurrectPlayerInfo&)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GoLobbyWindow(){
    if(stackedWidget->currentIndex()==0) stackedWidget->setCurrentIndex(1);
    connect(&client,SIGNAL(updateInit(INIT_TYPE)),this,SLOT(GoGameWindow()));
    disconnect(&client,SIGNAL(updatePlayers(QMap<QString,PlayerInfo>&)),this,SLOT(GoLobbyWindow()));
}

void MainWindow::GoGameWindow(){
    gameWindow->StartGame(client.players);
    if(stackedWidget->currentIndex()==1) stackedWidget->setCurrentIndex(2);
    disconnect(&client,SIGNAL(updateInit(INIT_TYPE)),this,SLOT(GoGameWindow()));
}

void MainWindow::Disconnect(){
    stackedWidget->setCurrentIndex(0);
    startWindow->setLabelText("Disconnect!..");
    connect(&client,SIGNAL(updatePlayers(QMap<QString,PlayerInfo>&)),this,SLOT(GoLobbyWindow()));
}

AlienClient MainWindow::client;
