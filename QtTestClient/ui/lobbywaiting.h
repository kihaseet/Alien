#ifndef LOBBYWAITING_H
#define LOBBYWAITING_H

#include <QWidget>

namespace Ui {
class LobbyWaiting;
}

class LobbyWaiting : public QWidget
{
    Q_OBJECT

public:
    explicit LobbyWaiting(QWidget *parent = 0);
    ~LobbyWaiting();

private:
    Ui::LobbyWaiting *ui;
};

#endif // LOBBYWAITING_H
