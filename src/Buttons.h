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

class OptionsMenuButtons : public Buttons
{
 public:
  virtual void mouseOver(sf::Vector2i cursor) override;
  void switchTexture();
  bool isSelected();

 protected:
  bool selected = false;
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
