
#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
  game_state = MAIN_MENU;
}

Game::~Game()
{

}

bool Game::init()
{
  initTextures();
  sling_left_spr.setPosition(200, 420);
  sling_full_spr.setPosition(200, 420);
  bird_spr.setOrigin(bird_tex.getSize().x/2, bird_tex.getSize().y/2);
  bird_spr.setPosition(start_pos);
  return true;
}

void Game::update(float dt)
{
  if (grabbed)
  {
    bird_spr.setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);

    float dist = getDistance(bird_spr.getPosition(), start_pos);
    if (dist > MAX_DIST)
    {
      float x_dist = start_pos.x - bird_spr.getPosition().x;
      float y_dist = start_pos.y - bird_spr.getPosition().y;
      Vector2 placement = {x_dist, y_dist};
      placement.normalise();
      placement = placement * MAX_DIST;
      bird_spr.setPosition(start_pos.x - placement.x, start_pos.y - placement.y);
    }
  }
  else if (launched)
  {
    bird_spr.move(bird_vector.x * speed *dt, bird_vector.y * speed *dt);
    bird_vector.y += gravity;
  }

}

void Game::render()
{
  window.draw(background_spr);

  if (game_state == MAIN_MENU)
  {
    //render menu items;
  }
  else if (game_state == IN_GAME)
  {
    window.draw(sling_full_spr);
    window.draw(bird_spr);
    window.draw(sling_left_spr);
  }
  else if (game_state == GAME_WON)
  {
    //game over screen, player won
  }
  else if (game_state == GAME_LOST)
  {
    //game over screen, player lost
  }

}

void Game::mouseClicked(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    sf::Vector2i click = sf::Mouse::getPosition(window);
    if (bird_spr.getGlobalBounds().contains(click.x, click.y))
    {
      std::cout << "Bird clicked\n";
      grabbed = true;
    }
  }
  //get the click position

}

void Game::mouseReleased(sf::Event event)
{
//  sf::Vector2i click = sf::Mouse::getPosition(window);
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    if (grabbed)
    {
      grabbed = false;
      launchBird();
    }
  }
}

void Game::keyPressed(sf::Event event)
{
  std::cout << "Key pressed\n";
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

  if (game_state == MAIN_MENU)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      std::cout << "Entering game";
      game_state = IN_GAME;
      background_spr.setTexture(lvl1_tex);
    }
  }
}

void Game::loadTexture(sf::Sprite& sprite, sf::Texture& texture, std::string path)
{
  if(!texture.loadFromFile(path))
  {
    std::cout << path <<" texture didn't load\n";
  }
  sprite.setTexture(texture);
}

void Game::loadTexture(sf::Texture& texture, std::string path)
{
  if(!texture.loadFromFile(path))
  {
    std::cout << path <<" texture didn't load\n";
  }
}

void Game::initTextures()
{
  loadTexture(background_spr, background_tex, "Data/Images/Backgrounds/menu.jpg");
  loadTexture(lvl1_tex, "Data/Images/Backgrounds/lvl1.png");
  loadTexture(lvl2_tex, "Data/Images/Backgrounds/lvl2.png");
  loadTexture(lvl3_tex, "Data/Images/Backgrounds/lvl3.png");
  loadTexture(sling_full_spr, sling_full_tex, "Data/Images/Objects/slingshot_full.png");
  loadTexture(sling_left_spr, sling_left_tex, "Data/Images/Objects/slingshot_leftbranch.png");
  loadTexture(bird_spr, bird_tex, "Data/Images/Objects/parrot.png");
}

float Game::getDistance(sf::Vector2<float> vector1,
                        sf::Vector2<float> vector2)
{
  float x = vector1.x - vector2.x;
  float y = vector1.y - vector2.y;
  float distance = sqrt(pow(x,2) + pow(y,2));
  return distance;
}

void Game::launchBird()
{
  speed = getDistance(bird_spr.getPosition(), start_pos) * 4;
  bird_vector.x = start_pos.x - bird_spr.getPosition().x;
  bird_vector.y = start_pos.y - bird_spr.getPosition().y;
  bird_vector.normalise();
  launched = true;
}