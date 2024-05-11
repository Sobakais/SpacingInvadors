#include "game.hpp"

Game::Game() {}
Game::~Game() {}

void Game::Draw(sf::RenderWindow& window) { 
  for (auto& laser : spaceship.lasers) {
    laser.Draw(window);
  }
  spaceship.Draw(window); 
}

void Game::Update() {
  for (auto& laser : spaceship.lasers) {
    laser.Update();
  }
}

void Game::InputHandle() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    spaceship.MoveLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    spaceship.MoveRight();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    spaceship.Fire();
  }
}
