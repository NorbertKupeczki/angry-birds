#ifndef ANGRYBIRDS_BUTTONS_H
#define ANGRYBIRDS_BUTTONS_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Buttons
{
 public:
  Buttons();
  ~Buttons();

  void setTextures(std::string active_path, std::string inactive_path);
  void setTextures(std::string path);
  void setSounds(sf::SoundBuffer& hover_bfr, sf::SoundBuffer& click_bfr);
  sf::Sprite* getSprite();
  void mouseOver(sf::Vector2i cursor);
  bool activeBtn();
  void click();
  void setPosition (float x, float y);

 protected:
  sf::Sprite* sprite = nullptr;
  sf::Texture active_texture;
  sf::Texture inactive_texture;
  sf::Sound* button_hover = nullptr;
  sf::Sound* button_click = nullptr;

  bool visible;
  bool active;
};

class PlayButton : public Buttons
{
};

class HelpButton : public Buttons
{
};

class OptionsButton : public Buttons
{
};

class MenuButton : public Buttons
{
};

class QuitButton : public Buttons
{
};

class Lvl1Button : public Buttons
{
};

class Lvl2Button : public Buttons
{
};

class Lvl3Button : public Buttons
{
};

class AcceptButton : public Buttons
{
};

class CancelButton : public Buttons
{
};

class MusicButton : public Buttons
{
};

#endif // ANGRYBIRDS_BUTTONS_H
