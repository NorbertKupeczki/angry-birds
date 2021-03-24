
#ifndef ANGRYBIRDS_GAME_H
#define ANGRYBIRDS_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vector2.h"
#include "Pig.h"
#include "Slingshot.h"
#include "Buttons.h"
#include "Options.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseReleased(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  void loadTexture(sf::Sprite& sprite, sf::Texture& texture, std::string path);
  void loadTexture(sf::Texture& texture, std::string path);
  void loadSound(sf::SoundBuffer& buffer, std::string path);
  void initTextures();
  void initButtons();
  void initSounds();
  void setButtonPosition();
  void initPigs(int level);
  void checkButtons(sf::Vector2i mouse_pos);
  float getDistance(sf::Vector2<float> vector1,
                    sf::Vector2<float> vector2);
  void moveBird(float dt, sf::Vector2f start_pos);
  void launchBird();
  void drawPigs();
  void drawButtons();
  void resetGame();

  sf::RenderWindow& window;

  sf::Sprite background_spr;
  sf::Texture background_tex;
  sf::Sprite pause_spr;
  sf::Texture pause_tex;
  sf::Texture lvl1_tex;
  sf::Texture lvl2_tex;
  sf::Texture lvl3_tex;
  sf::Texture game_won_tex;

  sf::Texture sling_full_tex;
  sf::Texture sling_left_tex;
  sf::Sprite bird_spr;
  sf::Texture bird_tex;
  sf::Texture pig_tex;

  sf::SoundBuffer menu_hover_bfr;
  sf::SoundBuffer menu_click_bfr;
  sf::SoundBuffer slingshot_launch;
  sf::SoundBuffer pig_squeek;
  sf::Music background_music;

  enum GameState {
    MAIN_MENU = 0,
    IN_GAME = 1,
    GAME_WON = 2,
    GAME_LOST =3
  };

  bool game_paused;

  GameState game_state;
  Slingshot slingshot;
  Options options;
  Pig* pigs = nullptr;

  PlayButton play_button;
  HelpButton help_button;
  OptionsButton options_button;
  MenuButton menu_button;
  QuitButton quit_button;

  const int NUMBER_OF_PIGS = 3;
  const float GRAVITY = 0.0011;
  const float MAX_DIST = 120.0;
  int pigs_left;
  float elapsed_time = 0;

  bool grabbed = false;
  bool launched = false;
  Vector2 bird_vector = {0,0};
  Vector2 bird_start = {0,0};
  float speed = 0.0;



};

#endif // ANGRYBIRDS_GAME_H
