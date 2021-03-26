#include "Obstacles.h"

Obstacles::Obstacles()
{
  destructible = true;
}

void Obstacles::destroyObstacle()
{
  visible = false;
}

MetalObstacle::MetalObstacle()
{
  destructible = false;
}
