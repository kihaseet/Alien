#ifndef STATUS
#define STATUS

#include <QString>

enum Status
{
    UP = 8,
    DOWN = 9,
    DIED = -4,
};

namespace StatusProcess
{
    QString statusToString(Status status);
}

#endif // STATUS

