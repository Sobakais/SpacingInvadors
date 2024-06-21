#pragma once

#include <Barrier/barrier.hpp>
#include <Invador/invador.hpp>
#include <RandomInvador/randominvador.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <Spaceship/spaceship.hpp>
#include <UI.hpp>

class Game {
 public:
  Game();
  ~Game();
  void Draw(sf::RenderWindow& window);
  void Update();
  void InputHandle();
  void CheckCollisions();
  bool HitboxCollide(const sf::FloatRect hitbox1, const sf::FloatRect hitbox2);
  bool running;

  std::vector<Barrier> CreateBarriers();
  std::vector<Invador> CreateInvadors();

  int shipLives;
  int score;
  int highScore;

  void UpdateHighScore();
  int LoadHighScore();
  void SaveHighScore();

 private:
  UserInterface ui;

  sf::Music backgroundMusic;
  Spaceship spaceship;

  void GameOver();
  void InintializeGame();
  void ResetGame();

  std::vector<Laser> invadorsLasers;
  std::vector<Invador> invadors;
  float invadorsShootDelay = 3.5f;
  int invadorsDirection;

  RandomInvador randomInvador;
  float randomInvadorsDelay = 1.0f;

  std::vector<Barrier> barriers;

  void MoveInvadors();
  void MoveInvadorsDown(int dist);
  void DeleteInactiveLasers();
  void InvadorShootLaser();
};
