#include "laser.hpp"
#include <SFML/Graphics/Color.hpp>
#include <config.hpp>

std::vector<sf::Texture> Laser::animation = std::vector<sf::Texture>();

Laser::Laser(sf::Vector2f position, int velocity, sf::Color color) {
  if (animation.empty()){
    for (int i = 0; i < 13; i++) {
      sf::Texture texture;
      texture.loadFromFile(PROJECT_DIR "/src/media/animation_Laser/sprite_" + std::to_string(i) + ".png");
      animation.push_back(texture);
    }
  }
  this->position = position;
  this->velocity = velocity;
  sprite.setPosition(position);
  sprite.setColor(color);
  sprite.setTexture(animation[frame]);
  active = true;
  time = 0.f;
}

Laser::~Laser() {
}

void Laser::Draw(sf::RenderWindow& window) {
  window.draw(sprite);
}

void Laser::Update() {
  if (position.y + sprite.getLocalBounds().height < 0.f || position.y > WINDOW_HEIGHT) {
    active = false;
  }
  time = time > 12.7f ? 0.f : time + 0.2f;
  frame = (int)time;
position.y -= velocity;
  sprite.setTexture(animation[frame]);
  sprite.setPosition(position);

}
