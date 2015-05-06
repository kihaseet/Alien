#ifndef GAME
#define GAME

#include <QWidget>
#include <QStackedWidget>
#include "types.h"
#include "actions.h"
#include "inventory.h"
#include "log.h"
#include "status.h"
#include "playerlist.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    int day;
    void StartGame(QMap<QString, PlayerInfo> play);

public slots:
    void updateActions(QVector<TurnObject> ActionsVector);
    void UpdateInit(INIT_TYPE type);
    void UpdateItems(QMap<QString, int>& updated_items);
    void UpdateStat(CurrectPlayerInfo& info);
    void UpdateEvents(QVector<EventInfo> events);
    void StartVoting(QString target, QStringList players);
    void UpdateVoting(QMap<QString, QPair<int, QString> > votelist);
    void EndVoting(QString target, QString name, QString result);
    void UpdatePlayers(QMap<QString, PlayerInfo>& updated_players);
    void MakeTurn();

private slots:
    void on_pushButton_clicked();

    void on_Button_log_clicked();

private:
    Ui::Game *ui;
    QStackedWidget *stackedWidgetInventory;
    QStackedWidget *stackedWidgetMain;
    Inventory* inventory;
    Actions* actions;
    Log* log;
    Status* status;
    PlayerList* playerlist;
    QVector<TurnObject> TurnObjectPool;
};

#endif // GAME

