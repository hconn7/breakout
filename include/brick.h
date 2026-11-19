#pragma once

#include "config.h"
#include "graphics.h"
#include <SDL3/SDL_rect.h>
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
};

const SDL_FRect getBrickIndex(Brick::Type type, int health);
bool renderBrick(Graphics& g);
