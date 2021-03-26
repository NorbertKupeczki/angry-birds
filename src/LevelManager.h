#ifndef ANGRYBIRDS_LEVELMANAGER_H
#define ANGRYBIRDS_LEVELMANAGER_H

#include <SFML/Graphics.hpp>
#include "Obstacles.h"

class LevelManager
{
 public:
  LevelManager();
  ~LevelManager();

  sf::Vector2f getPigCoords(int level,
                            int pig_index,
                            sf::RenderWindow& window);
  sf::Texture& levelTexture (int level,
                             sf::Texture& lvl1,
                             sf::Texture& lvl2,
                             sf::Texture& lvl3);

  void createObstacles(int level, sf::RenderWindow& window);
  void deleteObstacles();
  void renderObstacles(sf::RenderWindow& window);

 private:
  sf::Vector2f getLvl1PigCoords(int pig_index, sf::RenderWindow& window);
  sf::Vector2f getLvl2PigCoords(int pig_index, sf::RenderWindow& window);
  sf::Vector2f getLvl3PigCoords(int pig_index, sf::RenderWindow& window);

  void loadTexture(sf::Texture& texture, std::string path);

  MetalObstacle* metal_obstacle = nullptr;
  StoneObstacle* stone_obstacle = nullptr;
  WoodObstacle* wood_obstacle = nullptr;

  sf::Texture metal_tex;
  sf::Texture wood_tex;
  sf::Texture stone_tex;
};

#endif // ANGRYBIRDS_LEVELMANAGER_H
