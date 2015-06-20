#include "start.h"
#include "ui_start.h"

start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    ui->lineEdit->setText("192.168.1.162");
}

start::~start()
{
    delete ui;
}

void start::on_pushButton_clicked()
{
    //emit ConnectClicked(ui->lineEdit->text());
    ALIENCLIENT.server_connection->connect_(ui->lineEdit->text(),21277);
        ui->label->setText("Connecting...");
        ui->pushButton->setDisabled(true);

}

void start::setLabelText(QString msg){
    ui->label->setText(msg);
    if(msg!="Loading player's list...") ui->pushButton->setEnabled(true);
}

