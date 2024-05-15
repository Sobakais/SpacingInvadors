#include <SFML/Graphics/Rect.hpp>
#include <config.hpp>

#include "spaceship.hpp"

Spaceship::Spaceship() {
  for (int i = 0; i < 21; i++) {
    sf::Texture texture;
    texture.loadFromFile(PROJECT_DIR "/src/media/animation_Spaceship/sprite_" +
                         std::to_string(i) + ".png");
    animation.push_back(texture);
  }
  sprite.setTexture(animation[frame]);
  position = {(WINDOW_WIDTH + UI_OFFSET - sprite.getLocalBounds().width) / 2,
              (WINDOW_HEIGHT + UI_OFFSET - 25 - sprite.getLocalBounds().height)};
  sprite.setPosition(position);
  lasers = std::vector<Laser>();
}

Spaceship::~Spaceship() {
  // As far as I can tell, Sprite destructor will clean up its texture
}

void Spaceship::Draw(sf::RenderWindow& window) { window.draw(sprite); }

void Spaceship::Fire() {
  // 14 and 20 is resolution of laser sprite
  if (delay_to_shoot <= 0.f) {
    lasers.push_back(Laser(
        {position.x + (sprite.getLocalBounds().width / 2) - 7, position.y - 19},
        5, sf::Color({153, 0, 189, 255})));
    delay_to_shoot = 2.5f;
  }
}

void Spaceship::Update() {
  time = time > 20.2f ? 0.f : time + 0.2f;
  frame = (int)time;
  sprite.setTexture(animation[frame]);
  sprite.setPosition(position);
  delay_to_shoot = delay_to_shoot > 0.f ? delay_to_shoot - 0.1f : 0.f;
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

sf::FloatRect Spaceship::GetHitbox() const {
  return sf::FloatRect(position, {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height});
}

void Spaceship::Reset() {
  position = {(WINDOW_WIDTH + UI_OFFSET - sprite.getLocalBounds().width) / 2,
              (WINDOW_HEIGHT + UI_OFFSET - 25 - sprite.getLocalBounds().height)};
  lasers.clear();
}
