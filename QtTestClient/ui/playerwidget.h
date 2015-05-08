#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QMouseEvent>


namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT
private:
    void mousePressEvent ( QMouseEvent * event ){
        event->accept();
        emit mouseClick(this);
    }

public:
    void setBackColor( const QColor &c );
    explicit PlayerWidget(QString n, QString r, QWidget *parent = 0);
    ~PlayerWidget();
    QString name;
    QList <QString> rolelist;
    int HP;
    QString status; //↑ ↓ D
    QString vote;

    void SetStatus(QString st);
    void giveRole(QString r);
    void delRole(QString r);
    void setHP(int h);
    void setVote(int v);
signals:
    void mouseClick(PlayerWidget* noob);

private:
    Ui::PlayerWidget *ui;
};

#endif // PLAYERWIDGET_H
