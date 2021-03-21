#include "GameObject.h"

GameObject::GameObject()
{
  sprite = new sf::Sprite;
}

GameObject::~GameObject()
{
  delete sprite;
}

void GameObject::setTexture(sf::Texture& texture)
{
  sprite->setTexture(texture);
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}