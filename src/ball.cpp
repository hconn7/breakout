#include "ball.h"
#include "config.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <algorithm>

bool updateBall(Ball& b, float deltaTime) {
  SDL_Log("Ball X: %f\n", b.posX);

  b.posX += b.speed * deltaTime;
  detectWallHitX(b, deltaTime);

  return true;
}

bool detectWallHitX(Ball& b, float deltaTime) {
  if (b.posX > Config::screenWidth) {
    b.posX = Config::screenWidth;
    b.speed = -b.speed;
    return true;
  }

  return false;
}
