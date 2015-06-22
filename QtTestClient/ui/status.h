#ifndef STATUS_H
#define STATUS_H

#include <QWidget>
#include <types.h>

namespace Ui {
class Status;
}

class Status : public QWidget
{
    Q_OBJECT

public:
    explicit Status(QWidget *parent = 0);
    void updateStatus(CurrectPlayerInfo& inf);
    ~Status();

private:
    Ui::Status *ui;
};

#endif // STATUS_H
