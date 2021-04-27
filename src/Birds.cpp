#include "Birds.h"

Birds::Birds() {

}

Birds::~Birds()
{

}

bool Birds::isGrabbed()
{
  return grabbed;
}

void Birds::setGrabbed(bool value)
{
  grabbed = value;
}

bool Birds::isLaunched()
{
  return launched;
}

void Birds::setLaunched(bool value)
{
  launched = value;
}

float Birds::getSpeed()
{
  return speed;
}

void Birds::setSpeed(float value)
{
  speed = value;
}

void Birds::setVector(Vector2 value)
{
  bird_vector = value;
}

Vector2 Birds::getVector()
{
  return bird_vector;
}

void Birds::normaliseVector()
{
  bird_vector.normalise();
}

void Birds::setStart(Vector2 value)
{
  bird_start = value;
}

Vector2 Birds::getStart()
{
  return bird_start;
}
