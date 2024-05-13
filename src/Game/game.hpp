#pragma once

#include <Barrier/barrier.hpp>
#include <Invador/invador.hpp>
#include <RandomInvador/randominvador.hpp>
#include <Spaceship/spaceship.hpp>

class Game {
 public:
  Game();
  ~Game();
  void Draw(sf::RenderWindow& window);
  void Update();
  void InputHandle();

  std::vector<Barrier> CreateBarriers();
  std::vector<Invador> CreateInvadors();

 private:
  Spaceship spaceship;

  std::vector<Laser> invadorsLasers;
  std::vector<Invador> invadors;
  float invadorsShootDelay = 3.5f;
  int invadorsDirection;

  RandomInvador randomInvador;
  float randomInvadorsDelay = 1.0f;

  std::vector<Barrier> barriers;

  void MoveInvadors();
  void MoveInvadorsDown(int dist);
  void DeleteInactiveLasers();
  void InvadorShootLaser();
};
