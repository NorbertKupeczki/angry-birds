#ifndef ANGRYBIRDS_SLINGSHOT_H
#define ANGRYBIRDS_SLINGSHOT_H

#include <SFML/Graphics/Sprite.hpp>
#include "GameObject.h"

class Slingshot : public GameObject
{
 public:
  Slingshot();
  ~Slingshot();

  void setPosition(float x, float y);
  sf::Sprite* getSpriteLeft();
  void setTexture(sf::Texture& texture_full, sf::Texture& texture_left);
  void setSound(sf::SoundBuffer& buffer);
  void launch();
  sf::Vector2f getLaunchPos();
  void drawTrajectory(sf::RenderWindow& window);
  void trajectory(sf::Vector2f origin, float GRAVITY);

 private:
  void initTrajectory();
  float getDistance(sf::Vector2<float> vector1,
                    sf::Vector2<float> vector2);

  static const int NUM_OF_CIRCLES = 16;
  sf::CircleShape circles[NUM_OF_CIRCLES];

  sf::Sprite* sprite_left;
  sf::Vector2f launch_pos = {250,450};

  sf::Sound* slingshot_launch = nullptr;
};

#endif // ANGRYBIRDS_SLINGSHOT_H
