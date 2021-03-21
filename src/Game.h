
#ifndef ANGRYBIRDS_GAME_H
#define ANGRYBIRDS_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vector2.h"

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
  float getDistance(sf::Vector2<float> vector1,
                    sf::Vector2<float> vector2);
  void launchBird();

  sf::RenderWindow& window;

  sf::Sprite background_spr;
  sf::Texture background_tex;
  sf::Texture lvl1_tex;
  sf::Texture lvl2_tex;
  sf::Texture lvl3_tex;
  sf::Sprite sling_full_spr;
  sf::Texture sling_full_tex;
  sf::Sprite sling_left_spr;
  sf::Texture sling_left_tex;
  sf::Sprite bird_spr;
  sf::Texture bird_tex;

  enum GameState {
    MAIN_MENU = 0,
    IN_GAME = 1,
    GAME_WON = 2,
    GAME_LOST =3
  };

  GameState game_state;

  bool grabbed = false;
  bool launched = false;
  sf::Vector2f start_pos = {250,450};
  Vector2 bird_vector = {0,0};
  float speed = 0.0;
  float gravity = 0.007;
  const float MAX_DIST = 150.0;

};

#endif // ANGRYBIRDS_GAME_H
