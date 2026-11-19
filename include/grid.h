#pragma once

#include "config.h"
#include "graphics.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <vector>

struct Grid {
  int m_rows{Config::rows};
  int m_cols{Config::cols};
  int m_cellWidth{Config::cellWidth};
  int m_cellHeight{Config::cellHeight};
  std::vector<int> m_Grid{Config::rows * Config::cols};
};

int gridIndex(const Grid& g, int row, int col) {
  return (row * g.m_cols) + col;
}
