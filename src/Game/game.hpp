#pragma once

#include <Spaceship/spaceship.hpp>
#include <Barrier/barrier.hpp>
#include <Invador/invador.hpp>

class Game {
 public:
  Game();
  ~Game();
  void Draw(sf::RenderWindow& window);
  void Update();
  void InputHandle();
  void DeleteInactiveShipLasers();
  std::vector<Barrier> CreateBarriers();
  std::vector<Invador> CreateInvadors();

 private:
  Spaceship spaceship;
  std::vector<Invador> invadors;
  std::vector<Barrier> barriers;
};
