#ifndef ANGRYBIRDS_BIRDS_H
#define ANGRYBIRDS_BIRDS_H

#include "GameObject.h"

class Birds : public GameObject
{
 public:
  Birds();
  ~Birds();

  bool isGrabbed();
  void setGrabbed(bool value);
  bool isLaunched();
  void setLaunched(bool value);

  void setSpeed(float value);
  float getSpeed();

  void setVector(Vector2 value);
  Vector2 getVector();
  void normaliseVector();

  void setStart(Vector2 value);
  Vector2 getStart();

 protected:
  bool grabbed = false;
  bool launched = false;
  Vector2 bird_vector = {0,0};
  Vector2 bird_start = {0,0};
  float speed = 0.0;

};

#endif // ANGRYBIRDS_BIRDS_H
