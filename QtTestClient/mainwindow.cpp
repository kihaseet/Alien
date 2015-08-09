#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qclickablelabel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameClient = new GameClient();
    protocol = new XmlProtocol();

    ui->fBottom->layout()->setContentsMargins(0, 15, 0, 15);

    tabs.addMainTabWidget(ui->lCurrentTab, ui->lAddCurrentTab_2, ui->fAddInfo);
    tabs.addSecTabWidget(ui->lTab2);
    tabs.addSecTabWidget(ui->lTab3);

    tabs.addTab(TAB_DAY, GameTab("DAY: 1", "Голосование на операцию"));
    tabs.addTab(TAB_PROFILE, GameTab("Профиль", ""));
    tabs.addTab(TAB_LOG, GameTab("Лог", ""));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bConnect_clicked()
{
    QString address = ui->eAddress->text();

    //protocol->_connect(address);

    ui->swGame->setCurrentIndex(1);
}

void MainWindow::on_bRegisterName_clicked()
{
    QString name = ui->eName->text();

    //protocol->registerName(name);

    this->nameCorrect();
}

void MainWindow::nameCorrect()
{
    ui->swGame->setCurrentIndex(2);
}

void MainWindow::nameIncorrect()
{

}

void MainWindow::roleCorrect()
{

}

void MainWindow::roleIncorrect()
{

}

void MainWindow::dayTime()
{

}

void MainWindow::nightTime()
{

}

void MainWindow::startVote(Vote vote)
{

}

void MainWindow::endVote(EndVote endvote)
{

}

void MainWindow::playersUpdate(QVector<Player> players)
{

}

void MainWindow::statUpdate(IStatUpdate stat)
{

}

void MainWindow::event(IEvent event)
{

}

void MainWindow::errorMessage(QString message)
{

}

void MainWindow::disconnected()
{

}

void MainWindow::on_lTab2_onclick()
{
    onTabClick(1);
}

void MainWindow::on_lTab3_onclick()
{
    onTabClick(2);
}

void MainWindow::onTabClick(int tab_num)
{
    tabs.onClick(tab_num);

    switch(tabs.getActiveTab())
    {
    case TAB_DAY:
        ui->swPresent->setCurrentIndex(0);
        break;
    case TAB_PROFILE:
        ui->swPresent->setCurrentIndex(1);
        break;
    case TAB_LOG:
        ui->swPresent->setCurrentIndex(2);
        break;
    }
}
