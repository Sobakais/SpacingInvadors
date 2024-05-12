#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Laser {
 public:
  Laser(sf::Vector2f position, int velocity, sf::Color color);
  ~Laser();

  void Draw(sf::RenderWindow& window);
  void Update();
  bool active;
  int velocity;

 private:
  sf::Sprite sprite;
  std::vector<sf::Texture> animation;
  sf::Vector2f position;
  size_t frame = 0;
  float time = 0.f;
};
