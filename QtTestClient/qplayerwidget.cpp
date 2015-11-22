#include "qplayerwidget.h"
#include "ui_player.h"
#include <QDebug>

void QPlayerWidget::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked(this->player->getName());
}

void QPlayerWidget::paintEvent(QPaintEvent * event)
{
    QPainter p(this);

    p.drawPixmap(QPoint(0, 0), QPixmap::fromImage(QImage(":/player_widget/border.png")));

    QWidget::paintEvent(event);

    if (!this->isEnabled())
    {


        p.setOpacity(0.3);

        p.fillRect(0, 0, this->width(), this->height(), QColor::fromRgb(0, 0, 0));
    }
}

QPlayerWidget::QPlayerWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QPlayerWidget)
{
  ui->setupUi(this);

  roleWidgets.push_back(ui->lRole1);
  roleWidgets.push_back(ui->lRole2);
  roleWidgets.push_back(ui->lRole3);

  this->setVote(-1);
}
QPlayerWidget::QPlayerWidget(PlayerConstPtr &p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QPlayerWidget)
{
    ui->setupUi(this);

    roleWidgets.push_back(ui->lRole1);
    roleWidgets.push_back(ui->lRole2);
    roleWidgets.push_back(ui->lRole3);

    this->setPlayer(p);
    this->setVote(-1);
}

QPlayerWidget::~QPlayerWidget()
{
    delete ui;
}

void QPlayerWidget::setPlayer(PlayerConstPtr &p)
{
    this->player = std::make_shared<Player>(*p);

    ui->lPlayerName->setText(p->getName());
    ui->lOnline->setPixmap(QPixmap::fromImage(QImage(":/buttons/" + (p->isOnline() ? QString("online") : QString("offline") + ".png"))));
    for (int i = 0; i < player->getRoles().length(); i++)
    {
        roleWidgets[i]->setPixmap(QPixmap::fromImage(QImage(":/roles/" + player->getRoles()[i])));
    }

    ui->fPlayerImage->setStyleSheet("#fPlayerImage {background-image: url(:/player_avatar/" + QString::number(player->getImage()) + ");}");
}

PlayerPtr QPlayerWidget::getPlayer()
{
    return this->player;
}

void QPlayerWidget::setVote(int vote)
{
    if (vote == -1)
    {
        ui->lVotes->setText("");
    }
    else
    {
        ui->lVotes->setText(QString::number(vote));
        this->vote = vote;
    }
}

int QPlayerWidget::getVote()
{
    return vote;
}

void QPlayerWidget::makeSelectable(bool selectable)
{
    this->setEnabled(selectable);
}
