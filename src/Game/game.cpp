#include "game.hpp"
#include <config.hpp>

Game::Game() {
  barriers = CreateBarriers();
}

Game::~Game() {}

void Game::Draw(sf::RenderWindow& window) {
  for (auto& laser : spaceship.lasers) {
    laser.Draw(window);
  }
  for (auto& barrier : barriers) {
    barrier.Draw(window);
  }
  spaceship.Draw(window);
}

void Game::Update() {
  spaceship.Update();
  DeleteInactiveShipLasers();
  for (auto& laser : spaceship.lasers) {
    laser.Update();
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
