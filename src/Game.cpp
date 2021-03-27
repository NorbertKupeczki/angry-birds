#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
//  srand(time(NULL));
  game_state = MAIN_MENU;
  game_paused = false;
  level_set = false;
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
  initSounds();
  setButtonPosition();

  bird_spr.setOrigin(bird_tex.getSize().x/2, bird_tex.getSize().y/2);
  bird_spr.setPosition(slingshot.getLaunchPos());

  return true;
}

void Game::update(float dt)
{
  updateMenus();
  updateInGame(dt);
}

void Game::render()
{
  window.draw(background_spr);

  if (game_state == MAIN_MENU)
  {
    if (!options.isOptionsActive())
    {
      drawButtons();
    }
    else if (options.isOptionsActive())
    {
      options.renderOptions(window);
    }
  }
  else if (game_state == IN_GAME)
  {
    window.draw(*slingshot.getSprite());
    window.draw(bird_spr);
    window.draw(*slingshot.getSpriteLeft());
    level_manager.renderObstacles(window);
    drawPigs();
    if (grabbed || launched)
    {
      slingshot.drawTrajectory(window);
    }
    if (game_paused)
    {
      window.draw(pause_spr);
    }
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
    if (game_state == MAIN_MENU &&
        !options.isOptionsActive())
    {
      if (play_button.activeBtn())
      {
        game_state = IN_GAME;
        play_button.click();
      }
      else if (options_button.activeBtn())
      {
        options_button.click();
        options.enterOptionsMenu();
      }
      else if (help_button.activeBtn())
      {
        help_button.click();
      }
      else if (quit_button.activeBtn())
      {
        quit_button.click();
        window.close();
      }
    }
    else if (game_state == MAIN_MENU &&
             options.isOptionsActive())
    {
      options.mouseClicked(event);
    }
    else if (game_state == IN_GAME)
    {
      sf::Vector2i click = sf::Mouse::getPosition(window);
      if (bird_spr.getGlobalBounds().contains(click.x, click.y) && !launched)
      {
        grabbed = true;
      }
    }
    else if (game_state == GAME_WON ||
             game_state == GAME_LOST)
    {
      if (quit_button.activeBtn())
      {
        quit_button.click();
        window.close();
      }
      else if (menu_button.activeBtn())
      {
        menu_button.click();
        resetGame();
      }
    }
  }
}

void Game::mouseReleased(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left &&
      game_state == IN_GAME)
  {
    if (!options.isOptionsActive())
    {
      if (grabbed)
      {
        grabbed = false;
        slingshot.launch();
        launchBird();
      }
    }
  }
  else if (event.mouseButton.button == sf::Mouse::Left &&
           options.isOptionsActive())
  {
    options.mouseReleased(event);
  }
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

  if (game_state == IN_GAME)
    if (event.key.code == sf::Keyboard::P)
    {
      game_paused = !game_paused;
    }
    else if (event.key.code == sf::Keyboard::B &&
             game_paused)
    {
      game_paused = false;
      resetGame();
    }
}

//---------------------------------- PRIVATE ----------------------------------

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

void Game::loadSound(sf::SoundBuffer& buffer, std::string path)
{
  if(!buffer.loadFromFile(path))
  {
    std::cout << path <<" sound failed to load\n";
  }
}

void Game::initTextures()
{
  loadTexture(background_spr, background_tex, "Data/Images/Backgrounds/menu.jpg");
  loadTexture(pause_spr, pause_tex, "Data/Images/Backgrounds/pause_menu.png");
  loadTexture(lvl1_tex, "Data/Images/Backgrounds/lvl1.png");
  loadTexture(lvl2_tex, "Data/Images/Backgrounds/lvl2.png");
  loadTexture(lvl3_tex, "Data/Images/Backgrounds/lvl3.png");
  loadTexture(game_won_tex, "Data/Images/Backgrounds/game_won.png");
  loadTexture(sling_full_tex, "Data/Images/Objects/slingshot_full.png");
  loadTexture(sling_left_tex, "Data/Images/Objects/slingshot_leftbranch.png");
  loadTexture(bird_spr, bird_tex, "Data/Images/Objects/parrot.png");
  loadTexture(pig_tex, "Data/Images/Objects/pig.png");

  pause_spr.setOrigin(pause_tex.getSize().x / 2, pause_tex.getSize().y / 2);
  pause_spr.setPosition(window.getSize().x / 2, window.getSize().y / 2);

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

void Game::initSounds()
{
  loadSound(menu_hover_bfr, "Data/Audio/menu_hover.ogg");
  loadSound(menu_click_bfr, "Data/Audio/menu_click.ogg");
  loadSound(slingshot_launch, "Data/Audio/slingshot_launch.ogg");
  loadSound(pig_squeek, "Data/Audio/pig_squeek.ogg");

  play_button.setSounds(menu_hover_bfr, menu_click_bfr);
  options_button.setSounds(menu_hover_bfr, menu_click_bfr);
  menu_button.setSounds(menu_hover_bfr, menu_click_bfr);
  help_button.setSounds(menu_hover_bfr, menu_click_bfr);
  quit_button.setSounds(menu_hover_bfr, menu_click_bfr);

  options.initButtons(menu_hover_bfr, menu_click_bfr, window);

  slingshot.setSound(slingshot_launch);
  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    pigs[i].setSound(pig_squeek);
  }
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
  else if (game_state == GAME_WON ||
           game_state == GAME_LOST)
  {
    menu_button.setPosition(window.getSize().x * 0.4,
                            window.getSize().y * 0.85);
    quit_button.setPosition(window.getSize().x * 0.6,
                            window.getSize().y * 0.85);
  }
}

void Game::initLevel(int level)
{
  background_spr.setTexture(
  level_manager.levelTexture(level, lvl1_tex, lvl2_tex, lvl3_tex));
  level_manager.createObstacles(level, window);

  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    pigs[i].setTexture(pig_tex);
    pigs[i].getSprite()->setPosition(
      level_manager.getPigCoords(level,i,window));
  }
}

void Game::updateMenus()
{
  if (game_state == MAIN_MENU ||
      game_state == GAME_WON ||
      game_state == GAME_LOST)
  {
    if (!options.isOptionsActive())
    {
      checkButtons(sf::Mouse::getPosition(window));
    }
    else if (options.isOptionsActive())
    {
      options.checkButtons(sf::Mouse::getPosition(window));
      if (options.isSliderGrabbed())
      {
        options.moveSlider(window);
      }
    }
  }
}

void Game::updateInGame(float dt)
{
  if (game_state == IN_GAME && !game_paused)
  {
    if (!level_set)
    {
      initLevel(options.levelSelected());
      level_set = true;
    }
    moveBird(dt, slingshot.getLaunchPos());

    if (bird_spr.getPosition().x - bird_spr.getGlobalBounds().width/2 > window.getSize().x ||
        bird_spr.getPosition().y - bird_spr.getGlobalBounds().height/2 > window.getSize().y)
    {
      bird_spr.setPosition(slingshot.getLaunchPos());
      launched = false;
    }

    collisionCheck();
    checkEndOfGameConditions();
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
    float x_dist = start_pos.x - bird_spr.getPosition().x;
    float y_dist = start_pos.y - bird_spr.getPosition().y;
    Vector2 vect = {x_dist, y_dist};
    vect.normalise();
    vect = vect * MAX_DIST;
    if (dist > MAX_DIST)
    {
      bird_spr.setPosition(start_pos.x - vect.x, start_pos.y - vect.y);
    }
    if (bird_spr.getPosition().x > start_pos.x)
    {
      bird_spr.setPosition(start_pos.x, bird_spr.getPosition().y);
    }
    if (bird_spr.getPosition().y < start_pos.y)
    {
      bird_spr.setPosition(bird_spr.getPosition().x, start_pos.y);
    }
    slingshot.trajectory(bird_spr.getPosition(), GRAVITY);
  }
  else if (launched)
  {
    bird_spr.setPosition(bird_vector.x * speed * elapsed_time + bird_start.x,
                         bird_vector.y * speed * elapsed_time + 60 * pow(elapsed_time,2) +bird_start.y);
    elapsed_time += dt;
  }
}

void Game::launchBird()
{
  speed = getDistance(bird_spr.getPosition(), slingshot.getLaunchPos()) * 6;
  bird_vector.x = slingshot.getLaunchPos().x - bird_spr.getPosition().x;
  bird_vector.y = slingshot.getLaunchPos().y - bird_spr.getPosition().y;
  bird_vector.normalise();
  bird_start = {bird_spr.getPosition().x, bird_spr.getPosition().y};
  launched = true;
  elapsed_time = 0;
}

void Game::collisionCheck()
{
  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    if (getDistance(bird_spr.getPosition(),pigs[i].getSprite()->getPosition()) <= 40.0 && pigs[i].isVisible())
    {
      pigs[i].setVisibility(false);
      pigs[i].squeek();
      bird_spr.setPosition(slingshot.getLaunchPos());
      launched = false;
      pigs_left -= 1;
    }
    if (level_manager.collisionCheck(bird_spr))
    {
      bird_spr.setPosition(slingshot.getLaunchPos());
      launched = false;
    }
  }
}

void Game::checkEndOfGameConditions()
{
  if (pigs_left <= 0)
  {
    game_state = GAME_WON;
    background_spr.setTexture(game_won_tex);
    setButtonPosition();
  }
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
  grabbed = false;
  launched = false;
  level_set = false;
  setButtonPosition();
  bird_spr.setPosition(slingshot.getLaunchPos());
  background_spr.setTexture(background_tex);
  level_manager.deleteObstacles();
  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    pigs[i].setVisibility(true);
  }
}