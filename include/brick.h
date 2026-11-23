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
  Type type;
  int m_maxHealth{};
  int m_currentHealth{m_maxHealth};
  bool alive{true};
  SDL_FRect m_brick;
};

struct AllBricks {
  std::vector<Brick> m_allBricks;
};
const SDL_FRect getBrickIndex(Brick::Type type, int health);

void makeAllBricks(AllBricks& arrBricks);
