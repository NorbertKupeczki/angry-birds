#ifndef ANGRYBIRDS_GAMEOBJECT_H
#define ANGRYBIRDS_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  void setTexture(sf::Texture& texture);
  sf::Sprite* getSprite();
  void setVisibility(bool value);
  bool isVisible();

 protected:
  bool visible;
  sf::Sprite* sprite = nullptr;
};

#endif // ANGRYBIRDS_GAMEOBJECT_H
