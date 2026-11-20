#pragma once
#include <SDL3/SDL_rect.h>
struct Player {
  float posX{140};
  float posY{405};
  SDL_FRect player{posX, posY, 54, 14};
};
