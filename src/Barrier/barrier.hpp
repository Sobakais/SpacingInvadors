#pragma once

#include <Barrier/Block/block.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Barrier {
 public:
  Barrier(sf::Vector2f position);

  void Draw(sf::RenderWindow& window);

  std::vector<Block> blocks;
  std::vector<std::vector<int>> grid;

 private:
  sf::Vector2f position;
};
