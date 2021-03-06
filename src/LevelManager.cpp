#include "LevelManager.h"
#include <cmath>
#include <iostream>

LevelManager::LevelManager()
{
  loadTexture(wood_tex, "Data/Images/Obstacles/obst_wood.png");
  loadTexture(stone_tex, "Data/Images/Obstacles/obst_stone.png");
  loadTexture(metal_tex, "Data/Images/Obstacles/obst_metal.png");
  loadTexture(boulder_tex, "Data/Images/Obstacles/rock.png");

  boulder.setTexture(boulder_tex);
  boulder.setVisibility(false);
  boulder.getSprite()->setPosition(1110.0,15.0);
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

    boulder.setVisibility(true);
    boulder.getSprite()->setPosition(1110.0,15.0);

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
    wood_obstacle[0].getSprite()->setScale(1.55,1.0);
    wood_obstacle[0].getSprite()->setPosition(
      window.getSize().x * 0.94 - wood_tex.getSize().x + wood_tex.getSize().y * 0.5,
      window.getSize().y * 0.25 - wood_tex.getSize().x + wood_tex.getSize().y);
  }
  else if (level == 3)
  {
    number_of_metals = 6;
    number_of_stones = 5;
    number_of_woods = 2;

    boulder.setVisibility(true);
    boulder.getSprite()->setPosition(1110.0,15.0);

    metal_obstacle = new MetalObstacle[number_of_metals];
    stone_obstacle = new StoneObstacle[number_of_stones];
    wood_obstacle = new WoodObstacle[number_of_woods];

    for (int i = 0; i < number_of_metals; ++i)
    {
      metal_obstacle[i].setTexture(metal_tex);
      metal_obstacle[i].getSprite()->setOrigin(metal_tex.getSize().x / 2,
                                               metal_tex.getSize().y /2);

      metal_obstacle[0].getSprite()->setPosition(
        window.getSize().x * 0.88,
        window.getSize().y * 0.63);
      metal_obstacle[1].getSprite()->setPosition(
        window.getSize().x * 0.823,
        window.getSize().y * 0.58);
      metal_obstacle[1].getSprite()->setRotation(90.0);
      metal_obstacle[2].getSprite()->setPosition(
        window.getSize().x * 0.823,
        window.getSize().y * 0.38);
      metal_obstacle[2].getSprite()->setRotation(90.0);
      metal_obstacle[3].getSprite()->setPosition(
        window.getSize().x * 0.78,
        window.getSize().y * 0.33);
      metal_obstacle[3].getSprite()->setScale(0.65,1.0);
      metal_obstacle[4].getSprite()->setPosition(
        window.getSize().x * 0.675,
        window.getSize().y * 0.145);
      metal_obstacle[4].getSprite()->setScale(0.6,1.0);
      metal_obstacle[5].getSprite()->setPosition(
        window.getSize().x * 0.716,
        window.getSize().y * 0.086);
      metal_obstacle[5].getSprite()->setScale(1.1,1.0);
      metal_obstacle[5].getSprite()->setRotation(90.0);
    }

    for (int i = 0; i < number_of_stones; ++i)
    {
      stone_obstacle[i].setTexture(stone_tex);
      stone_obstacle[i].getSprite()->setOrigin(stone_tex.getSize().x / 2,
                                               stone_tex.getSize().y /2);
      stone_obstacle[i].getSprite()->setPosition(1200.0,55 + i * stone_tex.getSize().x);
      stone_obstacle[i].getSprite()->setRotation(90.0);
    }

    for (int i = 0; i < number_of_woods; ++i)
    {
      wood_obstacle[i].setTexture(wood_tex);
      wood_obstacle[i].getSprite()->setOrigin(wood_tex.getSize().x / 2,
                                              wood_tex.getSize().y /2);
      wood_obstacle[i].getSprite()->setScale(1.55,1.0);
      wood_obstacle[i].getSprite()->setPosition(
        window.getSize().x * 0.857,
        window.getSize().y * 0.15 + i * 237.0);
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

  boulder.setVisibility(false);
  boulder.resetSpeed();

  number_of_metals = 0;
  number_of_stones = 0;
  number_of_woods = 0;
}

bool LevelManager::collisionCheck(sf::Sprite& bird, bool destruction)
{
  bool collision;

  collision = checkObstacles(metal_obstacle, bird, number_of_metals, destruction) ||
              checkObstacles(stone_obstacle, bird, number_of_stones, destruction) ||
              checkObstacles(wood_obstacle, bird, number_of_woods, destruction);

  return collision;
}

bool LevelManager::checkObstacles(Obstacles* obstacles,
                                  sf::Sprite& bird,
                                  int array_size,
                                  bool destruction)
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
        if (obstacles[i].isDestructible() && destruction)
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
  if (boulder.isVisible())
  {
    window.draw(*boulder.getSprite());
  }

  if (metal_obstacle != nullptr)
  {
    for (int i = 0; i < number_of_metals; ++i)
    {
      if (metal_obstacle[i].isVisible())
      {
        window.draw(*metal_obstacle[i].getSprite());
      }
    }
  }
  if (stone_obstacle != nullptr)
  {
    for (int i = 0; i < number_of_stones; ++i)
    {
      if (stone_obstacle[i].isVisible())
      {
        window.draw(*stone_obstacle[i].getSprite());
      }
    }
  }
  if (wood_obstacle != nullptr)
  {
    for (int i = 0; i < number_of_woods; ++i)
    {
      if (wood_obstacle[i].isVisible())
      {
        window.draw(*wood_obstacle[i].getSprite());
      }
    }
  }
}

sf::Sprite* LevelManager::getBoulder()
{
    return boulder.getSprite();
}

void LevelManager::moveBoulder(float dt)
{
  boulder.MoveBoulder(dt);
}

void LevelManager::resetBoulderSpeed()
{
  boulder.resetSpeed();
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