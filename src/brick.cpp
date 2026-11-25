#include "brick.h"
#include "config.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <span>
#include <string>
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
bool loadBricks(AllBricks& allb, std::string lvlData) {
  SDL_Log("LEVEL DATA IS: %c", lvlData[0]);
  std::vector<Brick> arrayBricks;
  int type{};
  int rowMax = lvlData[1] - '0';
  float totalGridWidth = (Config::cols * pixelDataBrick::brickWidth);
  size_t charIndex = 2;
  char c = lvlData[charIndex];
  for (int rows = 0; rows < rowMax; rows++) {
    for (int cols = 0; cols < Config::cols; cols++) {

      switch (c) {
      case 'O':
        type = (5);
        break;
      case 'Y':
        type = (4);
        break;
      case 'P':
        type = 3;
        break;
      case 'B':
        type = 2;
        break;
      case 'G':
        type = 1;
        break;
      case 'R':
        type = 0;
        break;
      default:
        SDL_Log("defaut triggered");
        continue;
      }
      Brick::Type typeB = static_cast<Brick::Type>(type);
      SDL_FRect dst;
      float startX = (360 - totalGridWidth) / 2.0f;
      dst.x = 1 + startX + (cols * pixelDataBrick::brickWidth);
      dst.y = Config::Y_OFF_SET + (rows * pixelDataBrick::brickHeight);
      dst.w = pixelDataBrick::brickWidth;
      dst.h = pixelDataBrick::brickHeight;

      int maxHealth{};
      if (typeB == Brick::Type::orange || typeB == Brick::Type::yellow) {
        maxHealth = 1;
      } else if (typeB == Brick::Type::purple || typeB == Brick::Type::blue) {
        maxHealth = 3;
      } else {
        maxHealth = 6;
      }
      SDL_Log("Making brick with Type %d", static_cast<int>(typeB));
      Brick brickI{
          typeB, maxHealth, 6, true, SDL_FRect{dst.x, dst.y, dst.w, dst.h}};
      arrayBricks.push_back(brickI);
      charIndex++;
    }
  }
  if (lvlData[0] == '1') {
    allb.m_allBrickslvl1 = std::move(arrayBricks);
  }
  if (lvlData[0] == '2') {
    allb.m_allBrickslvl2 = std::move(arrayBricks);
  }
  if (lvlData[0] == '3')
    allb.m_allBrickslvl3 = std::move(arrayBricks);
  return true;
}

bool allBricksDead(std::span<Brick> bricks) {
  for (const auto& b : bricks) {
    if (b.alive) {
      return false;
    }
  }
  return true;
}
