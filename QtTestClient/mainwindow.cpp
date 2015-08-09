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
    currentDay = 0;
    InventoryMode = false;

    ui->fBottom->layout()->setContentsMargins(0, 15, 0, 15);
    ui->fItemsAndActions->layout()->setContentsMargins(0, 15, 0, 15);

    tabs.addMainTabWidget(ui->lCurrentTab, ui->lAddCurrentTab_2, ui->fAddInfo);
    tabs.addSecTabWidget(ui->lTab2);
    tabs.addSecTabWidget(ui->lTab3);

    tabs.addTab(TAB_DAY, GameTab("DAY: 1", "Голосование на операцию"));
    tabs.addTab(TAB_PROFILE, GameTab("Профиль", ""));
    tabs.addTab(TAB_LOG, GameTab("Лог", ""));

    itemsLabels.push_back(ui->lItem1);
    ui->lItem1->setProperty("id", QVariant(1));
    itemsLabels.push_back(ui->lItem2);
    ui->lItem2->setProperty("id", QVariant(2));
    itemsLabels.push_back(ui->lItem3);
    ui->lItem3->setProperty("id", QVariant(3));
    itemsLabels.push_back(ui->lItem4);
    ui->lItem4->setProperty("id", QVariant(4));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recalcActions()
{
    updateItemsAndActions();
}

void MainWindow::updateItemsAndActions()
{

}

void MainWindow::log(QString text)
{
   ui->lLog->addItem(text);
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
    QMessageBox("Sign In", "Incorrect name.", QMessageBox::Critical, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton, this).exec();
}

void MainWindow::roleCorrect()
{
    // Okay
}

void MainWindow::roleIncorrect()
{
    QMessageBox("Sign In", "Incorrect role.", QMessageBox::Critical, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton, this).exec();
}

void MainWindow::dayTime(int day)
{
    this->recalcActions();
    tabs.updateDay("DAY: " + QString(day));
    tabs.updateDayInfo("Нет");
}

void MainWindow::nightTime()
{
    this->recalcActions();
    tabs.updateDay("NIGHT: " + QString(this->gameClient->getCurrentDay()));
    tabs.updateDayInfo("Нет");
}

void MainWindow::startVote(Vote vote)
{
    tabs.updateDayInfo("Голосование на " + vote.getVotingFor());
    this->recalcActions();
}

void MainWindow::endVote(EndVote endvote)
{
    tabs.updateDayInfo("Нет");
    log(endvote.getDisplayMsg());
    this->recalcActions();
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
