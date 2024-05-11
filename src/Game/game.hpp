#pragma once

#include <Spaceship/spaceship.hpp>

class Game {
 public:
  Game();
  ~Game();
  void Draw(sf::RenderWindow& window);
  void Update();
  void InputHandle();
 private:
  Spaceship spaceship;
};
