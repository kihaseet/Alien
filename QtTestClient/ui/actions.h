#ifndef ACTIONS_H
#define ACTIONS_H

#include <QWidget>

namespace Ui {
class Actions;
}

class Actions : public QWidget
{
    Q_OBJECT

public:
    explicit Actions(QWidget *parent = 0);
    ~Actions();

private:
    Ui::Actions *ui;
};

#endif // ACTIONS_H
