#include "graphics.h"

bool init(Graphics& graphics) {
  SDL_Surface* surface{nullptr};
  char* png_path = {nullptr};

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error loading Sub Systems %s", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer("Breakout", 800, 600, 0, &graphics.window, &graphics.renderer)) {
    SDL_Log("Error init renderer and window%s", SDL_GetError());
    return false;
  }

  SDL_asprintf(&png_path, "%sassets/spritesheet-breakout.png", SDL_GetBasePath());
  surface = SDL_LoadPNG(png_path);

  SDL_free(png_path);

  graphics.spritePng = SDL_CreateTextureFromSurface(graphics.renderer, surface);

  SDL_DestroySurface(surface);
  return true;
}
