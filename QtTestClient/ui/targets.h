#ifndef TARGETS_H
#define TARGETS_H

#include <QWidget>

namespace Ui {
class Targets;
}

class Targets : public QWidget
{
    Q_OBJECT

public:
    explicit Targets(QWidget *parent = 0);
    ~Targets();

private:
    Ui::Targets *ui;
};

#endif // TARGETS_H
