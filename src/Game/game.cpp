#include <config.hpp>

#include "game.hpp"

Game::Game() {
  barriers = CreateBarriers(); 
  invadors = CreateInvadors();
}

Game::~Game() {}

void Game::Draw(sf::RenderWindow& window) {
  for (auto& laser : spaceship.lasers) {
    laser.Draw(window);
  }
  for (auto& barrier : barriers) {
    barrier.Draw(window);
  }
  for (auto& invador : invadors) {
    invador.Draw(window);
  }
  spaceship.Draw(window);
}

void Game::Update() {
  spaceship.Update();
  DeleteInactiveShipLasers();
  for (auto& laser : spaceship.lasers) {
    laser.Update();
  }
  for (auto& invador : invadors) {
    invador.Update();
  }
}

void Game::InputHandle() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
      !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    spaceship.MoveLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
             !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    spaceship.MoveRight();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    spaceship.Fire();
  }
}

void Game::DeleteInactiveShipLasers() {
  for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
    if (!it->active) {
      spaceship.lasers.erase(it);
    } else {
      ++it;
    }
  }
}

std::vector<Barrier> Game::CreateBarriers() {
  int barrierWidth = 25 * 3;
  float gap = (WINDOW_WIDTH - barrierWidth * 4) / 5;
  for (int i = 0; i < 4; i++) {
    float x = gap * (i + 1) + i * barrierWidth;
    barriers.push_back(Barrier(sf::Vector2f(x, WINDOW_HEIGHT - 100)));
  }
  return barriers;
}

std::vector<Invador> Game::CreateInvadors() {
  int gap = 15;
  //Enemies field is 11 x 5
  //Invador sptite is 35 x 30
  float beginX = (WINDOW_WIDTH - ((35 * 11) + (gap * 10))) / 2;
  float beginY = 50;
  for (int row = 0; row < 5; row++) {
    int Type = row % 3;
    for (int col = 0; col < 11; col++) {
      int x = beginX + (col * (gap + 35)); 
      int y = beginY + (row * (gap + 30));
      invadors.push_back(Invador(sf::Vector2f(x, y), Type));
    }
  }
  return invadors;
}
