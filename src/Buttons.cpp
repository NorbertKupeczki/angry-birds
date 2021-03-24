#include "Buttons.h"
#include <iostream>

Buttons::Buttons()
{
  sprite = new sf::Sprite;
  button_hover = new sf::Sound;
  button_click = new sf::Sound;
  visible = false;
  active = false;
}

Buttons::~Buttons()
{
  delete sprite;
  delete button_hover;
  delete button_click;
}

void Buttons::setTextures(std::string active_path, std::string inactive_path)
{
  if(!active_texture.loadFromFile(active_path))
  {
    std::cout << active_path <<" texture didn't load\n";
  }
  if(!inactive_texture.loadFromFile(inactive_path))
  {
    std::cout << active_path <<" texture didn't load\n";
  }

  sprite->setTexture(inactive_texture);
  sprite->setOrigin(active_texture.getSize().x / 2,
                    active_texture.getSize().y / 2);
}

void Buttons::setTextures(std::string path)
{
  if(!active_texture.loadFromFile(path))
  {
    std::cout << path <<" texture didn't load\n";
  }
  sprite->setTexture(active_texture);
  sprite->setOrigin(active_texture.getSize().x / 2,
                    active_texture.getSize().y / 2);
}

void Buttons::setSounds(sf::SoundBuffer& hover_bfr, sf::SoundBuffer& click_bfr)
{
  button_hover->setBuffer(hover_bfr);
  button_click->setBuffer(click_bfr);
}

sf::Sprite * Buttons::getSprite()
{
  return sprite;
}

void Buttons::mouseOver(sf::Vector2i cursor)
{
  if (!active)
  {
    if (sprite->getGlobalBounds().contains(cursor.x, cursor.y))
    {
      active = true;
      sprite->setTexture(active_texture);
      button_hover->play();
    }
  }
  else
  {
    if (!sprite->getGlobalBounds().contains(cursor.x, cursor.y))
    {
      active = false;
      sprite->setTexture(inactive_texture);
    }
  }
}

bool Buttons::activeBtn()
{
  return active;
}

void Buttons::click()
{
  button_click->play();
}

void Buttons::setPosition(float x, float y)
{
  sprite->setPosition(x, y);
}