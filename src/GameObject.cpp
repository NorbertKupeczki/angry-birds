#include "GameObject.h"

GameObject::GameObject()
{
  sprite = new sf::Sprite;
  visible = true;
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

void GameObject::setVisibility(bool value)
{
  visible = value;
}

bool GameObject::isVisible()
{
  return visible;
}