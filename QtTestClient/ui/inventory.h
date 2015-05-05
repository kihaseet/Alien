#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>

namespace Ui {
class Inventory;
}

class Inventory : public QWidget
{
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = 0);
    ~Inventory();

private:
    Ui::Inventory *ui;
};

#endif // INVENTORY_H
