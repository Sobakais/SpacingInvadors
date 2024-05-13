#pragma once

#include <SFML/Graphics.hpp>

class Block {
 public:
  Block(sf::Vector2f pos);

  void Draw(sf::RenderWindow& window);

 private:
  sf::Vector2f position;
};
