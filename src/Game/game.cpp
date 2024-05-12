#include "game.hpp"
#include <iostream>

Game::Game() {}
Game::~Game() {}

void Game::Draw(sf::RenderWindow& window) { 
  for (auto& laser : spaceship.lasers) {
    laser.Draw(window);
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    spaceship.MoveLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    spaceship.MoveRight();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    spaceship.Fire();
  }
}

void Game::DeleteInactiveShipLasers() {
    std::cout << spaceship.lasers.size() << std::endl;
    spaceship.lasers.erase(std::remove_if(spaceship.lasers.begin(), spaceship.lasers.end(),
    [](const Laser& laser) { return !laser.active; }), spaceship.lasers.end());
}
