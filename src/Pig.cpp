#include "Pig.h"

Pig::Pig()
{
  pig_squeek = new sf::Sound;
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