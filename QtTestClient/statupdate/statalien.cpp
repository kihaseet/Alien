#include "statalien.h"

StatAlien::StatAlien()
{

}

void StatAlien::apply(CurrentPlayer &player) const
{
    player.setAlien(true);
}

