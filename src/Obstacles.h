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

#endif // ANGRYBIRDS_OBSTACLES_H
