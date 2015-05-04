#ifndef GAME
#define GAME

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

public slots:


private:
    Ui::Game *ui;
    QStackedWidget *stackedWidget;
};

#endif // GAME

