#pragma once

#include "config.h"
#include <SDL3/SDL_rect.h>
#include <span>
#include <string>
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
  std::vector<Brick> m_allBrickslvl1;
  std::vector<Brick> m_allBrickslvl2;
  std::vector<Brick> m_allBrickslvl3;
};
const SDL_FRect getBrickIndex(Brick::Type type, int health);
bool loadBricks(AllBricks& allb, std::string lvlData);
void makeAllBricks(AllBricks& arrBricks);
bool allBricksDead(std::span<Brick> bricks);
