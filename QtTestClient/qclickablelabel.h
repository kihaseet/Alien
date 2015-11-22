#ifndef QCLICKABLELABEL_H
#define QCLICKABLELABEL_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

class QClickableLabel : public QLabel
{
    Q_OBJECT

    bool is_selected;

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent*event);

public:
    QClickableLabel(QWidget* parent = 0);
    void setSelected(bool is_selected);

signals:
    void onMouseClick(QPoint point);
};

#endif // QCLICKABLELABEL_H
