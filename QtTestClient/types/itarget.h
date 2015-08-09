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

    QString getName() const;
    void setName(QString name);
};

#endif // ITARGET_H
