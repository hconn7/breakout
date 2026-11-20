#include "brick.h"
#include "graphics.h"
#include "grid.h"
#include "input.h"
#include "player.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
int main() {
  Graphics graphics{};
  Player player;

  if (!init(graphics))
    return 0;

  loadSpritePng(graphics);
  Uint64 t = SDL_GetTicksNS();

  while (!update(player, t)) {

    SDL_RenderClear(graphics.renderer);
    render(graphics, player);
    SDL_RenderPresent(graphics.renderer);
  }
  destroy(graphics);
}
