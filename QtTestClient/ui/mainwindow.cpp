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

    connect(ALIENCLIENT.server_connection,SIGNAL(errormess(QString)),startWindow,SLOT(setLabelText(QString)));
    connect(ALIENCLIENT.server_connection,SIGNAL(sig_disconnect()),this,SLOT(Disconnect()));
    connect(&ALIENCLIENT,SIGNAL(updatePlayers(QMap<QString,PlayerInfo>&)),this,SLOT(GoLobbyWindow()));

    connect(&ALIENCLIENT,SIGNAL(registerStatus(SELECT_TYPE)),lobbyWindow,SLOT(setSelectWindow(SELECT_TYPE)));
    connect(&ALIENCLIENT,SIGNAL(updatePlayers(QMap<QString,PlayerInfo>&)),lobbyWindow,SLOT(updatePlayerList(QMap<QString,PlayerInfo>)));

    connect(&ALIENCLIENT,SIGNAL(updateInit(INIT_TYPE)),gameWindow,SLOT(UpdateInit(INIT_TYPE)));
    connect(&ALIENCLIENT,SIGNAL(updateActions(QVector<TurnObject>)),gameWindow,SLOT(updateActions(QVector<TurnObject>)));
    connect(&ALIENCLIENT,SIGNAL(updateEvents(QVector<EventInfo>)),gameWindow,SLOT(UpdateEvents(QVector<EventInfo>)));
    connect(&ALIENCLIENT,SIGNAL(startVoting(QString,QStringList)),gameWindow,SLOT(StartVoting(QString,QStringList)));
    connect(&ALIENCLIENT,SIGNAL(updateVoting(QMap<QString,QPair<int,QString> >)),gameWindow,SLOT(UpdateVoting(QMap<QString,QPair<int,QString> >)));
    connect(&ALIENCLIENT,SIGNAL(endVoting(QString,QString,QString)),gameWindow,SLOT(EndVoting(QString,QString,QString)));
    connect(&ALIENCLIENT,SIGNAL(updateItems(QMap<QString,int>&)),gameWindow,SLOT(UpdateItems(QMap<QString,int>&)));
    connect(&ALIENCLIENT,SIGNAL(updateStat(CurrectPlayerInfo&)),gameWindow,SLOT(UpdateStat(CurrectPlayerInfo&)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GoLobbyWindow(){
    if(stackedWidget->currentIndex()==0) stackedWidget->setCurrentIndex(1);
    connect(&ALIENCLIENT,SIGNAL(updateInit(INIT_TYPE)),this,SLOT(GoGameWindow()));
    disconnect(&ALIENCLIENT,SIGNAL(updatePlayers(QMap<QString,PlayerInfo>&)),this,SLOT(GoLobbyWindow()));
}

void MainWindow::GoGameWindow(){
    gameWindow->StartGame(ALIENCLIENT.players);
    if(stackedWidget->currentIndex()==1) stackedWidget->setCurrentIndex(2);
    disconnect(&ALIENCLIENT,SIGNAL(updateInit(INIT_TYPE)),this,SLOT(GoGameWindow()));
}

void MainWindow::Disconnect(){
    stackedWidget->setCurrentIndex(0);
    startWindow->setLabelText("Disconnect!..");
    connect(&ALIENCLIENT,SIGNAL(updatePlayers(QMap<QString,PlayerInfo>&)),this,SLOT(GoLobbyWindow()));
}

//AlienClient MainWindow::client;
