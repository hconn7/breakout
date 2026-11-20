#include "graphics.h"
#include "brick.h"
#include "config.h"
#include "player.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

bool init(Graphics& graphics) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error loading Sub Systems %s", SDL_GetError());
    return false;
  }
  if (!SDL_CreateWindowAndRenderer("Breakout", 360, 480, 0, &graphics.window, &graphics.renderer)) {
    SDL_Log("Error init renderer and window%s", SDL_GetError());
    return false;
  }
  SDL_SetRenderVSync(graphics.renderer, 1);
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

void destroy(Graphics& graphics) {
  SDL_DestroyRenderer(graphics.renderer);
  graphics.renderer = nullptr;

  SDL_DestroyWindow(graphics.window);
  graphics.window = nullptr;

  SDL_DestroyTexture(graphics.spritePng);
  graphics.spritePng = nullptr;
}

bool renderAllBick(Graphics& graphics) {
  float totalGridWidth = (Config::cols * pixelDataBrick::brickWidth + ((Config::cols - 2)));
  for (int rows = 0; rows < Config::rows; rows++) {
    for (int cols = 0; cols < Config::cols; cols++) {
      SDL_FRect dst;
      float startX = (360 - totalGridWidth) / 2.0f;
      Brick::Type type = static_cast<Brick::Type>(rows);
      SDL_FRect src{getBrickIndex(type, 6)};

      dst.x = 1 + startX + (cols * pixelDataBrick::brickWidth);
      dst.y = Config::Y_OFF_SET + (rows * pixelDataBrick::brickHeight);
      dst.w = pixelDataBrick::brickWidth;
      dst.h = pixelDataBrick::brickHeight;
      SDL_RenderTexture(graphics.renderer, graphics.spritePng, &src, &dst);
    }
  }
  return true;
}
bool renderPlayer(Graphics& graphics, Player& p) {

  SDL_FRect playerSpriteSrc{2, 68, 54, 15};

  p.player = {p.posX, p.posY, 54, 14};

  if (!SDL_RenderTexture(graphics.renderer, graphics.spritePng, &playerSpriteSrc, &p.player)) {
    SDL_Log("Failed to render png %s", SDL_GetError());
    return false;
  }
  return true;
}

void render(Graphics& graphics, Player& player) {
  renderAllBick(graphics);
  renderPlayer(graphics, player);
}
