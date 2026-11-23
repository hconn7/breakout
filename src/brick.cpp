#include "brick.h"
#include "config.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <vector>

const SDL_FRect getBrickIndex(Brick::Type type, int health) {
  int brickMultiplierHealth = (6 - health);
  SDL_FRect rect{};
  switch (type) {
  case Brick::Type::red:
    rect = SDL_FRect(pixelDataBrick::allBricksX + (pixelDataBrick::brickWidth * brickMultiplierHealth), pixelDataBrick::redY, pixelDataBrick::brickWidth, pixelDataBrick::brickHeight);
    break;
  case Brick::Type::green:
    rect = SDL_FRect(pixelDataBrick::allBricksX + (pixelDataBrick::brickWidth * brickMultiplierHealth), pixelDataBrick::greenY, pixelDataBrick::brickWidth, pixelDataBrick::brickHeight);
    break;
  case Brick::Type::blue:
    rect = SDL_FRect(pixelDataBrick::allBricksX + (pixelDataBrick::brickWidth * brickMultiplierHealth), pixelDataBrick::blueY, pixelDataBrick::brickWidth, pixelDataBrick::brickHeight);
    break;
  case Brick::Type::purple:
    rect = SDL_FRect(pixelDataBrick::allBricksX + (pixelDataBrick::brickWidth * brickMultiplierHealth), pixelDataBrick::purpleY, pixelDataBrick::brickWidth, pixelDataBrick::brickHeight);
    break;
  case Brick::Type::yellow:
    rect = SDL_FRect(pixelDataBrick::allBricksX + (pixelDataBrick::brickWidth * brickMultiplierHealth), pixelDataBrick::yellowY, pixelDataBrick::brickWidth, pixelDataBrick::brickHeight);
    break;
  case Brick::Type::orange:
    rect = SDL_FRect(pixelDataBrick::allBricksX + (pixelDataBrick::brickWidth * brickMultiplierHealth), pixelDataBrick::orangeY, pixelDataBrick::brickWidth, pixelDataBrick::brickHeight);
    break;
  default:
    break;
  }
  return rect;
}

void makeAllBricks(AllBricks& arrBricks) {
  float totalGridWidth = (Config::cols * pixelDataBrick::brickWidth);
  for (int rows = 0; rows < Config::rows; rows++) {
    for (int cols = 0; cols < Config::cols; cols++) {
      SDL_FRect dst;
      float startX = (360 - totalGridWidth) / 2.0f;
      Brick::Type type = static_cast<Brick::Type>(rows);
      dst.x = 1 + startX + (cols * pixelDataBrick::brickWidth);
      dst.y = Config::Y_OFF_SET + (rows * pixelDataBrick::brickHeight);
      SDL_Log("DST Y FOR BRICK: %f", dst.y);
      dst.w = pixelDataBrick::brickWidth;
      dst.h = pixelDataBrick::brickHeight;

      int maxHealth{};
      if (static_cast<int>(type) >= 4) {
        maxHealth = 1;
      } else if (static_cast<int>(type) >= 2) {
        maxHealth = 3;
      } else {
        maxHealth = 6;
      }

      Brick brickI{
          type, maxHealth, 6, true, SDL_FRect{dst.x, dst.y, dst.w, dst.h}};

      arrBricks.m_allBricks.push_back(brickI);
    }
  }
}
