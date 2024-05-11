#pragma once
#include <SFML/Graphics.hpp>
#include <Laser/laser.hpp>
#include <vector>


class Spaceship {
 public:
  Spaceship();
  ~Spaceship();
  void Draw(sf::RenderWindow& window);
  void Fire();
  void MoveLeft();
  void MoveRight();

  std::vector<Laser> lasers;
 private:
  sf::Sprite sprite;
  std::vector<sf::Texture> animation;
  sf::Vector2f position;
  size_t frame = 0;
  float time = 0.f;
};
