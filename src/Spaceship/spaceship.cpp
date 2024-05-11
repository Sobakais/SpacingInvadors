#include <config.hpp>
#include <stdexcept>

#include "spaceship.hpp"

Spaceship::Spaceship() {
  if (!texture.loadFromFile(PROJECT_DIR "/src/media/spaceship.png")) {
    throw std::runtime_error("Spaceship texture not found");
  }
  sprite.setTexture(texture);
  sprite.scale(0.2f, 0.2f);
  position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
  sprite.setPosition(position);
}
Spaceship::~Spaceship() {
  // As far as I can tell, Sprite destructor will clean up its texture
}

void Spaceship::Draw(sf::RenderWindow& window) {
  sprite.setPosition(position);
  window.draw(sprite);
}

void Spaceship::Fire() {}

void Spaceship::MoveLeft() {
  position.x -= 5;
  if (position.x < 0) {
    position.x = 0;
  }
}

void Spaceship::MoveRight() {
  position.x += 5;
  if (position.x + sprite.getLocalBounds().width > WINDOW_WIDTH) {
    position.x = WINDOW_WIDTH - sprite.getLocalBounds().width;
  }
}
