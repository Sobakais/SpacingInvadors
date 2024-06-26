#include "invador.hpp"

std::vector<std::vector<sf::Texture>> Invador::allInvadorAnimations = {
    {}, {}, {}};

Invador::Invador(sf::Vector2f position, int type) {
  if (allInvadorAnimations[0].empty()) {
    for (int i = 0; i < 3; i++) {
      for (int frame = 0; frame < 2; frame++) {
        sf::Texture texture;
        texture.loadFromFile(
            PROJECT_DIR "/src/media/animation_Invador/sprite_" +
            std::to_string(i) + "_" + std::to_string(frame) + ".png");
        allInvadorAnimations[i].push_back(texture);
      }
    }
  }
  this->type = type;
  this->position = position;

  animation = allInvadorAnimations[type];
  sprite.setTexture(animation[frame]);
  sprite.setPosition(position);
  switch (type) {
    case 0:
      sprite.setColor(sf::Color(255, 25, 140, 255));
      break;
    case 1:
      sprite.setColor(sf::Color(136, 77, 255, 255));
      break;
    case 2:
      sprite.setColor(sf::Color(25, 178, 255, 255));
      break;
    default:
      break;
  }
}

void Invador::Draw(sf::RenderWindow& window) { window.draw(sprite); }

void Invador::Update() {
  sprite.setPosition(position);
  time = time > 1.9f ? 0.f : time + 0.05f;
  frame = (int)time;
  sprite.setTexture(animation[frame]);
}

sf::FloatRect Invador::GetHitbox() const {
  return sf::FloatRect(position, {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height});
}
