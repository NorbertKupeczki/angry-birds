#include "Options.h"

Options::Options(sf::RenderWindow& window)
{
  initMusic();
  background_music->play();

  options_bg_tex.loadFromFile("Data/Images/Options/options_bg.png");
  options_bg_spr.setTexture(options_bg_tex);
  options_bg_spr.setOrigin(options_bg_tex.getSize().x / 2,
                           options_bg_tex.getSize().y / 2);
  options_bg_spr.setPosition(window.getSize().x / 2,
                             window.getSize().y / 2);
  level_selected = LEVEL1;
  options_active = false;
}

Options::~Options()
{
  delete background_music;
}

void Options::initButtons(sf::SoundBuffer& hover_bfr,
                          sf::SoundBuffer& click_bfr,
                          sf::RenderWindow& window)
{
  accept_button.setTextures("Data/Images/Options/accept.png");
  music_button.setTextures("Data/Images/Options/music_off.png",
                           "Data/Images/Options/music_on.png");
  lvl1_button.setTextures("Data/Images/Options/lvl1_selected.png",
                           "Data/Images/Options/lvl1_deselected.png");
  lvl2_button.setTextures("Data/Images/Options/lvl2_selected.png",
                          "Data/Images/Options/lvl2_deselected.png");
  lvl3_button.setTextures("Data/Images/Options/lvl3_selected.png",
                          "Data/Images/Options/lvl3_deselected.png");
  volume_slider.setTextures("Data/Images/Options/volume_slider.png");

  accept_button.setPosition(window.getSize().x / 2,
                            window.getSize().y * 0.79);
  music_button.setPosition(window.getSize().x / 2 - 187,
                           window.getSize().y * 0.37);
  lvl1_button.setPosition(window.getSize().x / 2 - 190,
                          window.getSize().y * 0.6);
  lvl2_button.setPosition(window.getSize().x / 2,
                          window.getSize().y * 0.6);
  lvl3_button.setPosition(window.getSize().x / 2 + 190,
                          window.getSize().y * 0.6);
  volume_slider.setPosition(window.getSize().x / 2 + 199,
                            window.getSize().y * 0.3595);

  accept_button.setSounds(hover_bfr, click_bfr);
  music_button.setSounds(hover_bfr, click_bfr);
  lvl1_button.setSounds(hover_bfr, click_bfr);
  lvl2_button.setSounds(hover_bfr, click_bfr);
  lvl3_button.setSounds(hover_bfr, click_bfr);
  volume_slider.setSounds(hover_bfr, click_bfr);

  lvl1_button.switchTexture();
}

void Options::checkButtons(sf::Vector2i mouse_pos)
{
  accept_button.mouseOver(mouse_pos);
  music_button.mouseOver(mouse_pos);
  lvl1_button.mouseOver(mouse_pos);
  lvl2_button.mouseOver(mouse_pos);
  lvl3_button.mouseOver(mouse_pos);
  volume_slider.mouseOver(mouse_pos);
}

bool Options::isSliderGrabbed()
{
  return volume_slider.isGrabbed();
}

void Options::moveSlider(sf::RenderWindow& window)
{
  float d = volume_slider.MAX_POS - volume_slider.MIN_POS;
  volume_slider.moveSlider(window);
  music_volume = 50 * (volume_slider.getSprite()->getPosition().x - volume_slider.MIN_POS) / d;
  background_music->setVolume(music_volume);
}

void Options::initMusic()
{
  background_music = new sf::Music;
  background_music->openFromFile("Data/Audio/bg_music.ogg");
  background_music->setVolume(music_volume);
  background_music->setLoop(true);
}

bool Options::isOptionsActive()
{
  return options_active;
}

void Options::enterOptionsMenu()
{
  options_active = true;
}

int Options::levelSelected()
{
  return level_selected;
}

void Options::mouseClicked(sf::Event event)
{
  if (accept_button.activeBtn())
  {
    accept_button.click();
    options_active = false;
  }
  else if (music_button.activeBtn())
  {
    music_button.click();
    if (music_on)
    {
      background_music->pause();
    }
    else if (!music_on)
    {
      background_music->play();
    }
    music_on = !music_on;
    music_button.switchTexture();
  }
  else if (lvl1_button.activeBtn())
  {
    lvl1_button.click();
    level_selected = LEVEL1;
    if (!lvl1_button.isSelected())
    {
      lvl1_button.switchTexture();
      if (lvl2_button.isSelected())
      {
        lvl2_button.switchTexture();
      }
      else if (lvl3_button.isSelected())
      {
        lvl3_button.switchTexture();
      }
    }
  }
  else if (lvl2_button.activeBtn())
  {
    lvl2_button.click();
    level_selected = LEVEL2;
    if (!lvl2_button.isSelected())
    {
      lvl2_button.switchTexture();
      if (lvl1_button.isSelected())
      {
        lvl1_button.switchTexture();
      }
      else if (lvl3_button.isSelected())
      {
        lvl3_button.switchTexture();
      }
    }
  }
  else if (lvl3_button.activeBtn())
  {
    lvl3_button.click();
    level_selected = LEVEL3;
    if (!lvl3_button.isSelected())
    {
      lvl3_button.switchTexture();
      if (lvl2_button.isSelected())
      {
        lvl2_button.switchTexture();
      }
      else if (lvl1_button.isSelected())
      {
        lvl1_button.switchTexture();
      }
    }
  }
  else if (volume_slider.activeBtn())
  {
    volume_slider.grabSlider();
  }
}

void Options::mouseReleased(sf::Event event)
{
  if (volume_slider.isGrabbed())
  {
    volume_slider.releaseSlider();
  }
}

void Options::renderOptions(sf::RenderWindow& window)
{
  window.draw(options_bg_spr);
  window.draw(*accept_button.getSprite());
  window.draw(*music_button.getSprite());
  window.draw(*lvl1_button.getSprite());
  window.draw(*lvl2_button.getSprite());
  window.draw(*lvl3_button.getSprite());
  window.draw(*volume_slider.getSprite());
}
