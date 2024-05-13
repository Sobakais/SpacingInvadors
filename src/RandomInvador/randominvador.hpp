#pragma once
#include <SFML/Graphics.hpp>

class RandomInvador {
 public:
  RandomInvador();

  void Spawn();
  void Update();
  void Draw(sf::RenderWindow& window);

  bool isAlive;

 private:
  std::vector<sf::Texture> texture;
  sf::Sprite sprite;
  int velocity;
};
