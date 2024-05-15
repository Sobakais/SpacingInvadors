#pragma once
#include <Laser/laser.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

class Spaceship {
 public:
  Spaceship();
  ~Spaceship();

  void Draw(sf::RenderWindow& window);
  void Update();
  void Fire();
  void MoveLeft();
  void MoveRight();

  void Reset();

  std::vector<Laser> lasers;

  sf::FloatRect GetHitbox() const;

 private:
  sf::Sprite sprite;
  std::vector<sf::Texture> animation;
  sf::Vector2f position;
  size_t frame = 0;
  float time = 0.f;
  float delay_to_shoot = 0.f;
};
