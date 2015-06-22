#include "status.h"
#include "ui_status.h"

Status::Status(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Status)
{
    ui->setupUi(this);
}

void Status::updateStatus(CurrectPlayerInfo& inf)
{
    this->ui->lblHealth->setText(QString::number(inf.health));

    QString roles = "";
    foreach (QString role, inf.role) {
        roles += (role + "; ");
    }
    if (roles[0] == ';')
    {
        roles.remove(0, 2);
    }
    this->ui->lblRoles->setText(roles);

    switch(inf.status)
    {
    case PS_UP:
        this->ui->lblStatus->setText("↑");
        break;
    case PS_DOWN:
        this->ui->lblStatus->setText("↓");
        break;
    case PS_DEAD:
        this->ui->lblStatus->setText("D");
        break;
    }

    if (inf.alien && inf.infected)
    {
        this->ui->lblInfected->setText("Infected");
    }

    this->ui->lblHuman->setText(inf.alien ? "Alien" : "Human");

    this->ui->lblOnDuty->setText(inf.onDuty ? "On Duty" : "Not On Duty");
}

Status::~Status()
{
    delete ui;
}
