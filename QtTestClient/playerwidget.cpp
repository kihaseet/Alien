#include "playerwidget.h"
#include "ui_player.h"

void PlayerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit clicked();
}

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

Player PlayerWidget::getPlayer()
{
    return this->player;
}

void PlayerWidget::setPlayer(Player &p)
{
    this->player = p;

}

void PlayerWidget::setVotes(int votes)
{
    this->votes = votes;

    ui->lVotes->setText((votes == -1 ? "" : QString(votes)));
}
