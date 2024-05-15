#pragma once
#include <SFML/Graphics.hpp>
#include <config.hpp>

class UserInterface {
 public:
  UserInterface() {
    sf::Color uiColor = sf::Color(153, 0, 189, 255);

    topLine = sf::RectangleShape({WINDOW_WIDTH + UI_OFFSET, 2});
    topLine.setPosition(0, 0);
    topLine.setFillColor(uiColor);

    botLine = sf::RectangleShape({WINDOW_WIDTH + UI_OFFSET, 2});
    botLine.setPosition(0, WINDOW_HEIGHT - 2 + UI_OFFSET * 2);
    botLine.setFillColor(uiColor);

    leftLine = sf::RectangleShape({2, WINDOW_HEIGHT + UI_OFFSET * 2});
    leftLine.setPosition(0, 0);
    leftLine.setFillColor(uiColor);

    rightLine = sf::RectangleShape({2, WINDOW_HEIGHT + UI_OFFSET * 2});
    rightLine.setPosition(WINDOW_WIDTH + UI_OFFSET - 2, 0);
    rightLine.setFillColor(uiColor);

    separatorLine = sf::RectangleShape({WINDOW_WIDTH, 2});
    separatorLine.setPosition(UI_OFFSET / 2, WINDOW_HEIGHT + UI_OFFSET);
    separatorLine.setFillColor(uiColor);
  };

  void Draw(sf::RenderWindow& window) {
    window.draw(topLine);
    window.draw(botLine);
    window.draw(leftLine);
    window.draw(rightLine);
    window.draw(separatorLine);
  };

 private:
  sf::Color uiColor;
  sf::RectangleShape topLine;
  sf::RectangleShape botLine;
  sf::RectangleShape leftLine;
  sf::RectangleShape rightLine;
  sf::RectangleShape separatorLine;
};
