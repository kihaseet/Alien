#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include <QWidget>
#include <ui/playerwidget.h>
#include <QMap>

namespace Ui {
class PlayerList;
}

class PlayerList : public QWidget
{
    Q_OBJECT
    QMap <QString, QWidget*> playlist;

public:
    explicit PlayerList(QWidget *parent = 0);
    ~PlayerList();
    void startGame (QMap<QString,QString> playerlist);

private:
    Ui::PlayerList *ui;
};

#endif // PLAYERLIST_H
