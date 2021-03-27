#include "Obstacles.h"

Obstacles::Obstacles()
{
  destructible = true;
}

void Obstacles::destroyObstacle()
{
  visible = false;
}

bool Obstacles::isDestructible()
{
    return destructible;
}

MetalObstacle::MetalObstacle()
{
  destructible = false;
}
