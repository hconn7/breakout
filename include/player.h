#pragma once
#include <SDL3/SDL_rect.h>

struct PlayerState {
  int m_lives{3};
  int m_score{0};
};

struct Player {

  float posX{140};
  float posY{405};
  SDL_FRect player{posX, posY, 54, 14};
};
