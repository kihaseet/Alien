#include "statalien.h"

StatAlien::StatAlien()
{

}

void StatAlien::apply(CurrentPlayer &player)
{
    player.setAlien(true);
}

