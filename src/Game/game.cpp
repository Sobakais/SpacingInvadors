#include <config.hpp>
#include <cstdlib>

#include "game.hpp"

Game::Game() { InintializeGame(); }

Game::~Game() {}

void Game::Draw(sf::RenderWindow& window) {
  ui.Draw(window);

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

  if (randomInvador.isAlive) {
    randomInvador.Draw(window);
  }
}

void Game::Update() {
  if (!running) {
    return;
  }
  CheckCollisions();

  spaceship.Update();

  DeleteInactiveLasers();

  if (invadorsShootDelay <= 0) {
    InvadorShootLaser();
  } else {
    invadorsShootDelay -= 0.1f;
  }

  if (!randomInvador.isAlive && randomInvadorsDelay <= 0) {
    randomInvador.Spawn();
  } else if (randomInvador.isAlive && randomInvadorsDelay <= 0) {
    randomInvadorsDelay = rand() % (40 + 15 + 1) + 15;
  } else if (!randomInvador.isAlive && randomInvadorsDelay > 0) {
    randomInvadorsDelay -= 0.1f;
  }

  if (randomInvador.isAlive) {
    randomInvador.Update();
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
  if (running) {
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
  } else {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      ResetGame();
      InintializeGame();
    }
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
  float gap = (WINDOW_WIDTH + UI_OFFSET - barrierWidth * 4) / 5;
  for (int i = 0; i < 4; i++) {
    float x = gap * (i + 1) + i * barrierWidth;
    barriers.push_back(Barrier(sf::Vector2f(x, WINDOW_HEIGHT + UI_OFFSET - 135)));
  }
  return barriers;
}

std::vector<Invador> Game::CreateInvadors() {
  int gap = 15;
  // Enemies field is 11 x 5
  // Invador sptite is 35 x 30
  float beginX = (WINDOW_WIDTH + (UI_OFFSET / 2) - ((35 * 11) + (gap * 10))) / 2;
  float beginY = 50 + UI_OFFSET;
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
    if (invador.position.x + 35 >= WINDOW_WIDTH + UI_OFFSET / 2) {
      invadorsDirection = -1;
      MoveInvadorsDown(7);
    } else if (invador.position.x <= UI_OFFSET / 2) {
      invadorsDirection = 1;
      MoveInvadorsDown(7);
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
  if (invadors.empty()) {
    return;
  }
  int random = rand() % (invadors.size() - 0 + 1);
  invadorsLasers.push_back(Laser({invadors[random].position.x + ((35 - 14) / 2),
                                  invadors[random].position.y + 20},
                                 -5, invadors[random].sprite.getColor()));
  invadorsShootDelay = 5.5f;
}

void Game::CheckCollisions() {
  // Check if spaceship lasers collides with invadors and block
  for (auto& laser : spaceship.lasers) {
    // Laser collides with invadors
    auto it = invadors.begin();
    while (it != invadors.end()) {
      if (HitboxCollide(it->GetHitbox(), laser.GetHitbox())) {
        it = invadors.erase(it);
        laser.active = false;
      } else {
        ++it;
      }
    }
    // Laser collides with blocks
    for (auto& barrier : barriers) {
      auto it = barrier.blocks.begin();
      while (it != barrier.blocks.end()) {
        if (HitboxCollide(it->GetHitbox(), laser.GetHitbox())) {
          it = barrier.blocks.erase(it);
          laser.active = false;
        } else {
          ++it;
        }
      }
    }

    if (HitboxCollide(randomInvador.GetHitbox(), laser.GetHitbox())) {
      laser.active = false;
      randomInvador.isAlive = false;
    }
  }

  // Check if invadors lasers collides with spaceship and block
  for (auto& laser : invadorsLasers) {
    // Laser collides with blocks
    for (auto& barrier : barriers) {
      auto it = barrier.blocks.begin();
      while (it != barrier.blocks.end()) {
        if (HitboxCollide(it->GetHitbox(), laser.GetHitbox())) {
          it = barrier.blocks.erase(it);
          laser.active = false;
        } else {
          ++it;
        }
      }
    }
    // Laser collides with spaceship
    if (HitboxCollide(spaceship.GetHitbox(), laser.GetHitbox())) {
      laser.active = false;
      shipLives--;
      if (shipLives == 0) {
        GameOver();
      }
    }
  }

  // Check if invadors lasers collides with spaceship and block
  for (auto& invador : invadors) {
    for (auto& barrier : barriers) {
      auto it = barrier.blocks.begin();
      while (it != barrier.blocks.end()) {
        if (HitboxCollide(it->GetHitbox(), invador.GetHitbox())) {
          it = barrier.blocks.erase(it);
        } else {
          ++it;
        }
      }
    }
    if (HitboxCollide(spaceship.GetHitbox(), invador.GetHitbox())) {
      GameOver();
    }
  }
}

bool Game::HitboxCollide(const sf::FloatRect hitbox1,
                         const sf::FloatRect hitbox2) {
  // Determine the minimum and maximum points of each hitbox
  float left1 = hitbox1.left;
  float right1 = hitbox1.left + hitbox1.width;
  float top1 = hitbox1.top;
  float bottom1 = hitbox1.top + hitbox1.height;

  float left2 = hitbox2.left;
  float right2 = hitbox2.left + hitbox2.width;
  float top2 = hitbox2.top;
  float bottom2 = hitbox2.top + hitbox2.height;

  return (left1 < right2 && right1 > left2 && top1 < bottom2 && bottom1 > top2);
}

void Game::InintializeGame() {
  ui = UserInterface();
  
  shipLives = 3;

  barriers = CreateBarriers();

  invadors = CreateInvadors();
  invadorsDirection = 1;
  invadorsLasers = std::vector<Laser>();

  randomInvador = RandomInvador();

  running = true;
}

void Game::GameOver() { running = false; }

void Game::ResetGame() {
  spaceship.Reset();
  invadors.clear();
  invadorsLasers.clear();
  barriers.clear();
}
