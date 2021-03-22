
#ifndef ANGRYBIRDS_GAME_H
#define ANGRYBIRDS_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vector2.h"
#include "Pig.h"
#include "Slingshot.h"
#include "Buttons.h"

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
  void initTextures();
  void initButtons();
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
  sf::Texture lvl1_tex;
  sf::Texture lvl2_tex;
  sf::Texture lvl3_tex;
  sf::Texture game_won_tex;

  sf::Texture sling_full_tex;
  sf::Texture sling_left_tex;
  sf::Sprite bird_spr;
  sf::Texture bird_tex;
  sf::Texture pig_tex;

  enum GameState {
    MAIN_MENU = 0,
    IN_GAME = 1,
    GAME_WON = 2,
    GAME_LOST =3
  };

  bool game_paused;

  GameState game_state;
  Slingshot slingshot;
  Pig* pigs;

  Play play_button;
  Help help_button;
  Options options_button;
  Menu menu_button;
  Quit quit_button;

  const int NUMBER_OF_PIGS = 3;
  int pigs_left;

  bool grabbed = false;
  bool launched = false;
  sf::Vector2f start_pos = {250,450};
  Vector2 bird_vector = {0,0};
  float speed = 0.0;
  float gravity = 0.007;
  const float MAX_DIST = 150.0;

};

#endif // ANGRYBIRDS_GAME_H
