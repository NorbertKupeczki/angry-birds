#ifndef ANGRYBIRDS_OPTIONS_H
#define ANGRYBIRDS_OPTIONS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Buttons.h"

class Options
{
 public:
  Options(sf::RenderWindow& window);
  ~Options();

  void initButtons(sf::SoundBuffer& hover_bfr,
                   sf::SoundBuffer& click_bfr,
                   sf::RenderWindow& window);
  void checkButtons(sf::Vector2i mouse_pos);
  bool isSliderGrabbed();
  void moveSlider(sf::RenderWindow& window);

  void initMusic();
  bool isOptionsActive();
  void enterOptionsMenu();
  int levelSelected();

  void mouseClicked(sf::Event event);
  void mouseReleased(sf::Event event);
  void renderOptions(sf::RenderWindow& window);

 private:
  sf::Sprite options_bg_spr;
  sf::Texture options_bg_tex;
  sf::Music* background_music = nullptr;
  const float MAX_VOLUME = 5.0;
  float music_volume;
  bool music_on = true;
  bool options_active;

  OptionsMenuButtons accept_button;
  OptionsMenuButtons music_button;
  OptionsMenuButtons lvl1_button;
  OptionsMenuButtons lvl2_button;
  OptionsMenuButtons lvl3_button;
  VolumeSlider volume_slider;

  enum LevelSelected {
    LEVEL1 = 1,
    LEVEL2 = 2,
    LEVEL3 = 3
  };

  LevelSelected level_selected;

};

#endif // ANGRYBIRDS_OPTIONS_H
