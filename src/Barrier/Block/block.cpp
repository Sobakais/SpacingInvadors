#include "block.hpp"

Block::Block(sf::Vector2f pos) { position = pos; }

void Block::Draw(sf::RenderWindow& window) {
  sf::RectangleShape rect;
  rect.setSize({3, 3});
  rect.setPosition(position);
  rect.setFillColor(sf::Color(13, 0, 203, 255));
  window.draw(rect);
}
