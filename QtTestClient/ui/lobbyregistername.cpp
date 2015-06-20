#include "lobbyregistername.h"
#include "ui_lobbyregistername.h"
#include "alienclient.h"

LobbyRegisterName::LobbyRegisterName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LobbyRegisterName)
{
    ui->setupUi(this);
    ui->label->setText("Enter your nickname:");
    QRegExp rx("-?\\D{1,20}");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit->installEventFilter(this);
}

LobbyRegisterName::~LobbyRegisterName()
{
    delete ui;
}

void LobbyRegisterName::on_pushButton_clicked()
{
   // emit sendNewName("regname",ui->lineEdit->text());
    ALIENCLIENT.register_(this->ui->lineEdit->text());
    ui->label->setText("Please, wait...");
    ui->pushButton->setDisabled(true);
}

void LobbyRegisterName::slot_wrongName(){
    ui->label->setText("Ouuups! The name was changed, select another!");
    ui->pushButton->setEnabled(true);
}

