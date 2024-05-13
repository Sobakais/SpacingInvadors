#include <Game/game.hpp>
#include <SFML/Graphics.hpp>
#include <config.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
  window.setFramerateLimit(FPS);

  Game game;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    game.InputHandle();
    game.Update();

    window.clear();

    game.Draw(window);

    window.display();
  }

  return 0;
}
