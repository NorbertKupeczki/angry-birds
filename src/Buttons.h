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
  virtual void mouseOver(sf::Vector2i cursor);
  bool activeBtn();
  void click();
  void setPosition (float x, float y);

 protected:
  sf::Sprite* sprite = nullptr;
  sf::Texture active_texture;
  sf::Texture inactive_texture;
  sf::Sound* button_hover = nullptr;
  sf::Sound* button_click = nullptr;

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

class OptionsMenuButtons : public Buttons
{
 public:
  virtual void mouseOver(sf::Vector2i cursor) override;
  void switchTexture();
  bool isSelected();

 private:
  bool selected = false;
};

class Lvl1Button : public OptionsMenuButtons
{
};

class Lvl2Button : public OptionsMenuButtons
{
};

class Lvl3Button : public OptionsMenuButtons
{
};

class AcceptButton : public OptionsMenuButtons
{
};

class MusicButton : public OptionsMenuButtons
{
};

class VolumeSlider : public OptionsMenuButtons
{
 public:
  bool isGrabbed();
  void grabSlider();
  void releaseSlider();
  void moveSlider(sf::RenderWindow& window);
  virtual void mouseOver(sf::Vector2i cursor) override;

  const int MIN_POS = 687;
  const int MAX_POS = 839;

 private:
  bool grabbed = false;
};

#endif // ANGRYBIRDS_BUTTONS_H
