#include "graphics.h"
#include "brick.h"
#include "config.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

bool init(Graphics& graphics) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error loading Sub Systems %s", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer("Breakout", 360, 480, 0, &graphics.window, &graphics.renderer)) {
    SDL_Log("Error init renderer and window%s", SDL_GetError());
    return false;
  }
  return true;
}

bool loadSpritePng(Graphics& graphics) {

  SDL_Surface* surface{nullptr};
  char* png_path = {nullptr};

  SDL_asprintf(&png_path, "%sassets/spritesheet-breakout_1.png", SDL_GetBasePath());
  surface = SDL_LoadPNG(png_path);
  SDL_SetRenderLogicalPresentation(graphics.renderer, 360, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

  SDL_free(png_path);
  graphics.spritePng = SDL_CreateTextureFromSurface(graphics.renderer, surface);

  return true;
}

bool renderSpritePng(Graphics& graphics) {
  SDL_FRect src{0.0f, 0.0f, 559.0f, 337.0f};
  SDL_FRect dst{100.0f, 100.0f, 559.0f, 337.0f};
  if (!SDL_RenderTexture(graphics.renderer, graphics.spritePng, &src, &dst)) {
    SDL_Log("Failed to render png %s", SDL_GetError());
    return false;
  }
  return true;
}

bool renderBrick(Graphics& g) {
  SDL_FRect src{getBrickIndex(Brick::Type::red, 6)};
  SDL_FRect dst{100, 100, 32, 16};

  if (!SDL_RenderTexture(g.renderer, g.spritePng, &src, &dst)) {
    SDL_Log("Failed to render brick %s", SDL_GetError());
    return false;
  }
  return true;
}

bool renderAllBick(Graphics& graphics) {
  for (int row = 0; row < Config::rows; row++) {
    for (int col = 0; col < Config::cols; col++) {
      Brick::Type type = static_cast<Brick::Type>(row);

      SDL_FRect dst;

      dst.x = Config::X_OFF_SET + (col * Config::cellWidth);
      dst.y = Config::Y_OFF_SET + (row * Config::cellHeight);
      dst.w = Config::cellWidth;
      dst.h = Config::cellHeight;

      SDL_FRect src = getBrickIndex(type, 6);
      if (!SDL_RenderTexture(graphics.renderer, graphics.spritePng, &src, &dst)) {
        SDL_Log("Failed to render png %s", SDL_GetError());
        return false;
      }
    }
  }
  return true;
}
