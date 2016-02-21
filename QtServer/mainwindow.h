#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QtGui>
#include <QtCore>
#include <QMainWindow>
#include <QListWidgetItem>


#include "server.h"
#include "xml_maker.h"
#include "proto/protobuf_maker.h"
#include "game.h"

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
    Ui::MainWindow *ui;
    Server* _serv;
    Protocol* serilazer;
    game* _game;

public slots:
    void onAddLogToGui(QString name, QString string);
    void newGameSessionStatus(bool check);
    void updatePlayerlist(QList<player*>playerlist);
    void updateInventory(QListWidgetItem* ss);
    void updateInventoryInfo(QListWidgetItem* ss);
    void UpdateVotelist();
    void gameisover();
};

#endif // MAINWINDOW_H
