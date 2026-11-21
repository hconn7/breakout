#pragma once

#include "config.h"
#include <SDL3/SDL_rect.h>
#include <vector>
struct Brick {
  enum class Type {
    red,
    green,
    blue,
    purple,
    yellow,
    orange,
    maxBricks
  };

  int m_MaxHealth{6};
  bool alive{true};
  std::vector<SDL_FRect> m_bricks;
};

const SDL_FRect getBrickIndex(Brick::Type type, int health);
void makeAllBricks(Brick& b);
