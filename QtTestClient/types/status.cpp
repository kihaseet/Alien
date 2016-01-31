#include "status.h"

namespace StatusProcess
{
    QString statusToString(Status status)
    {
        switch(status)
        {
        case UP:
            return "встал";
        case DOWN:
            return "лег";
        case DIED:
            return "умер";
        default:
            return "unknown";
        }
    }
}
