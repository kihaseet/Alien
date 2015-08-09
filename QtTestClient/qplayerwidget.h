#ifndef QPLAYERWIDGET_H
#define QPLAYERWIDGET_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QMouseEvent>

#include "types/player.h"

namespace Ui {
class QPlayerWidget;
}

class QPlayerWidget : public QWidget
{
    Q_OBJECT
    Player player;
    int vote;

    QVector<QLabel*> roleWidgets;
protected:
    void mouseReleaseEvent(QMouseEvent*);

public:
    explicit QPlayerWidget(QWidget *parent = 0);
    ~QPlayerWidget();

    void setPlayer(Player& p);
    void setVote(int vote);
signals:
    void clicked();
private:
    Ui::QPlayerWidget *ui;
};

#endif // QPLAYERWIDGET_H
