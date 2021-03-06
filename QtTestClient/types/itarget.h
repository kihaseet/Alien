#ifndef ITARGET_H
#define ITARGET_H

#include <QString>

class ITarget
{
protected:
    QString name;
public:
    ITarget();
    ITarget(QString name);

    virtual QString getName() const;
    virtual void setName(QString name);
};

#endif // ITARGET_H
