#pragma once

#include "brick.h"
#include "config.h"
#include <SDL3/SDL_stdinc.h>
struct Ball {
  float posY{200};
  float posX{Config::screenWidth / 2.f};
  float radius{5};
  float speedX{150};
  float speedY{150};
};

bool detectPlayerHit(Ball& b);
bool updateBall(Ball& ball, float deltaTime, AllBricks& b);
