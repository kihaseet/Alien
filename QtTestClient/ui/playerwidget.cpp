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
    ui->labelName->setText(name);
    ui->labelStatus->setText(status);
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void PlayerWidget::SetStatus(QString st){
    ui->labelStatus->setText(st);
}

void PlayerWidget::giveRole(QString r){
    rolelist.append(r);
    name = r+name;
     ui->labelName->setText(name);
}
void PlayerWidget::delRole(QString r){
    if(rolelist.contains(r)){
        rolelist.removeOne(r);

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
    ui->labelVote->setText(vote);
}

void PlayerWidget::setBackColor( const QColor &c )
{
        QPalette p = palette();
        p.setColor(backgroundRole(), c);
        setPalette(p);
}
