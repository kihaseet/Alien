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
