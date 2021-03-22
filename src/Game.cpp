
#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
  game_state = MAIN_MENU;
  game_paused = false;
  pigs = new Pig[NUMBER_OF_PIGS];
  pigs_left = NUMBER_OF_PIGS;
}

Game::~Game()
{
  delete[] pigs;
}

bool Game::init()
{
  initTextures();
  initButtons();
  setButtonPosition();

  bird_spr.setOrigin(bird_tex.getSize().x/2, bird_tex.getSize().y/2);
  bird_spr.setPosition(slingshot.getLaunchPos());

  initPigs(1);
  return true;
}

void Game::update(float dt)
{
  if (game_state == MAIN_MENU ||
      game_state == GAME_WON)
  {
    checkButtons(sf::Mouse::getPosition(window));
  }
  else if (game_state == IN_GAME)
  {
    moveBird(dt, slingshot.getLaunchPos());
  }

  if (bird_spr.getPosition().x - bird_spr.getGlobalBounds().width/2 > window.getSize().x ||
      bird_spr.getPosition().y - bird_spr.getGlobalBounds().height/2 > window.getSize().y)
  {
    bird_spr.setPosition(slingshot.getLaunchPos());
    launched = false;
  }

  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    if (bird_spr.getGlobalBounds().intersects(pigs[i].getSprite()->getGlobalBounds()) &&
        pigs[i].isVisible())
    {
      pigs[i].setVisibility(false);
      bird_spr.setPosition(slingshot.getLaunchPos());
      launched = false;
      pigs_left -= 1;
    }
  }

  if (pigs_left <= 0)
  {
    game_state = GAME_WON;
    background_spr.setTexture(game_won_tex);
    setButtonPosition();
  }
}

void Game::render()
{
  window.draw(background_spr);

  if (game_state == MAIN_MENU)
  {
    drawButtons();
  }
  else if (game_state == IN_GAME)
  {
    window.draw(*slingshot.getSprite());
    window.draw(bird_spr);
    window.draw(*slingshot.getSpriteLeft());
    drawPigs();
  }
  else if (game_state == GAME_WON)
  {
    drawButtons();
  }
  else if (game_state == GAME_LOST)
  {
    drawButtons();
  }
}

void Game::mouseClicked(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    if (game_state == MAIN_MENU)
    {
      if (play_button.activeBtn())
      {
        game_state = IN_GAME;
        background_spr.setTexture(lvl1_tex);
      }
      else if (quit_button.activeBtn())
      {
        window.close();
      }
    }
    else if (game_state == IN_GAME)
    {
      sf::Vector2i click = sf::Mouse::getPosition(window);
      if (bird_spr.getGlobalBounds().contains(click.x, click.y))
      {
        grabbed = true;
      }
    }
    else if (game_state == GAME_WON)
    {
      if (quit_button.activeBtn())
      {
        window.close();
      }
      else if (menu_button.activeBtn())
      {
        resetGame();
      }
    }
    else if (game_state == GAME_LOST)
    {
      // Game lost menu mouse controls
    }
  }
}

void Game::mouseReleased(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left && game_state == IN_GAME)
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
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
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
  loadTexture(game_won_tex, "Data/Images/Backgrounds/game_won.png");
  loadTexture(sling_full_tex, "Data/Images/Objects/slingshot_full.png");
  loadTexture(sling_left_tex, "Data/Images/Objects/slingshot_leftbranch.png");
  loadTexture(bird_spr, bird_tex, "Data/Images/Objects/parrot.png");
  loadTexture(pig_tex, "Data/Images/Objects/pig.png");

  slingshot.setTexture(sling_full_tex, sling_left_tex);
}

void Game::initButtons()
{
  play_button.setTextures("Data/Images/Buttons/play_active.png",
                          "Data/Images/Buttons/play_inactive.png");
  options_button.setTextures("Data/Images/Buttons/options_active.png",
                          "Data/Images/Buttons/options_inactive.png");
  help_button.setTextures("Data/Images/Buttons/help_active.png",
                          "Data/Images/Buttons/help_inactive.png");
  menu_button.setTextures("Data/Images/Buttons/menu_active.png",
                          "Data/Images/Buttons/menu_inactive.png");
  quit_button.setTextures("Data/Images/Buttons/quit_active.png",
                          "Data/Images/Buttons/quit_inactive.png");
}

void Game::setButtonPosition()
{
  if (game_state == MAIN_MENU)
  {
    play_button.setPosition(window.getSize().x * 0.2,
                            window.getSize().y * 0.85);
    options_button.setPosition(window.getSize().x * 0.4,
                               window.getSize().y * 0.85);
    help_button.setPosition(window.getSize().x * 0.6,
                            window.getSize().y * 0.85);
    quit_button.setPosition(window.getSize().x * 0.8,
                            window.getSize().y * 0.85);
  }
  else if (game_state == GAME_WON)
  {
    menu_button.setPosition(window.getSize().x * 0.4,
                            window.getSize().y * 0.85);
    quit_button.setPosition(window.getSize().x * 0.6,
                            window.getSize().y * 0.85);
  }
}

void Game::initPigs(int level)
{
  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    pigs[i].setTexture(pig_tex);
    if (level == 1)
    {
      pigs[i].getSprite()->setPosition(
        window.getSize().x * 0.65 + i * 150,
        window.getSize().y * 0.75);
    }
  }
}

void Game::checkButtons(sf::Vector2i mouse_pos)
{
  play_button.mouseOver(mouse_pos);
  options_button.mouseOver(mouse_pos);
  help_button.mouseOver(mouse_pos);
  menu_button.mouseOver(mouse_pos);
  quit_button.mouseOver(mouse_pos);
}

float Game::getDistance(sf::Vector2<float> vector1,
                        sf::Vector2<float> vector2)
{
  float x = vector1.x - vector2.x;
  float y = vector1.y - vector2.y;
  float distance = sqrt(pow(x,2) + pow(y,2));
  return distance;
}

void Game::moveBird(float dt, sf::Vector2f start_pos)
{
  if (grabbed)
  {
    bird_spr.setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);

    float dist = getDistance(bird_spr.getPosition(), start_pos);
    if (dist > MAX_DIST)
    {
      float x_dist = start_pos.x - bird_spr.getPosition().x;
      float y_dist = start_pos.y - bird_spr.getPosition().y;
      Vector2 vect = {x_dist, y_dist};
      vect.normalise();
      vect = vect * MAX_DIST;
      bird_spr.setPosition(start_pos.x - vect.x, start_pos.y - vect.y);
    }
  }
  else if (launched)
  {
    bird_spr.move(bird_vector.x * speed *dt, bird_vector.y * speed *dt);
    bird_vector.y += gravity;
  }
}

void Game::launchBird()
{
  speed = getDistance(bird_spr.getPosition(), start_pos) * 4;
  bird_vector.x = start_pos.x - bird_spr.getPosition().x;
  bird_vector.y = start_pos.y - bird_spr.getPosition().y;
  bird_vector.normalise();
  launched = true;
}

void Game::drawPigs()
{
  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    if (pigs[i].isVisible())
    {
      window.draw(*pigs[i].getSprite());
    }
  }
}

void Game::drawButtons()
{
  if (game_state == MAIN_MENU)
  {
    window.draw(*play_button.getSprite());
    window.draw(*options_button.getSprite());
    window.draw(*help_button.getSprite());
    window.draw(*quit_button.getSprite());
  }
  else if (game_state == GAME_WON)
  {
    window.draw(*menu_button.getSprite());
    window.draw(*quit_button.getSprite());
  }
}

void Game::resetGame()
{
  pigs_left = NUMBER_OF_PIGS;
  game_state = MAIN_MENU;
  setButtonPosition();
  background_spr.setTexture(background_tex);
  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    pigs[i].setVisibility(true);
  }
}