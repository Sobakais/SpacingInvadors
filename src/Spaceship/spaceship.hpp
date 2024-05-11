#pragma once
#include <SFML/Graphics.hpp>


class Spaceship {
 public:
  Spaceship();
  ~Spaceship();
  void Draw(sf::RenderWindow& window);
  void Fire();
  void MoveLeft();
  void MoveRight();

 private:
  sf::Sprite sprite, bulletSprite;
  sf::Texture texture, bulletTexture;
  sf::Vector2f position;
};
