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

Boulder::Boulder()
{
  speed = 1.0;
}

void Boulder::MoveBoulder(float dt)
{
  if(visible)
  {
    speed *= 1.2;
    sprite->move(0.0,speed * dt);
  }
}
