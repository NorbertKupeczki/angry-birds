#include "LevelManager.h"
#include <cmath>
#include <iostream>

LevelManager::LevelManager()
{
  loadTexture(wood_tex, "Data/Images/Obstacles/obst_wood.png");
  loadTexture(stone_tex, "Data/Images/Obstacles/obst_stone.png");
  loadTexture(metal_tex, "Data/Images/Obstacles/obst_metal.png");
}

LevelManager::~LevelManager()
{
  deleteObstacles();
}

sf::Vector2f LevelManager::getPigCoords(int level,
                                        int pig_index,
                                        sf::RenderWindow& window)
{
  sf::Vector2f coordinates;

  if (level == 1)
  {
    coordinates = getLvl1PigCoords(pig_index, window);
  }
  else if (level == 2)
  {
    coordinates = getLvl2PigCoords(pig_index, window);
  }
  else if (level == 3)
  {
    coordinates = getLvl3PigCoords(pig_index, window);
  }

  return coordinates;
}

sf::Texture& LevelManager::levelTexture(int level,
                                        sf::Texture& lvl1,
                                        sf::Texture& lvl2,
                                        sf::Texture& lvl3)
{
  if (level == 1) {return lvl1;}
  else if (level == 2) {return lvl2;}
  else if (level == 3) {return lvl3;}
}

void LevelManager::createObstacles(int level, sf::RenderWindow& window)
{
  if (level == 1)
  {
    number_of_metals = 4;

    metal_obstacle = new MetalObstacle[number_of_metals];

    for (int i = 0; i < number_of_metals; ++i)
    {
      metal_obstacle[i].setTexture(metal_tex);
      metal_obstacle[i].getSprite()->setOrigin(metal_tex.getSize().x / 2,
                                               metal_tex.getSize().y /2);
      metal_obstacle[i].getSprite()->setPosition(
        window.getSize().x * 0.64 + i * metal_tex.getSize().x,
        window.getSize().y * 0.805);
    }
  }
  else if (level == 2)
  {
    number_of_metals = 9;
    number_of_woods = 1;

    metal_obstacle = new MetalObstacle[number_of_metals];
    wood_obstacle = new WoodObstacle[number_of_woods];

    for (int i = 0; i < number_of_metals; ++i)
    {
      metal_obstacle[i].setTexture(metal_tex);
      metal_obstacle[i].getSprite()->setOrigin(metal_tex.getSize().x / 2,
                                               metal_tex.getSize().y /2);
      if (i < 5)
      {
        metal_obstacle[i].getSprite()->setRotation(90);
        metal_obstacle[i].getSprite()->setPosition(
          window.getSize().x * 0.95,
          window.getSize().y * 0.2 + i * metal_tex.getSize().x);
      }
      else if (i == 5)
      {
        metal_obstacle[i].getSprite()->setRotation(90);
        metal_obstacle[i].getSprite()->setPosition(
          window.getSize().x * 0.95 - (metal_tex.getSize().x + metal_tex.getSize().y),
          window.getSize().y * 0.2 + metal_tex.getSize().y);
      }
      else
      {
        metal_obstacle[i].getSprite()->setPosition(
          window.getSize().x * 0.95 - (metal_tex.getSize().x + metal_tex.getSize().y) / 2,
          window.getSize().y * 0.25 * (i-5) + metal_tex.getSize().y/2 + 22 );
      }
    }

    wood_obstacle[0].setTexture(wood_tex);
    wood_obstacle[0].getSprite()->setOrigin(wood_tex.getSize().x / 2,
                                            wood_tex.getSize().y /2);
    wood_obstacle[0].getSprite()->setScale(1.3,1.0);
    wood_obstacle[0].getSprite()->setPosition(
      window.getSize().x * 0.95 - wood_tex.getSize().x + wood_tex.getSize().y * 0.5,
      window.getSize().y * 0.25 - wood_tex.getSize().x + wood_tex.getSize().y);
  }
}

void LevelManager::deleteObstacles()
{
  if (metal_obstacle != nullptr)
  {
    delete[] metal_obstacle;
    metal_obstacle = nullptr;
  }
  if (stone_obstacle != nullptr)
  {
    delete[] stone_obstacle;
    stone_obstacle = nullptr;
  }
  if (wood_obstacle != nullptr)
  {
    delete[] wood_obstacle;
    wood_obstacle = nullptr;
  }

  number_of_metals = 0;
  number_of_stones = 0;
  number_of_woods = 0;
}

bool LevelManager::collisionCheck(sf::Sprite& bird)
{
  bool collision;

  collision = checkObstacles(metal_obstacle, bird, number_of_metals) ||
              checkObstacles(stone_obstacle, bird, number_of_stones) ||
              checkObstacles(wood_obstacle, bird, number_of_woods);

  return collision;
}

bool LevelManager::checkObstacles(Obstacles* obstacles,
                                  sf::Sprite& bird,
                                  int array_size)
{
  bool collision = false;
  if (obstacles != nullptr)
  {
    for (int i = 0; i < array_size; ++i)
    {
      if (bird.getGlobalBounds().intersects(
        obstacles[i].getSprite()->getGlobalBounds()) &&
        obstacles[i].isVisible())
      {
        collision = true;
        if (obstacles[i].isDestructible())
        {
          obstacles[i].destroyObstacle();
        }
      }
    }
  }
  return collision;
}

void LevelManager::renderObstacles(sf::RenderWindow& window)
{
  if (metal_obstacle != nullptr)
  {
    for (int i = 0; i < number_of_metals; ++i)
    {
      if (metal_obstacle->isVisible())
      {
        window.draw(*metal_obstacle[i].getSprite());
      }
    }
  }
  if (stone_obstacle != nullptr)
  {
    for (int i = 0; i < number_of_stones; ++i)
    {
      if (stone_obstacle->isVisible())
      {
        window.draw(*stone_obstacle[i].getSprite());
      }
    }
  }
  if (wood_obstacle != nullptr)
  {
    for (int i = 0; i < number_of_woods; ++i)
    {
      if (wood_obstacle->isVisible())
      {
        window.draw(*wood_obstacle[i].getSprite());
      }
    }
  }
}

// ---------------------------------- PRIVATE ----------------------------------

sf::Vector2f LevelManager::getLvl1PigCoords(int pig_index, sf::RenderWindow& window)
{
  sf::Vector2f coordinates;
  coordinates.x = window.getSize().x * 0.65 + pig_index * 150;
  coordinates.y = window.getSize().y * 0.75;
  return coordinates;
}

sf::Vector2f LevelManager::getLvl2PigCoords(int pig_index, sf::RenderWindow& window)
{
  sf::Vector2f coordinates;
  coordinates.x = window.getSize().x * 0.9;
  coordinates.y = window.getSize().y * 0.25 * (pig_index + 1);
  return coordinates;
}

sf::Vector2f LevelManager::getLvl3PigCoords(int pig_index, sf::RenderWindow& window)
{
  sf::Vector2f coordinates;
  coordinates.x = window.getSize().x * 0.65 + pig_index * 150;
  coordinates.y = 0.0017 * pow(coordinates.x - window.getSize().x/2,2);
  return coordinates;
}

void LevelManager::loadTexture(sf::Texture& texture, std::string path)
{
  if(!texture.loadFromFile(path))
  {
    std::cout << path <<" texture didn't load\n";
  }
}