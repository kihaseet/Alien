#include "qclickablelabel.h"

QClickableLabel::QClickableLabel(QWidget *parent) : QLabel(parent)
  , is_selected(false)
{
}

void QClickableLabel::setSelected(bool is_selected)
{
    this->is_selected = is_selected;
}

void QClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{

    emit onMouseClick(event->localPos().toPoint());
}

void QClickableLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter p(this);

    if (is_selected)
    {
        p.setPen(Qt::red);
        for (int i = 0; i < 5; i++)
        {
            p.drawRect(0 + i, 0 + i, this->width() - 2 * i, this->height() - 2 * i);
        }


        // TODO
        // p.drawPixmap(QPoint(0, 0), QPixmap::fromImage(QImage(":/player_widget/border.png")));
    }

}

