#include "actions.h"
#include "ui_actions.h"

Actions::Actions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Actions)
{
    ui->setupUi(this);
}

Actions::~Actions()
{
    delete ui;
}

void Actions::AddButton(QPushButton* button){
    ui->horizontalLayout->addWidget(button);
}

void Actions::RemoveButton(QPushButton* button){
    ui->horizontalLayout->removeWidget(button);
}
