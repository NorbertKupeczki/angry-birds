#include "Pig.h"

Pig::Pig()
{
  pig_squeek = new sf::Sound;
  sprite->setOrigin(25,22);

  value = 100;
}

Pig::~Pig()
{
  delete pig_squeek;
}

void Pig::setSound(sf::SoundBuffer& buffer)
{
  pig_squeek->setBuffer(buffer);
}

void Pig::squeek()
{
  pig_squeek->play();
}

int Pig::getValue()
{
  return value;
}