#pragma once

#include <SFML/Graphics.hpp>

class Block {
 public:
  Block(sf::Vector2f pos);

  void Draw(sf::RenderWindow& window);
  sf::FloatRect GetHitbox() const;

 private:
  sf::Vector2f position;
};
