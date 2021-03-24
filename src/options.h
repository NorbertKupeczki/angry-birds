#ifndef ANGRYBIRDS_OPTIONS_H
#define ANGRYBIRDS_OPTIONS_H

#include <SFML/Graphics.hpp>
#include "Buttons.h"

class Options
{
 public:
  Options();
  ~Options();

  float getMusicVolume();
  bool isMusicOn();
  int levelSelected();

  void renderOptions(sf::RenderWindow& window);

 private:
  sf::Sprite options_bg_spr;
  sf::Texture options_bg_tex;
  float music_volume = 0.8;
  bool music_on = true;

  enum LevelSelected {
    LEVEL1 = 1,
    LEVEL2 = 2,
    LEVEL3 = 3
  };

  LevelSelected level_selected;

};

#endif // ANGRYBIRDS_OPTIONS_H
