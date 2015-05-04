#ifndef START_H
#define START_H

#include <QWidget>

namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = 0);
    ~start();

private slots:
    void on_pushButton_clicked();
public slots:
    void setLabelText(QString msg);
private:
    Ui::start *ui;

signals:
    void ConnectClicked(QString addr);
};

#endif // START_H
