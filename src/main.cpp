#include "ball.h"
#include "brick.h"
#include "graphics.h"
#include "input.h"
#include "player.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <type_traits>

int main() {
  Graphics graphics{};
  Player player{};
  Ball ball{};
  Brick bricks{};

  if (!init(graphics))
    return 0;

  loadSpritePng(graphics);
  makeAllBricks(bricks);

  Uint64 time = SDL_GetTicksNS();
  while (true) {

    Uint64 currentTime = SDL_GetTicksNS();
    float deltaTime = (currentTime - time) / 1000000000.0f;
    time = currentTime;

    if (update(player, deltaTime)) {
      break;
    }
    updateBall(ball, deltaTime);
    SDL_RenderClear(graphics.renderer);
    render(graphics, player, ball, bricks);
    SDL_RenderPresent(graphics.renderer);
  }
  destroy(graphics);
}
