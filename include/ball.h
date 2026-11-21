#pragma once

#include <SDL3/SDL_stdinc.h>
struct Ball {
  float posY{100};
  float posX{100};
  float radius{5};
  float speed{100};
};

bool updateBall(Ball& ball, float deltaTime);
void resolveBrick(Ball& ball);
bool detectWallHitX(Ball& b, float dt);
