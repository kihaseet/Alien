#ifndef LOG_H
#define LOG_H

#include <QWidget>

namespace Ui {
class Log;
}

class Log : public QWidget
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent = 0);
    ~Log();
    void appendText(QString t);

private:
    Ui::Log *ui;
};

#endif // LOG_H
