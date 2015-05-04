#include "playerwidget.h"
#include "ui_playerwidget.h"

PlayerWidget::PlayerWidget(QString n, QString r, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    name = r+" "+n;
    rolelist.append(r);
    status = "↑";
    ui->setupUi(this);
    HP = 3;
    ui->labelName=name;
    ui->labelStatus=status;
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void PlayerWidget::SetStatus(QString st){
    ui->labelStatus = st;
}

void PlayerWidget::giveRole(QString r){
    rolelist.append(r);
    name = r+name;
     ui->labelName=name;
}
void PlayerWidget::delRole(QString r){
    if(rolelist.contains(r)){
        rolelist.removeOne(role);

    }
}
void PlayerWidget::setHP(int h){
    HP = h;
}
void PlayerWidget::setVote(int v){
    vote = "";
    for(int i = 1;i<=v;i++){
        vote = vote+" *";
    }
    ui->labelVote=vote;
}
