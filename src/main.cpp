#include "brick.h"
#include "graphics.h"
#include "grid.h"
#include "input.h"
#include <SDL3/SDL_render.h>
int main() {
  Graphics graphics{};
  Input input{};

  if (!init(graphics))
    return 0;

  loadSpritePng(graphics);

  while (!input.update()) {

    SDL_RenderClear(graphics.renderer);
    renderAllBick(graphics);
    SDL_RenderPresent(graphics.renderer);
  }
}
