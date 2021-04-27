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
  help_open = false;
  pigs = new Pig[NUMBER_OF_PIGS];
  lives = new Birds[slingshot.MAX_LIVES];
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
  initFont();
  setButtonPosition();

  bird.getSprite()->setOrigin(bird_tex.getSize().x/2, bird_tex.getSize().y/2);
  bird.getSprite()->setPosition(slingshot.getLaunchPos());

  for (int i = 0; i < slingshot.MAX_LIVES;++i)
  {
    lives[i].setTexture(bird_tex);
    lives[i].getSprite()->setPosition(10.0 + i * bird_tex.getSize().y * 1.1,
                                      window.getSize().y - bird_tex.getSize().y * 1.5);
  }

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
      if (!help_open)
      {
        drawButtons();
      }
      else if (help_open)
      {
        window.draw(help_menu_spr);
      }
    }
    else if (options.isOptionsActive())
    {
      options.renderOptions(window);
    }
  }
  else if (game_state == IN_GAME)
  {
    window.draw(*slingshot.getSprite());
    window.draw(*bird.getSprite());
    window.draw(*slingshot.getSpriteLeft());
    level_manager.renderObstacles(window);
    drawLives(slingshot.getLives());
    drawPigs();
    if (bird.isGrabbed() || bird.isLaunched())
    {
      slingshot.drawTrajectory(window);
    }
    if (game_paused)
    {
      window.draw(pause_spr);
    }
    window.draw(score_text);
  }
  else if (game_state == GAME_WON)
  {
    drawButtons();
    window.draw(score_endlevel);
  }
  else if (game_state == GAME_LOST)
  {
    drawButtons();
    window.draw(score_endlevel);
  }
}

void Game::mouseClicked(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    if (game_state == MAIN_MENU &&
        !options.isOptionsActive())
    {
      if (!help_open)
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
          help_open = true;
        }
        else if (quit_button.activeBtn())
        {
          quit_button.click();
          window.close();
        }
      }
      else if (help_open)
      {
        help_open = false;
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
      if (bird.getSprite()->getGlobalBounds().contains(click.x, click.y) && !bird.isLaunched())
      {
        bird.setGrabbed(true);
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
      if (bird.isGrabbed())
      {
        bird.setGrabbed(false);
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
  loadTexture(help_menu_spr, help_menu_tex, "Data/Images/Backgrounds/help_menu.png");
  loadTexture(lvl1_tex, "Data/Images/Backgrounds/lvl1.png");
  loadTexture(lvl2_tex, "Data/Images/Backgrounds/lvl2.png");
  loadTexture(lvl3_tex, "Data/Images/Backgrounds/lvl3.png");
  loadTexture(game_won_tex, "Data/Images/Backgrounds/game_won.png");
  loadTexture(game_lost_tex, "Data/Images/Backgrounds/game_lost.png");
  loadTexture(sling_full_tex, "Data/Images/Objects/slingshot_full.png");
  loadTexture(sling_left_tex, "Data/Images/Objects/slingshot_leftbranch.png");
  loadTexture(bird_tex, "Data/Images/Objects/parrot.png");
  loadTexture(pig_tex, "Data/Images/Objects/pig.png");

  pause_spr.setOrigin(pause_tex.getSize().x / 2, pause_tex.getSize().y / 2);
  pause_spr.setPosition(window.getSize().x / 2, window.getSize().y / 2);

  help_menu_spr.setOrigin(help_menu_tex.getSize().x / 2, help_menu_tex.getSize().y / 2);
  help_menu_spr.setPosition(window.getSize().x / 2, window.getSize().y / 2);

  slingshot.setTexture(sling_full_tex, sling_left_tex);

  bird.setTexture(bird_tex);
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

void Game::initFont()
{
  if (!font.loadFromFile("Data/Fonts/angrybirds.ttf"))
  {
    std::cout << "font did not load \n";
  }

  score_text.setFont(font);
  score_text.setPosition(10.0, 10.0);
  score_text.setCharacterSize(35);
  score_text.setFillColor(sf::Color().White);
  score_text.setOutlineColor(sf::Color().Black);
  score_text.setOutlineThickness(2);
  score_text.setString("Score: " + std::to_string(slingshot.getScore()));

  score_endlevel.setFont(font);
  score_endlevel.setCharacterSize(70);
  score_endlevel.setFillColor(sf::Color().White);
  score_endlevel.setOutlineColor(sf::Color().Black);
  score_endlevel.setOutlineThickness(3);
  score_endlevel.setString(
    "Your score: " + std::to_string(slingshot.getScore()));
  score_endlevel.setPosition(
    window.getSize().x * 0.5 - score_endlevel.getGlobalBounds().width * 0.5,
    window.getSize().y * 0.55 - score_endlevel.getGlobalBounds().height * 0.5);
}

void Game::updateText()
{
  score_text.setString("Score: " + std::to_string(slingshot.getScore()));
  score_endlevel.setString(
    "Your score: " + std::to_string(slingshot.getScore()));
  score_endlevel.setPosition(
    window.getSize().x * 0.5 - score_endlevel.getGlobalBounds().width * 0.5,
    window.getSize().y * 0.55 - score_endlevel.getGlobalBounds().height * 0.5);
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

    if (!level_manager.collisionCheck(*level_manager.getBoulder(), false))
    {
      level_manager.moveBoulder(dt);
    }

    if (
      bird.getSprite()->getPosition().x -
          bird.getSprite()->getGlobalBounds().width / 2 > window.getSize().x ||
      bird.getSprite()->getPosition().y -
          bird.getSprite()->getGlobalBounds().height / 2 > window.getSize().y)
    {
      resetBird();
    }

    collisionCheck();
    updateText();
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
  if (bird.isGrabbed())
  {
    bird.getSprite()->setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);

    float dist = getDistance(bird.getSprite()->getPosition(), start_pos);
    float x_dist = start_pos.x - bird.getSprite()->getPosition().x;
    float y_dist = start_pos.y - bird.getSprite()->getPosition().y;
    Vector2 vect = {x_dist, y_dist};
    vect.normalise();
    vect = vect * MAX_DIST;
    if (dist > MAX_DIST)
    {
      bird.getSprite()->setPosition(start_pos.x - vect.x, start_pos.y - vect.y);
    }
    if (bird.getSprite()->getPosition().x > start_pos.x)
    {
      bird.getSprite()->setPosition(start_pos.x, bird.getSprite()->getPosition().y);
    }
    if (bird.getSprite()->getPosition().y < start_pos.y)
    {
      bird.getSprite()->setPosition(bird.getSprite()->getPosition().x, start_pos.y);
    }
    slingshot.trajectory(bird.getSprite()->getPosition(), GRAVITY);
  }
  else if (bird.isLaunched())
  {
    bird.getSprite()->setPosition(bird.getVector().x * bird.getSpeed() * elapsed_time + bird.getStart().x,
                                  bird.getVector().y * bird.getSpeed() * elapsed_time + 60 * pow(elapsed_time,2) +bird.getStart().y);
    elapsed_time += dt;
  }
}

void Game::launchBird()
{
  bird.setSpeed(getDistance(bird.getSprite()->getPosition(),
                                  slingshot.getLaunchPos()) * 6);
  bird.setVector({slingshot.getLaunchPos().x - bird.getSprite()->getPosition().x,
      slingshot.getLaunchPos().y - bird.getSprite()->getPosition().y });
  bird.normaliseVector();
  bird.setStart({ bird.getSprite()->getPosition().x, bird.getSprite()->getPosition().y });
  bird.setLaunched(true);
  elapsed_time = 0;
}

void Game::collisionCheck()
{
  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    if (
      getDistance(
        bird.getSprite()->getPosition(), pigs[i].getSprite()->getPosition()) <=
        40.0 && pigs[i].isVisible())
    {
      pigs[i].setVisibility(false);
      pigs[i].squeek();
      slingshot.addScore(pigs[i].getValue());
      resetBird();
      pigs_left -= 1;
    }
    if (
      level_manager.getBoulder()->getGlobalBounds().intersects(
        pigs[i].getSprite()->getGlobalBounds()) &&
      pigs[i].isVisible())
    {
      pigs[i].setVisibility(false);
      pigs[i].squeek();
      slingshot.addScore(pigs[i].getValue());
      pigs_left -= 1;
    }
    if (level_manager.collisionCheck(*bird.getSprite(), true))
    {
      resetBird();
    }
  }
}

void Game::checkEndOfGameConditions()
{
  if (pigs_left <= 0)
  {
    game_state = GAME_WON;
    background_spr.setTexture(game_won_tex);
    slingshot.addScore(slingshot.getLives() * 1000);
    updateText();
    setButtonPosition();
  }
  else if (slingshot.getLives() <= 0)
  {
    game_state = GAME_LOST;
    background_spr.setTexture(game_lost_tex);
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
  else if (game_state == GAME_WON ||
           game_state == GAME_LOST)
  {
    window.draw(*menu_button.getSprite());
    window.draw(*quit_button.getSprite());
  }
}

void Game::drawLives(int lives_left)
{
  if (lives_left > 1)
  {
    for (int i = 0; i < lives_left - 1; ++i)
    {
      window.draw(*lives[i].getSprite());
    }
  }
}

void Game::resetBird()
{
  bird.getSprite()->setPosition(slingshot.getLaunchPos());
  slingshot.loseLife();
  bird.setLaunched(false);
}

void Game::resetGame()
{
  pigs_left = NUMBER_OF_PIGS;
  game_state = MAIN_MENU;
  slingshot.setLives(slingshot.MAX_LIVES);
  slingshot.resetScore();
  updateText();
  bird.setGrabbed(false);
  bird.setLaunched(false);
  level_set = false;
  setButtonPosition();
  bird.getSprite()->setPosition(slingshot.getLaunchPos());
  background_spr.setTexture(background_tex);
  level_manager.deleteObstacles();
  for (int i = 0; i < NUMBER_OF_PIGS; ++i)
  {
    pigs[i].setVisibility(true);
  }
}