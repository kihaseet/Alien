#ifndef QPLAYERWIDGET_H
#define QPLAYERWIDGET_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

#include "types/player.h"

namespace Ui {
class QPlayerWidget;
}

class QPlayerWidget : public QWidget
{
    Q_OBJECT
    PlayerPtr player;
    int vote;

    QVector<QLabel*> roleWidgets;
protected:
    void mouseReleaseEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*event);

public:
    explicit QPlayerWidget(QWidget *parent = 0);
    explicit QPlayerWidget(PlayerConstPtr& p, QWidget *parent = 0);
    ~QPlayerWidget();

    void setPlayer(PlayerConstPtr &p);
    PlayerPtr getPlayer();

    void setVote(int vote);
    int getVote();

    void makeSelectable(bool selectable);
signals:
    void clicked(QString name);
private:
    Ui::QPlayerWidget *ui;
};

#endif // QPLAYERWIDGET_H
