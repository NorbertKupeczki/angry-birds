#ifndef ANGRYBIRDS_OBSTACLES_H
#define ANGRYBIRDS_OBSTACLES_H

#include "GameObject.h"

class Obstacles : public GameObject
{
 public:
  Obstacles();

  void destroyObstacle();
  bool isDestructible();

 protected:
  bool destructible;
};

class MetalObstacle : public Obstacles
{
 public:
  MetalObstacle();
};

class StoneObstacle : public Obstacles
{

};

class WoodObstacle : public Obstacles
{

};

class Boulder : public Obstacles
{
 public:
  Boulder();
  void MoveBoulder(float dt);
  void resetSpeed();

 private:
  const float INIT_SPEED = 30.0;
  float speed;
};

#endif // ANGRYBIRDS_OBSTACLES_H
