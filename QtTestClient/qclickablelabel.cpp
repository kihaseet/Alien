#include "qclickablelabel.h"

QClickableLabel::QClickableLabel(QWidget *parent) : QLabel(parent)
{
}

void QClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
    emit onclick();
    emit onMouseClick(event->localPos().toPoint());
}

