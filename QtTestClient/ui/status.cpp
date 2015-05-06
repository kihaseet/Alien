#include "status.h"
#include "ui_status.h"

Status::Status(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Status)
{
    ui->setupUi(this);
}

Status::~Status()
{
    delete ui;
}
