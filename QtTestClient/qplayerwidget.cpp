#include "qplayerwidget.h"
#include "ui_player.h"

void QPlayerWidget::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked(this->player.getName());
}

QPlayerWidget::QPlayerWidget(QWidget *parent) : QPlayerWidget(Player(), parent)
{

}

QPlayerWidget::QPlayerWidget(Player p, QWidget *parent) :
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

void QPlayerWidget::setPlayer(Player &p)
{
    this->player = p;

    ui->lPlayerName->setText(p.getName());
    ui->lOnline->setStyleSheet("#lOnline { background-image: url(:/player_status/" + (p.isOnline() ? QString("online") : QString("offline")) + "); }");
    for (int i = 0; i < player.getRoles().length(); i++)
    {
        roleWidgets[i]->setStyleSheet("background-image: url(:/roles/Captain);");
    }

    ui->fPlayerImage->setStyleSheet("#fPlayerImage {background-image: url(:/player_avatar/0);}");
}

Player &QPlayerWidget::getPlayer()
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
    }
}

void QPlayerWidget::makeSelectable(bool selectable)
{
    this->setEnabled(selectable);
}
