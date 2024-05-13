#include <config.hpp>

#include "game.hpp"

Game::Game() {
  barriers = CreateBarriers();
  invadors = CreateInvadors();
  invadorsDirection = 1;
  invadorsLasers = std::vector<Laser>();
}

Game::~Game() {}

void Game::Draw(sf::RenderWindow& window) {
  for (auto& laser : spaceship.lasers) {
    laser.Draw(window);
  }
  for (auto& laser : invadorsLasers) {
    laser.Draw(window);
  }
  for (auto& barrier : barriers) {
    barrier.Draw(window);
  }
  for (auto& invador : invadors) {
    invador.Draw(window);
  }
  spaceship.Draw(window);
}

void Game::Update() {
  spaceship.Update();

  DeleteInactiveLasers();

  if (invadorsShootDelay <= 0) {
    InvadorShootLaser();
  } else {
    invadorsShootDelay -= 0.1f;
  }

  MoveInvadors();

  for (auto& laser : spaceship.lasers) {
    laser.Update();
  }
  for (auto& laser : invadorsLasers) {
    laser.Update();
  }
  for (auto& invador : invadors) {
    invador.Update();
  }
}

void Game::InputHandle() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
      !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    spaceship.MoveLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
             !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    spaceship.MoveRight();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    spaceship.Fire();
  }
}

void Game::DeleteInactiveLasers() {
  for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
    if (!it->active) {
      spaceship.lasers.erase(it);
    } else {
      ++it;
    }
  }
  for (auto it = invadorsLasers.begin(); it != invadorsLasers.end();) {
    if (!it->active) {
      invadorsLasers.erase(it);
    } else {
      ++it;
    }
  }
}

std::vector<Barrier> Game::CreateBarriers() {
  int barrierWidth = 25 * 3;
  float gap = (WINDOW_WIDTH - barrierWidth * 4) / 5;
  for (int i = 0; i < 4; i++) {
    float x = gap * (i + 1) + i * barrierWidth;
    barriers.push_back(Barrier(sf::Vector2f(x, WINDOW_HEIGHT - 100)));
  }
  return barriers;
}

std::vector<Invador> Game::CreateInvadors() {
  int gap = 15;
  // Enemies field is 11 x 5
  // Invador sptite is 35 x 30
  float beginX = (WINDOW_WIDTH - ((35 * 11) + (gap * 10))) / 2;
  float beginY = 50;
  for (int row = 0; row < 5; row++) {
    int Type = 0;
    if (row == 0) {
      Type = 2;
    }
    if (row == 1 || row == 2) {
      Type = 1;
    }
    for (int col = 0; col < 11; col++) {
      int x = beginX + (col * (gap + 35));
      int y = beginY + (row * (gap + 30));
      invadors.push_back(Invador(sf::Vector2f(x, y), Type));
    }
  }
  return invadors;
}

void Game::MoveInvadors() {
  for (auto& invador : invadors) {
    if (invador.position.x + 35 >= WINDOW_WIDTH) {
      invadorsDirection = -1;
      MoveInvadorsDown(5);
    } else if (invador.position.x <= 0) {
      invadorsDirection = 1;
      MoveInvadorsDown(5);
    }
    invador.position.x += invadorsDirection;
    invador.Update();
  }
}

void Game::MoveInvadorsDown(int dist) {
  for (auto& invador : invadors) {
    invador.position.y += dist;
  }
}

void Game::InvadorShootLaser() {
  int random = rand() % (invadors.size() - 0 + 1);
  invadorsLasers.push_back(Laser({invadors[random].position.x + ((35 - 14) / 2),
                                  invadors[random].position.y + 20},
                                 -5, invadors[random].sprite.getColor()));
  invadorsShootDelay = 3.5f;
}
