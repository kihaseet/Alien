#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qclickablelabel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameClient = new GameClient();
    gameConfig = new GameConfig();
    InventoryMode = false;
    selectTargetMode.currentButton = -1;
    selectTargetMode.multiSelect = false;
    colsCount = 4;

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

    connect(gameClient, SIGNAL(dayUpdate(int,bool)), this, SLOT(dayUpdate(int,bool)));
    connect(gameClient, SIGNAL(endVoting()), this, SLOT(endVoting()));
    connect(gameClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(gameClient, SIGNAL(errorLog(QString)), this, SLOT(errorLog(QString)));
    connect(gameClient, SIGNAL(log(QString)), this, SLOT(log(QString)));
    connect(gameClient, SIGNAL(registerNameStatus(bool)), this, SLOT(registerNameStatus(bool)));
    connect(gameClient, SIGNAL(registerRoleStatus(bool)), this, SLOT(registerRoleStatus(bool)));
    connect(gameClient, SIGNAL(startVoting(Vote)), this, SLOT(startVoting(Vote)));
    connect(gameClient, SIGNAL(updateActions(QVector<Action>)), this, SLOT(updateActions(QVector<Action>)));
    connect(gameClient, SIGNAL(updateItems(QVector<Item>)), this, SLOT(updateItems(QVector<Item>)));
    connect(gameClient, SIGNAL(updatePlayers(QVector<Player>)), this, SLOT(updatePlayers(QVector<Player>)));
    connect(gameClient, SIGNAL(voteUpdate(QString,int)), this, SLOT(voteUpdate(QString,int)));
}

MainWindow::~MainWindow()
{
    gameClient->disconnectFromServer();
    delete ui;
}

QStringList MainWindow::generateRoleList(QStringList usedRoles)
{
    QStringList result;

    for (auto& role: gameConfig->getRoles())
    {
        if (usedRoles.contains(role))
        {
            if (role == "Assistant")
            {
                continue;
            }

            if (role != "Captain")
            {
                result << "Dep_" + role;
            }
            else if (!usedRoles.contains("Assistant"))
            {
                result << "Assistant";
            }
        }
        else
        {
            result << role;
        }
    }

    return result;
}

void MainWindow::writeLog(QString text)
{
    ui->lLog->addItem(text);
}

void MainWindow::clearSelection()
{
    selectTargetMode.currentButton = -1;

    for (int i = 0; i < playersWidgets.length(); i++)
    {
        playersWidgets[i]->makeSelectable(true);
    }

    for (int i = 0; i < itemsLabels.length(); i++)
    {
        itemsLabels[i]->setEnabled(true);
    }
}

void MainWindow::useItem(ItemType item)
{
    if (item != IT_BADGE && item != IT_BATTERY && item != IT_ROTATION)
    {
        for (int i = 0; i < playersWidgets.length(); i++)
        {
            playersWidgets[i]->makeSelectable(playersWidgets[i]->getPlayer().getStatus() != DIED);
        }

        selectTargetMode.multiSelect = false;
    }
    else if (item == IT_BADGE)
    {
        QStringList items;
        bool ok = false;

        for (int i = 0; i <= ITEMTYPE_LAST; i++)
        {
            if (gameClient->getWreckedItems().indexOf((ItemType)i) == -1)
            {
                items.append(ItemTypeProcess::ItemTypeToString((ItemType)i));
            }
        }

        QString selectedItem = QInputDialog::getItem(this, "[Badge] Select item", "Item", items, 0, false, &ok);

        QVector<ITarget> target;

        target.push_back(Item(ItemTypeProcess::ItemTypeByName(selectedItem), 0));

        if (ok && !selectedItem.isEmpty())
        {
            gameClient->doAction(ActionFactory::useBadge(Item(IT_BADGE, 0), target));
        }
    }
    else if (item == IT_BATTERY)
    {
        QStringList items;
        bool ok = false;

        for (int i = 0; i < gameClient->getWreckedItems().length(); i++)
        {
            items.append(ItemTypeProcess::ItemTypeToString(gameClient->getWreckedItems()[i]));
        }

        QString selectedItem = QInputDialog::getItem(this, "[Battery] Select item", "Item", items, 0, false, &ok);

        QVector<ITarget> target;

        target.push_back(Item(ItemTypeProcess::ItemTypeByName(selectedItem), 0));

        if (ok && !selectedItem.isEmpty())
        {
            gameClient->doAction(ActionFactory::useItem(Item(IT_BATTERY, 0), target));
        }
    }
    else if (item == IT_ROTATION)
    {
        QStringList playersNames;

        for (int i = 0; i < gameClient->getPlayers().length(); i++)
        {
            playersNames << "[ " + gameClient->getPlayers()[i].getRoles().join(", ") + " ] " + gameClient->getPlayers()[i].getName();
        }

        ui->lstPlayersRotation->addItems(playersNames);
    }
}

void MainWindow::ultItem(ItemType item)
{
    QMessageBox("TEST", "ULT", QMessageBox::Critical, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton, this).exec();
}

void MainWindow::doAction(Action action)
{
    clearSelection();
    gameClient->doAction(action);

    selectTargetMode.multiSelect = false;
}

void MainWindow::errorLog(QString text)
{
    this->writeLog("[ERROR]" + text);
}

void MainWindow::voteUpdate(QString playerName, int votes)
{
    for (QPlayerWidget* playerWidget: this->playersWidgets)
    {
        if (playerWidget->getPlayer().getName() == playerName)
        {
            playerWidget->setVote(votes);
            break;
        }
    }
}

void MainWindow::on_bConnect_clicked()
{
    QString address = ui->eAddress->text();

    gameClient->connectToServer(address);
}

void MainWindow::on_bRegisterName_clicked()
{
    QString name = ui->eName->text();

    gameClient->registerName(name);

    //this->registerNameStatus(true);
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

void MainWindow::onItemMouseClick(QPoint point)
{
    QLabel* lItem = (QLabel*)QObject::sender();

    int id = lItem->property("id").toInt();

    if (selectTargetMode.currentButton != -1)
    {
        if (selectTargetMode.currentButton == id)
        {
            clearSelection();
        }

        return;
    }

    selectTargetMode.currentButton = id;

    for (int i = 0; i < itemsLabels.length(); i++)
    {
        if (i != id)
        {
            itemsLabels[i]->setEnabled(false);
        }
    }

    int w = ui->lItem1->width();
    int h = ui->lItem1->width();


    auto pointInTriangle = [] (QPoint pt, QPoint p1, QPoint p2, QPoint p3) -> bool
    {
        auto sign = [](QPoint p1, QPoint p2, QPoint p3) -> float
        {
            return (p1.x() - p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y());
        };

        bool b1, b2, b3;

        b1 = sign(pt, p1, p2) < 0.0;
        b2 = sign(pt, p2, p3) < 0.0;
        b3 = sign(pt, p3, p1) < 0.0;

        return ((b1 == b2) && (b2 == b3));
    };


    if (this->InventoryMode)
    {
        ItemType item = (ItemType)lItem->property("type").toInt();

        if (pointInTriangle(point, QPoint(0, 0), QPoint(w, 0), QPoint(0, h))) // if in left-top triangle
        {
            useItem(item);
        }
        else
        {
            if (item == IT_MOP)
            {
                useItem(item);
            }
            else
            {
                ultItem(item);
            }
        }
    }
    else
    {
        Action action = *gameClient->getCurrentPlayer()->getAction((ActionType)lItem->property("type").toInt());
        doAction(action);
    }
}

void MainWindow::onPlayerClick(QString name)
{
    if (!name.isEmpty() && this->gameClient->getCurrentVoting() != nullptr)
    {
        if (this->gameClient->getCurrentVoting()->getCurrentTarget().isEmpty())
        {
            gameClient->doAction(ActionFactory::vote(this->gameClient->getPlayerByName(name)));
        }
        else if (this->gameClient->getCurrentVoting()->getCurrentTarget() == name)
        {
            gameClient->doAction(ActionFactory::unvote());
        }
    }
}

void MainWindow::registerNameStatus(bool isCorrect)
{
    if (!isCorrect)
    {
        QMessageBox("Sign In", "Incorrect name.", QMessageBox::Critical, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton, this).exec();
    }
    else
    {
        ui->swRegister->setCurrentIndex(1);
    }
}

void MainWindow::registerRoleStatus(bool isCorrect)
{
    if (!isCorrect)
    {
        QMessageBox("Sign In", "Incorrect role.", QMessageBox::Critical, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton, this).exec();
    }
}

void MainWindow::dayUpdate(int day, bool isDay)
{
    if (ui->swGame->currentIndex() != 2)
    {
        ui->swGame->setCurrentIndex(2);
    }
    this->tabs.updateDay((isDay ? "DAY: " : "NIGHT: ") + QString(day));
}

void MainWindow::startVoting(Vote &vote)
{
    this->tabs.updateDayInfo("Голосование на " + vote.getVotingFor());
}

void MainWindow::endVoting()
{
    this->tabs.updateDayInfo("");

    for (QPlayerWidget* playerWidget: this->playersWidgets)
    {
        playerWidget->setVote(-1);
    }
}

void MainWindow::updateActions(QVector<Action> actions)
{
    if (!this->InventoryMode)
    {
        for (int i = 0; i < actions.length(); i++)
        {
            itemsLabels[i]->setPixmap(QPixmap::fromImage(QImage(":/actions/" + QString((int)actions[i].getActionType()))));
            itemsLabels[i]->setProperty("type", QVariant((int)actions[i].getActionType()));
            itemsLabels[i]->setVisible(true);
        }

        for (int i = actions.length(); i < itemsLabels.length(); i++)
        {
            itemsLabels[i]->setVisible(false);
        }
    }
}

void MainWindow::updateItems(QVector<Item> items)
{
    if (this->InventoryMode)
    {
        for (int i = 0; i < items.length(); i++)
        {
            itemsLabels[i]->setText(items[i].getName());
            //itemsLabels[i]->setPixmap(QPixmap::fromImage(QImage(":/items/" + QString((int)items[i].getType()))));
            itemsLabels[i]->setProperty("type", QVariant((int)items[i].getType()));
            itemsLabels[i]->setVisible(true);
        }

        for (int i = items.length(); i < itemsLabels.length(); i++)
        {
            itemsLabels[i]->setVisible(false);
        }
    }
}

void MainWindow::updatePlayers(QVector<Player> players)
{
    auto findPlayer = [this](QString name) -> QPlayerWidget*
    {
        for (int i = 0; i < this->playersWidgets.length(); i++)
        {
            if (this->playersWidgets[i]->getPlayer().getName() == name)
            {
                return this->playersWidgets[i];
            }
        }

        return nullptr;
    };

    if (!this->isLobbyWindow)
    {
        for (int i = 0; i < players.length(); i++)
        {
            QPlayerWidget* player = findPlayer(players[i].getName());

            if (player != nullptr)
            {
                player->setPlayer(players[i]);
            }
            else
            {
                QPlayerWidget* pw = new QPlayerWidget(players[i], ui->PlayersWidgets);
                connect(pw, SIGNAL(clicked(QString)), this, SLOT(onPlayerClick(QString)));
                ((QGridLayout*)ui->PlayersWidgets->layout())->addWidget(pw, playersWidgets.length() / colsCount, playersWidgets.length() % colsCount);
                playersWidgets.push_back(pw);
            }
        }
    }
    else
    {
        qDeleteAll(playersWidgets);
        playersWidgets.clear();
        ui->lstPlayers->clear();

        QStringList usedRoles;

        for (int i = 0; i < players.length(); i++)
        {
            QPlayerWidget* pw = new QPlayerWidget(players[i], ui->PlayersWidgets);
            connect(pw, SIGNAL(clicked(QString)), this, SLOT(onPlayerClick(QString)));
            ((QGridLayout*)ui->PlayersWidgets->layout())->addWidget(pw, playersWidgets.length() / colsCount, playersWidgets.length() % colsCount);
            playersWidgets.push_back(pw);

            ui->lstPlayers->addItem("[" + players[i].getRoles().join(", ") + "] " + players[i].getName());

            usedRoles += players[i].getRoles();
        }

        ui->comboBox->clear();
        ui->comboBox->addItems(generateRoleList(usedRoles));
    }
}

void MainWindow::log(QString text)
{
    this->writeLog(text);
}

void MainWindow::on_lInventory_onclick()
{
    this->InventoryMode = !this->InventoryMode;

    if (this->InventoryMode)
    {
        ui->lInventory->setText("Закрыть");
        this->updateItems(gameClient->getCurrentPlayer()->getItems());
    }
    else
    {
        ui->lInventory->setText("Инвентарь");
        this->updateItems(gameClient->getCurrentPlayer()->getItems());
    }
}

void MainWindow::on_bApplyRotation_clicked()
{
    QVector<ITarget> targets;

    for (int i = 0; i < ui->lstPlayersRotation->count(); i++)
    {
        QString playerName = ui->lstPlayersRotation->item(i)->text().split("] ")[1];
        targets.append(ITarget(playerName));
    }

    doAction(ActionFactory::useItem(Item(IT_ROTATION, 0), targets));
}

void MainWindow::on_bCancelRotation_clicked()
{
    ui->swPresent->setCurrentIndex((int)tabs.getActiveTab());
    clearSelection();
}

void MainWindow::connected()
{
    ui->swGame->setCurrentIndex(1);
    ui->swRegister->setCurrentIndex(0);
    this->isLobbyWindow = true;
}

void MainWindow::on_comboBox_activated(const QString &role)
{
    gameClient->registerRole(role);
}
