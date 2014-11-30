#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QtGui>
#include <QtCore>

#include "server.h"
#include "xml_maker.h"
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
    xml_maker* _xmlmaker;
    game* _game;

public slots:
    void onAddLogToGui(const QString string);
    void newGameSessionStatus(bool check);
};

#endif // MAINWINDOW_H
