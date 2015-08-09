#include "qplayerwidget.h"
#include "ui_player.h"

void QPlayerWidget::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked();
}

QPlayerWidget::QPlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QPlayerWidget)
{
    ui->setupUi(this);

    roleWidgets.push_back(ui->lRole1);
    roleWidgets.push_back(ui->lRole2);
    roleWidgets.push_back(ui->lRole3);
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

void QPlayerWidget::setVote(int vote)
{
    if (vote == -1)
    {
        ui->lVotes->setText("");
    }
    else
    {
        ui->lVotes->setText(QString(vote));
    }
}
