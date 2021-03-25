#include "Buttons.h"
#include <iostream>

Buttons::Buttons()
{
  sprite = new sf::Sprite;
  button_hover = new sf::Sound;
  button_click = new sf::Sound;
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

//---------------------------- Options menu buttons ----------------------------

void OptionsMenuButtons::mouseOver(sf::Vector2i cursor)
{
  if (!active)
  {
    if (sprite->getGlobalBounds().contains(cursor.x, cursor.y))
    {
      active = true;
      button_hover->play();
    }
  }
  else
  {
    if (!sprite->getGlobalBounds().contains(cursor.x, cursor.y))
    {
      active = false;
    }
  }
}

void OptionsMenuButtons::switchTexture()
{
  if (selected)
  {
    sprite->setTexture(inactive_texture);
  }
  else if (!selected)
  {
    sprite->setTexture(active_texture);
  }
  selected = !selected;
}

bool OptionsMenuButtons::isSelected()
{
  return selected;
}

//------------------------------- Volume slider -------------------------------

bool VolumeSlider::isGrabbed()
{
  return grabbed;
}

void VolumeSlider::grabSlider()
{
  grabbed = true;
}

void VolumeSlider::releaseSlider()
{
  grabbed = false;
}

void VolumeSlider::moveSlider(sf::RenderWindow& window)
{
  setPosition(sf::Mouse::getPosition(window).x, sprite->getPosition().y);
  if (sprite->getPosition().x < MIN_POS)
  {
    sprite->setPosition(MIN_POS, sprite->getPosition().y);
  }
  else if (sprite->getPosition().x > MAX_POS)
  {
    sprite->setPosition(MAX_POS, sprite->getPosition().y);
  }
}

void VolumeSlider::mouseOver(sf::Vector2i cursor)
{
  if (!active)
  {
    if (sprite->getGlobalBounds().contains(cursor.x, cursor.y))
    {
      active = true;
    }
  }
  else
  {
    if (!sprite->getGlobalBounds().contains(cursor.x, cursor.y))
    {
      active = false;
    }
  }
}