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
  if (metal_obstacle != nullptr)
  {
    delete[] metal_obstacle;
  }
  if (stone_obstacle != nullptr)
  {
    delete[] stone_obstacle;
  }
  if (wood_obstacle != nullptr)
  {
    delete[] wood_obstacle;
  }
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
    metal_obstacle = new MetalObstacle[4];
    for (int i = 0; i < 4; ++i)
    {
      metal_obstacle[i].setTexture(metal_tex);
      metal_obstacle[i].getSprite()->setOrigin(metal_tex.getSize().x / 2,
                                               metal_tex.getSize().y /2);
      metal_obstacle[i].getSprite()->setPosition(
        window.getSize().x * 0.64 + i * metal_tex.getSize().x,
        window.getSize().y * 0.805);
    }
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
}

void LevelManager::renderObstacles(sf::RenderWindow& window)
{
  if (metal_obstacle != nullptr)
  {
    for (int i = 0; i < 4; ++i)
    {
      window.draw(*metal_obstacle[i].getSprite());
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
  coordinates.y = window.getSize().y * 0.2 * (pig_index + 1);
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