#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "lobby.h"
#include "start.h"
#include "game.h"
#include "alienclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //AlienClient client;

public slots:
    void GoLobbyWindow();
    void GoGameWindow();
    void Disconnect();
    
private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    Lobby* lobbyWindow;
    start* startWindow;
    Game* gameWindow;
};

#endif // MAINWINDOW_H
