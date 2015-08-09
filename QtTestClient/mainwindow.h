#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QVector>
#include <QLabel>

#include "gameclient.h"
#include "protocol/xmlprotocol/xmlprotocol.h"
#include "types/currentplayer.h"
#include "types/vote.h"
#include "types/endvote.h"
#include "types/player.h"
#include "statupdate/istatupdate.h"
#include "events/ievent.h"
#include "gametabs.h"
#include "factories/actionfactory.h"

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
    void recalcActions();
    void updateItemsAndActions();
    void log(QString text);

private:
    CurrentPlayer* currentPlayer;
    GameClient* gameClient;
    IProtocol* protocol;
    GameTabs tabs;
    QVector<QLabel*> itemsLabels;
    int currentDay;
    bool InventoryMode;

private slots:
    void on_bConnect_clicked();

    void on_bRegisterName_clicked();

    void on_lTab2_onclick();

    void on_lTab3_onclick();

    void onTabClick(int tab_num);

private:
    Ui::MainWindow *ui;

public slots:
    void nameCorrect();
    void nameIncorrect();
    void roleCorrect();
    void roleIncorrect();
    void dayTime(int day);
    void nightTime();
    void startVote(Vote vote);
    void endVote(EndVote endvote);
    void playersUpdate(QVector<Player> players);
    void statUpdate(IStatUpdate stat);
    void event(IEvent event);
    void errorMessage(QString message);
    void disconnected();
};

#endif // MAINWINDOW_H
