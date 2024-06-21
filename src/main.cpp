#include <Game/game.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <config.hpp>
#include <iostream>

std::string formatWithForwardZero(int num) {
  int width = 5;
  std::string str = std::to_string(num);
  return std::string(width - str.size(), '0') + str;
}

int main() {
  sf::RenderWindow window(
      sf::VideoMode(WINDOW_WIDTH + UI_OFFSET, WINDOW_HEIGHT + 2 * UI_OFFSET),
      "Game");
  window.setFramerateLimit(FPS);

  // cornerText text
  sf::Font Font;
  if (!Font.loadFromFile(PROJECT_DIR
                         "/src/media/fonts/PressStart2P-Regular.ttf")) {
    std::cerr << "Error loading font" << std::endl;
  }

  sf::Text cornerText("", Font, 24);
  cornerText.setColor(sf::Color(153, 0, 189, 255));
  cornerText.setPosition(WINDOW_WIDTH - 180,
                         WINDOW_HEIGHT + (2 * UI_OFFSET) - 45);

  // lifes indicator
  sf::Texture lifes;
  if (!lifes.loadFromFile(PROJECT_DIR "/src/media/spaceShip.png")) {
    std::cerr << "Error loading lives" << std::endl;
  }
  sf::Sprite livesSprite(lifes);
  livesSprite.setScale(0.8f, 0.8f);

  // score text
  sf::Text scoreText("", Font, 21);
  scoreText.setColor(sf::Color(153, 0, 189, 255));
  scoreText.setPosition(UI_OFFSET / 2, UI_OFFSET / 2);

  // Highscore text
  sf::Text highScoreText("", Font, 21);
  highScoreText.setColor(sf::Color(153, 0, 189, 255));
  highScoreText.setPosition(WINDOW_WIDTH - 150, UI_OFFSET / 2);

  Game game;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    game.InputHandle();
    game.Update();

    window.clear(sf::Color(20, 10, 20, 255));

    game.Draw(window);

    // Game state text
    if (game.running) {
      cornerText.setString(" Level 01");
    } else {
      cornerText.setString("Game Over");
    }

    // Score display
    scoreText.setString("SCORE\n" + formatWithForwardZero(game.score));

    // Highscore display
    highScoreText.setString("HIGHSCORE\n    " +
                            formatWithForwardZero(game.highScore));

    // Ship lifes display
    for (int i = 0; i < game.shipLives; i++) {
      livesSprite.setPosition(50 + (i * 45),
                              WINDOW_HEIGHT + (UI_OFFSET * 2) - 48);
      window.draw(livesSprite);
    }

    window.draw(scoreText);
    window.draw(highScoreText);
    window.draw(cornerText);
    window.display();
  }

  game.SaveHighScore();
  return 0;
}
