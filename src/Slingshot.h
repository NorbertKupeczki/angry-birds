#ifndef ANGRYBIRDS_SLINGSHOT_H
#define ANGRYBIRDS_SLINGSHOT_H

#include <SFML/Graphics/Sprite.hpp>
#include "GameObject.h"

class Slingshot : public GameObject
{
 public:
  Slingshot();

  void setPosition(float x, float y);
  sf::Sprite* getSpriteLeft();
  void setTexture(sf::Texture& texture_full, sf::Texture& texture_left)
  {
    sprite->setTexture(texture_full);
    sprite_left->setTexture(texture_left);
  }
  sf::Vector2f getLaunchPos();

 private:
  sf::Sprite* sprite_left;
  sf::Vector2f launch_pos = {250,450};
};

#endif // ANGRYBIRDS_SLINGSHOT_H
