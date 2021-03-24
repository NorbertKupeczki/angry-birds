#include "Options.h"

Options::Options()
{
  options_bg_tex.loadFromFile("Data/Images/Options/options_bg.png");
  options_bg_spr.setOrigin(options_bg_tex.getSize().x / 2,
                           options_bg_tex.getSize().y / 2);
  level_selected = LEVEL1;
}

Options::~Options()
{

}

float Options::getMusicVolume()
{
  return music_volume;
}

bool Options::isMusicOn()
{
  return music_on;
}

int Options::levelSelected()
{
  return level_selected;
}

void Options::renderOptions(sf::RenderWindow& window)
{
  window.draw(options_bg_spr);
}
