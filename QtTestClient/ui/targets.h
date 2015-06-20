#ifndef TARGETS_H
#define TARGETS_H

#include <QWidget>
#include "playerwidget.h"
#include <QListWidgetItem>

namespace Ui {
class Targets;
}

class Targets : public QWidget
{
    Q_OBJECT

public:
    QString currtarget;
    bool rot;
    explicit Targets(QWidget *parent = 0);
    void DisabledOkButton();
    void addWidgetBattery(QStringList items);
    void addWidgetRotation(QStringList items);
    void setLabel(QString items, QString button);
    void setUltScreen(QString object);

    ~Targets();
signals:
    void rotation(QStringList rota);

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Targets *ui;
};

#endif // TARGETS_H
