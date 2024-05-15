#include <SFML/Graphics/Rect.hpp>
#include <config.hpp>
#include <vector>

#include "randominvador.hpp"

RandomInvador::RandomInvador() {
  texture = std::vector<sf::Texture>(1);
  texture[0].loadFromFile(PROJECT_DIR "/src/media/random_invador.png");
  sprite.setTexture(texture[0]);
  sprite.setPosition(0, 30);
  sprite.setColor(sf::Color({209, 253, 0, 255}));
  isAlive = false;
}

void RandomInvador::Spawn() {
  isAlive = true;
  bool direction = rand() % 2;
  if (direction) {
    sprite.setPosition(-sprite.getLocalBounds().width, UI_OFFSET + 30);
    velocity = 2;
  } else {
    sprite.setPosition(WINDOW_WIDTH + UI_OFFSET, UI_OFFSET + 30);
    velocity = -2;
  }
}

void RandomInvador::Update() {
  if (sprite.getPosition().x > WINDOW_WIDTH + UI_OFFSET ||
      sprite.getPosition().x + sprite.getLocalBounds().width < 0) {
    isAlive = false;
  }
  sprite.move(velocity, 0);
}

void RandomInvador::Draw(sf::RenderWindow& window) { window.draw(sprite); }

sf::FloatRect RandomInvador::GetHitbox() const {
  if (isAlive) {
    return sf::FloatRect(
        sprite.getPosition(),
        {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height});
  } else {
    return sf::FloatRect(sprite.getPosition(), {0, 0});
  }
}
