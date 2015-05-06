#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Inventory;
}

class Inventory : public QWidget
{
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = 0);
    ~Inventory();

    void AddButton(QPushButton *button);
    void RemoveButton(QPushButton *button);

private:
    Ui::Inventory *ui;
};

#endif // INVENTORY_H
