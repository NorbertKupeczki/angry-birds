#ifndef ANGRYBIRDS_BIRDS_H
#define ANGRYBIRDS_BIRDS_H

#include "GameObject.h"

class Birds : public GameObject
{
 public:
  //

 protected:
  bool grabbed = false;
  bool launched = false;
  Vector2 bird_vector = {0,0};
  Vector2 bird_start = {0,0};
  float speed = 0.0;

};

#endif // ANGRYBIRDS_BIRDS_H
