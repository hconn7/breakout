
#include "graphics.h"
#include "ball.h"
#include "brick.h"
#include "config.h"
#include "player.h"
#include "text.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <iostream>
#include <vector>

bool initGraphics(Graphics& graphics) {
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
bool initFont(Text& t, Graphics& g) {
  char* fontPath{};
  SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};
  if (!TTF_Init()) {
    SDL_Log("Couldn't init SDL_ttf: %s\n", SDL_GetError());
    return false;
  }
  asprintf(&fontPath, "%sassets/PressStart2P-Regular.ttf", SDL_GetBasePath());
  t.m_font = TTF_OpenFont(fontPath, 18.0f);
  free(fontPath);
  if (!t.m_font) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    return false;
  }
  SDL_Surface* textSurface = TTF_RenderText_Blended(t.m_font, "TEST", 0, color);
  if (textSurface) {
    t.m_textTexture = SDL_CreateTextureFromSurface(g.renderer, textSurface);
    SDL_DestroySurface(textSurface);
  }
  if (!t.m_textTexture) {
    SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool renderText(Graphics& g, Text& t) {
  int w = 0, h = 0;
  SDL_FRect dst;
  const float scale = 4.0f;

  SDL_GetRenderOutputSize(g.renderer, &w, &h);
  SDL_GetTextureSize(t.m_textTexture, &dst.w, &dst.h);
  dst.x = ((w / scale) - dst.w) / 2.0f;
  dst.y = ((h / scale) - dst.h) / 2.0f;

  if (!SDL_RenderTexture(g.renderer, t.m_textTexture, NULL, &dst)) {
    SDL_Log("Failed to set render Texture in Graphics call: %s", SDL_GetError());
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

void destroy(Graphics& graphics) {
  SDL_DestroyRenderer(graphics.renderer);
  graphics.renderer = nullptr;

  SDL_DestroyWindow(graphics.window);
  graphics.window = nullptr;

  SDL_DestroyTexture(graphics.spritePng);
  graphics.spritePng = nullptr;
}

bool renderAllBricks(Graphics& graphics, AllBricks& b) {
  for (Brick& r : b.m_allBricks) {

    if (!r.alive) {
      continue;
    }
    Brick::Type type = static_cast<Brick::Type>(static_cast<int>(r.m_brick.y / pixelDataBrick::brickHeight));
    SDL_FRect src{getBrickIndex(type, 6)};
    SDL_FRect dst{r.m_brick.x, r.m_brick.y, r.m_brick.w, r.m_brick.h};

    SDL_RenderTexture(graphics.renderer, graphics.spritePng, &src, &dst);
  }

  return true;
}

bool renderBall(Graphics& graphics, Ball& ball) {
  SDL_FRect ballSrc{20, 22, 12, 12};

  SDL_FRect ballDst = {ball.posX, ball.posY, 12, 12};

  if (!SDL_RenderTexture(graphics.renderer, graphics.spritePng, &ballSrc, &ballDst)) {
    SDL_Log("Failed to render png %s", SDL_GetError());
    return false;
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

void render(Graphics& graphics, Player& player, Ball& ball, AllBricks& b, Text& t) {
  renderAllBricks(graphics, b);
  renderPlayer(graphics, player);
  renderBall(graphics, ball);
  renderText(graphics, t);
}
