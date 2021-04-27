#include "Slingshot.h"
#include <cmath>

Slingshot::Slingshot()
{
  sprite_left = new sf::Sprite;
  visible = true;
  setPosition(200.0,420.0);
  initTrajectory();
  slingshot_launch = new sf::Sound;
  score = 0;
  lives = MAX_LIVES;
}

Slingshot::~Slingshot()
{
  delete sprite_left;
  delete slingshot_launch;
}

void Slingshot::setPosition(float x, float y)
{
  sprite->setPosition(x, y);
  sprite_left->setPosition(x, y);
}

sf::Sprite* Slingshot::getSpriteLeft()
{
  return sprite_left;
}

void Slingshot::setTexture(sf::Texture& texture_full, sf::Texture& texture_left)
{
  sprite->setTexture(texture_full);
  sprite_left->setTexture(texture_left);
}

void Slingshot::setSound(sf::SoundBuffer& buffer)
{
  slingshot_launch->setBuffer(buffer);
}

void Slingshot::launch()
{
  slingshot_launch->play();
}

sf::Vector2f Slingshot::getLaunchPos()
{
  return launch_pos;
}

void Slingshot::drawTrajectory(sf::RenderWindow& window)
{
  for (const auto & circle : circles)
  {
    window.draw(circle);
  }
}

void Slingshot::trajectory(sf::Vector2f origin, float GRAVITY)
{
  float x_dist = getLaunchPos().x - origin.x;
  float y_dist = getLaunchPos().y - origin.y;
  float spd = getDistance(origin, getLaunchPos());
  Vector2 v = {x_dist, y_dist};
  v.normalise();
  for (int i = 0; i < NUM_OF_CIRCLES; ++i)
  {
    circles[i].setPosition(v.x * spd * (i+1) * 0.33 + origin.x,
                           v.y * spd * (i+1) * 0.33 + 0.5 * GRAVITY * pow(i * 20,2) + origin.y);
  }
}

void Slingshot::setLives(int value)
{
  lives = value;
}

void Slingshot::loseLife()
{
  if (lives > 0)
  {
    lives--;
  }
}

int Slingshot::getLives()
{
  return lives;
}

void Slingshot::addScore(int value)
{
  score += value;
}

void Slingshot::resetScore()
{
  score = 0;
}

int Slingshot::getScore()
{
  return score;
}

void Slingshot::initTrajectory()
{
  for (int i = 0; i < NUM_OF_CIRCLES; ++i)
  {
    circles[i].setRadius(3);
    circles[i].setOutlineThickness(1);
    circles[i].setFillColor(sf::Color(255,150,150,225));
    circles[i].setOutlineColor(sf::Color(255,0,0,255));
    circles[i].setOrigin(2,2);
  }
}

float Slingshot::getDistance(sf::Vector2<float> vector1,
                             sf::Vector2<float> vector2)
{
  float x = vector1.x - vector2.x;
  float y = vector1.y - vector2.y;
  float distance = sqrt(pow(x,2) + pow(y,2));
  return distance;
}

