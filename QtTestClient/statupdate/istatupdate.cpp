#include "statupdate/istatupdate.h"

IStatUpdate::IStatUpdate() : QObject(0)
{

}

void IStatUpdate::apply(CurrentPlayer &) const
{
}

