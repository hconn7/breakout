#include "collisionMng.h"
#include "config.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <algorithm>
#include <cstdlib>
#include <span>

bool CollisionMng::collidedWithBrick(Ball& ball, std::vector<Brick>& bricks) {
  bool collided{false};
  float centerX = ball.posX + BallProperties::radius;
  float centerY = ball.posY + BallProperties::radius;
  float radiusSquaured = BallProperties::radiusSquared;

  for (size_t brick = 0; brick < bricks.size(); brick++) {
    if (!bricks[brick].alive) {
      continue;
    }
    float closestX = std::clamp(centerX, bricks[brick].m_brick.x, bricks[brick].m_brick.x + pixelDataBrick::brickWidth);
    // SDL_Log("Clamped X: %f\n", closestX);
    float closestY = std::clamp(centerY, bricks[brick].m_brick.y, bricks[brick].m_brick.y + pixelDataBrick::brickHeight);

    float distX = centerX - closestX;
    float distY = centerY - closestY;
    float distantceSquared = (distX * distX) + (distY * distY);

    if (distantceSquared < radiusSquaured) {
      collided = true;

      if (bricks[brick].m_currentHealth <= 0) {
        bricks[brick].alive = false;
      } else if (static_cast<int>(bricks[brick].type) >= 4) {
        bricks[brick].alive = false;
      } else if (static_cast<int>(bricks[brick].type) >= 2) {
        bricks[brick].m_currentHealth -= 2;
      } else {
        bricks[brick].m_currentHealth -= 1;
      }

      if (std::abs(distX) > std::abs(distY)) {
        ball.speedX = -ball.speedX;
      } else if (std::abs(distY) > std::abs(distX)) {
        ball.speedY = -ball.speedY;
      } else {
        ball.speedX = -ball.speedX;
        ball.speedY = -ball.speedX;
      }
    }
  }
  return collided;
}
bool CollisionMng::detectWallHitX(Ball& b) {
  if (b.posX + (b.radius * 2) > Config::screenWidth) {
    b.posX = Config::screenWidth - (b.radius * 2);
    b.speedX = -b.speedX;
    return true;
  } else if (b.posX < 0) {
    b.posX = 0;
    b.speedX = -1 * (b.speedX);
  }

  return false;
}

bool CollisionMng::detectWallHitY(Ball& b) {
  if (b.posY + (b.radius * 2) > Config::screenHeight) {
    b.posY = 150;
    return true;
  } else if (b.posY <= 0 + 50) {
    b.posY = 50;
    b.speedY = -1 * (b.speedY);
  }
  return false;
}

void CollisionMng::collidedWithPlayer(Ball& b, Player& p) {
  float centerX = b.posX + BallProperties::radius;
  float centerY = b.posY + BallProperties::radius;
  float radiusSquaured = BallProperties::radiusSquared;

  float clampX = std::clamp(centerX, p.posX, p.posX + 49.f);
  float clampY = std::clamp(centerY, p.posY, p.posY + 11.f);

  float distX = centerX - clampX;
  float distY = centerY - clampY;

  float hypotenuse = (distX * distX) + (distY * distY);

  if (hypotenuse <= radiusSquaured) {
    if (std::abs(distX) > std::abs(distY)) {
      b.speedX = -b.speedX;
    } else if (std::abs(distY) > std::abs(distX)) {
      b.speedY = -b.speedY;
    } else {
      b.speedX = -b.speedX;
      b.speedY = -b.speedY;
    }
  }
  return;
}
