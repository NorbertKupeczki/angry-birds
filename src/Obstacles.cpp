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
  speed = INIT_SPEED;
}

void Boulder::MoveBoulder(float dt)
{
  if(visible)
  {
    speed *= 1.1;
    sprite->move(0.0,speed * dt);
  }
}

void Boulder::resetSpeed()
{
  speed = INIT_SPEED;
}
