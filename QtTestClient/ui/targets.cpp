#include "targets.h"
#include "ui_targets.h"

Targets::Targets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Targets)
{
    ui->setupUi(this);
}

Targets::~Targets()
{
    delete ui;
}

void Targets::addWidget(PlayerWidget *noob, int i, int j){
    ui->gridLayout->addWidget(noob,i,j);
}
