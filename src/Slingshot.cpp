#include "Slingshot.h"

Slingshot::Slingshot()
{
  sprite_left = new sf::Sprite;
  visible = true;
  setPosition(200.0,420.0);
}

void Slingshot::setPosition(float x, float y)
{
  sprite->setPosition(x, y);
  sprite_left->setPosition(x, y);
}

sf::Sprite* Slingshot::getSpriteLeft()
{
  return sprite_left;
}

sf::Vector2f Slingshot::getLaunchPos()
{
  return launch_pos;
}