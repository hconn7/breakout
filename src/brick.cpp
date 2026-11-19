#include "brick.h"
#include "config.h"
#include "graphics.h"
#include <SDL3/SDL_error.h>

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
