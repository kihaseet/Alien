#include "targets.h"
#include "ui_targets.h"

Targets::Targets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Targets)
{
    ui->setupUi(this);
    ui->label_2->setWordWrap(true);
}

Targets::~Targets()
{
    delete ui;
}

void Targets::setLabel(QString items,QString button){
    ui->label->setText(items);
    ui->pushButton->setText(button);
}

void Targets::addWidgetBattery(QStringList items){
    rot=false;
    ui->label_2->hide();
    ui->listWidget->clear();
    foreach (QString name, items) {
        new QListWidgetItem(name,ui->listWidget,0);
    }
}

void Targets::addWidgetRotation(QStringList items){
    rot=true;
    ui->label_2->hide();
    ui->listWidget->clear();
    ui->listWidget->setAcceptDrops(true);
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);
    foreach (QString name, items) {
        new QListWidgetItem(name,ui->listWidget,0);
    }
}

void Targets::setUltScreen(QString object){
    ui->label_2->setText(object);
    ui->listWidget->hide();
    ui->label_2->show();
}

void Targets::DisabledOkButton(){
    ui->pushButton->setDisabled(true);
}

void Targets::on_pushButton_clicked()
{
    QStringList listing;
    if(rot){
        for(int i = 0; i < ui->listWidget->count(); ++i)
        {
            QListWidgetItem* item = ui->listWidget->item(i);
            listing.append(item->text());
        }
    }else listing.append(currtarget);
    emit rotation(listing);
}

void Targets::on_listWidget_itemClicked(QListWidgetItem *item)
{
    currtarget = item->text();
    ui->pushButton->setEnabled(true);
}
