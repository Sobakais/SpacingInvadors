#include <config.hpp>

#include "spaceship.hpp"

Spaceship::Spaceship() {
  for (int i = 0; i < 21; i++) {
        sf::Texture texture;
        texture.loadFromFile(PROJECT_DIR "/src/media/animation_Spaceship/sprite_" + std::to_string(i) + ".png");
        animation.push_back(texture);
  }
  sprite.setTexture(animation[frame]);
  position = {(WINDOW_WIDTH - sprite.getLocalBounds().width) / 2,(WINDOW_HEIGHT - sprite.getLocalBounds().height)};
  sprite.setPosition(position);
  lasers = {};
}

Spaceship::~Spaceship() {
  // As far as I can tell, Sprite destructor will clean up its texture
}

void Spaceship::Draw(sf::RenderWindow& window) {
  time = time > 20.2f ? 0.f : time + 0.1f;
  frame = (int)time;
  sprite.setTexture(animation[frame]);
  sprite.setPosition(position);
  window.draw(sprite);
}

void Spaceship::Fire() {
  lasers.push_back(Laser(position, 5, sf::Color({153, 0, 189, 255})));
}

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
