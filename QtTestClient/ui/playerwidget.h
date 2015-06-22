#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>


namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT
protected:
    virtual void mouseReleaseEvent( QMouseEvent * event ){
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
    bool YetVoting; //если за него проголосовали

    void SetStatus(QString st);
    void giveRole(QString r);
    void delRole(QString r);
    void setHP(int h);
    void setVote(int v);
    void paintEvent(QPaintEvent *e);
signals:
    void mouseClick(PlayerWidget* noob);

private:
    Ui::PlayerWidget *ui;
};

#endif // PLAYERWIDGET_H
