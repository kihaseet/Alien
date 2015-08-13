#ifndef IEVENT_H
#define IEVENT_H

#include <QString>
#include <QObject>
#include "types/eventtype.h"

class IEvent : public QObject
{
    Q_OBJECT
protected:
    QString who;
    QString target;
    QString what;
public:
    IEvent(QString what, QString who, QString target);
    IEvent(IEvent& e);
    virtual QString getWho() const
    {
        return who;
    }

    virtual QString getTarget() const
    {
        return target;
    }

    virtual QString getWhat() const
    {
        return what;
    }

    virtual QString getDisplayMsg() const
    {
        return "No event.";
    }
};

#endif // IEVENT_H
