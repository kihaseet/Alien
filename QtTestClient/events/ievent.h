#ifndef IEVENT_H
#define IEVENT_H

#include <QString>

class IEvent
{
protected:
    QString who;
    QString target;
    QString what;
public:
    IEvent(QString what, QString who, QString target);
    virtual QString getDisplayMsg()
    {
        return "No event.";
    }
};

#endif // IEVENT_H
