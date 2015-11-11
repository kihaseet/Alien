#ifndef CONFIG_H
#define CONFIG_H

#include <QWidget>

namespace Ui {
class config;
}

class config : public QWidget
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = 0);
    ~config();

private:
    Ui::config *ui;
};

#endif // CONFIG_H
