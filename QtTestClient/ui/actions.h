#ifndef ACTIONS_H
#define ACTIONS_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Actions;
}

class Actions : public QWidget
{
    Q_OBJECT

public:
    explicit Actions(QWidget *parent = 0);
    ~Actions();

    void AddButton(QPushButton *button);
    void RemoveButton(QPushButton *button);

private:
    Ui::Actions *ui;
};

#endif // ACTIONS_H
