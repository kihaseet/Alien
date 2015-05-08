#ifndef TARGETS_H
#define TARGETS_H

#include <QWidget>
#include "playerwidget.h"

namespace Ui {
class Targets;
}

class Targets : public QWidget
{
    Q_OBJECT

public:
    explicit Targets(QWidget *parent = 0);
    void addWidget(PlayerWidget *noob, int i, int j);

    ~Targets();

private:
    Ui::Targets *ui;
};

#endif // TARGETS_H
