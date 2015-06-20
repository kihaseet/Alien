#include "playerwidget.h"
#include "ui_playerwidget.h"

PlayerWidget::PlayerWidget(QString n, QString r, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    name = n;
    rolelist.append(r);
    status = "↑";
    ui->setupUi(this);
    HP = 3;
    ui->labelName->setText(r+" "+name);
    ui->labelStatus->setText(status);
    YetVoting=false;
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
    QString n = r + ui->labelName->text();
    ui->labelName->setText(n);
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

void PlayerWidget::showVoteButton(bool show = true){
    ui->pushButton->setText("Голосовать");
    if(show)ui->pushButton->show();
    else ui->pushButton->hide();
}

void PlayerWidget::showUnVoteButton(bool show = true){
    ui->pushButton->setText("Снять голос");
    if(show)ui->pushButton->show();
    else ui->pushButton->hide();
}

void PlayerWidget::on_pushButton_clicked()
{
    if(YetVoting){
        emit Cansel_Voting(name);
        this->showUnVoteButton(false);
        YetVoting=false;
    }else{
        emit Accept_Voting(name);
        this->showUnVoteButton();
        YetVoting=true;
    }
}
