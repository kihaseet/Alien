#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QWidget>
#include <ui/playerwidget.h>
#include <QMap>
#include "types.h"

namespace Ui {
class PlayerList;
}

class PlayerList : public QWidget
{
    Q_OBJECT


public:
    QMap <QString, PlayerWidget*> playlist;
    explicit PlayerList(QWidget *parent = 0);
    ~PlayerList();
    void startGame (QMap<QString,PlayerInfo> playerlist);

private:
    Ui::PlayerList *ui;
};

#endif // PLAYERLIST_H
