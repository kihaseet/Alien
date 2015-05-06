#include "inventory.h"
#include "ui_inventory.h"

Inventory::Inventory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inventory)
{
    ui->setupUi(this);
}

Inventory::~Inventory()
{
    delete ui;
}

void Inventory::AddButton(QPushButton* button){
    ui->horizontalLayout->addWidget(button);
}

void Inventory::RemoveButton(QPushButton* button){
    ui->horizontalLayout->removeWidget(button);
}
