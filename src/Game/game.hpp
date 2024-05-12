#pragma once

#include <Spaceship/spaceship.hpp>
#include <Barrier/barrier.hpp>

class Game {
 public:
  Game();
  ~Game();
  void Draw(sf::RenderWindow& window);
  void Update();
  void InputHandle();
  void DeleteInactiveShipLasers();
  std::vector<Barrier> CreateBarriers();

 private:
  Spaceship spaceship;
  std::vector<Barrier> barriers;
};
