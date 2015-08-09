#ifndef QCLICKABLELABEL_H
#define QCLICKABLELABEL_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>

class QClickableLabel : public QLabel
{
    Q_OBJECT
protected:
    void mouseReleaseEvent(QMouseEvent* event);

public:
    QClickableLabel(QWidget* parent = 0);

signals:
    void onclick();
};

#endif // QCLICKABLELABEL_H
