#include "game.hpp"

Game::Game() {}
Game::~Game() {}

void Game::Draw(sf::RenderWindow& window) { spaceship.Draw(window); }

void Game::Update() {}

void Game::InputHandle() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    spaceship.MoveLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    spaceship.MoveRight();
  }
}
