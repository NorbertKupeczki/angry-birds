#ifndef ANGRYBIRDS_BUTTONS_H
#define ANGRYBIRDS_BUTTONS_H

#include "SFML/Graphics.hpp"

class Buttons
{
 public:
  Buttons();
  ~Buttons();

  void setTextures(std::string active_path, std::string inactive_path);
  sf::Sprite* getSprite();
  void mouseOver(sf::Vector2i cursor);
  bool activeBtn();
  void setPosition (float x, float y);

 protected:
  sf::Sprite* sprite;
  sf::Texture active_texture;
  sf::Texture inactive_texture;

  bool visible;
  bool active;
};

class Play : public Buttons
{
};

class Help : public Buttons
{
};

class Options : public Buttons
{
};

class Menu : public Buttons
{
};

class Quit : public Buttons
{
};

#endif // ANGRYBIRDS_BUTTONS_H
