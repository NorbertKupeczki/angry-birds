#ifndef ANGRYBIRDS_PIG_H
#define ANGRYBIRDS_PIG_H

#include "GameObject.h"

class Pig : public GameObject
{
 public:
  Pig();
  ~Pig();
  void setSound(sf::SoundBuffer& buffer);
  void squeek();

  int getValue();

 private:
  int value;
  sf::Sound* pig_squeek = nullptr;
};

#endif // ANGRYBIRDS_PIG_H
