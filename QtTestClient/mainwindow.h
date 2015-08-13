#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QVector>
#include <QLabel>

#include "gameclient.h"
#include "gameconfig.h"
#include "protocol/xmlprotocol/xmlprotocol.h"
#include "types/currentplayer.h"
#include "types/vote.h"
#include "types/endvote.h"
#include "types/player.h"
#include "statupdate/istatupdate.h"
#include "events/ievent.h"
#include "gametabs.h"
#include "factories/actionfactory.h"
#include "qplayerwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QStringList generateRoleList(QStringList usedRoles);
    void writeLog(QString text);
    void selectTargets(QVector<QString> players);
    void clearSelection();
    void useItem(ItemType item);
    void ultItem(ItemType item);
    void doAction(Action action);

private:
    GameClient* gameClient;
    GameConfig* gameConfig;
    GameTabs tabs;
    QVector<QLabel*> itemsLabels;
    QVector<QPlayerWidget*> playersWidgets;
    bool InventoryMode;
    bool isLobbyWindow;

    struct
    {
        int currentButton;
        bool multiSelect;
    } selectTargetMode;

    int colsCount;

private slots:
    void on_bConnect_clicked();

    void on_bRegisterName_clicked();

    void on_lTab2_onclick();

    void on_lTab3_onclick();

    void onTabClick(int tab_num);

    void onItemMouseClick(QPoint point);

    void onPlayerClick(QString name);

    void on_lInventory_onclick();

    void on_bApplyRotation_clicked();

    void on_bCancelRotation_clicked();

    void on_comboBox_activated(const QString &role);

private:
    Ui::MainWindow *ui;

public slots:
    void connected();
    void registerNameStatus(bool isCorrect);
    void registerRoleStatus(bool isCorrect);
    void dayUpdate(int day, bool isDay);
    void startVoting(Vote& vote);
    void endVoting();
    void updateActions(QVector<Action> actions);
    void updateItems(QVector<Item> items);
    void updatePlayers(QVector<Player> players);
    void log(QString text);
    void errorLog(QString text);
    void voteUpdate(QString playerName, int votes);
};

#endif // MAINWINDOW_H
