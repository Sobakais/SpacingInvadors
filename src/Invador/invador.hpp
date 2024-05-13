#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Invador {
 public:
  Invador(sf::Vector2f position, int type);

  void Draw(sf::RenderWindow& window);
  void Update();
  
  int type;
  sf::Vector2f position;
  sf::Sprite sprite;
  static std::vector<std::vector<sf::Texture>> allInvadorAnimations;
  std::vector<sf::Texture> animation;

 private:
  size_t frame = 0;
  float time = 0.f;
};
