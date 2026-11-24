
#include "graphics.h"
#include "UI.h"
#include "ball.h"
#include "brick.h"
#include "config.h"
#include "player.h"
#include "text.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdlib>
#include <iostream>
#include <ranges>
#include <vector>

bool initGraphics(Graphics& graphics) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error loading Sub Systems %s", SDL_GetError());
    return false;
  }
  if (!SDL_CreateWindowAndRenderer("Breakout", 360, Config::screenHeight, 0, &graphics.window, &graphics.renderer)) {
    SDL_Log("Error init renderer and window%s", SDL_GetError());
    return false;
  }
  SDL_SetRenderVSync(graphics.renderer, 1);
  return true;
}

bool setText(Graphics& g, Text& t, const char* str) {
  SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};

  SDL_Surface* textSurface = TTF_RenderText_Blended(t.m_font, str, 0, color);
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
bool renderEndScreen(SDL_Renderer* renderer, UI& ui) {
  Text& score = ui.m_endUI.m_textScore;
  Text& replay = ui.m_endUI.m_textReplay;
  SDL_GetTextureSize(score.m_textTexture, &score.m_dst.w, &score.m_dst.h);
  SDL_GetTextureSize(replay.m_textTexture, &replay.m_dst.w, &replay.m_dst.h);
  return true;
}

bool renderStartMenu(Graphics& g, UI& ui) {

  Text& breakout = ui.m_menu.m_textBreakout;
  Text& start = ui.m_menu.m_textStart;
  Text& highScore = ui.m_menu.m_textHighScore;
  std::vector<Text> allMenuText{highScore, start, breakout};
  SDL_SetRenderDrawColor(g.renderer, 24, 58, 74, 255);
  for (size_t i = 0; i < allMenuText.size(); i++) {
    SDL_RenderFillRect(g.renderer, &allMenuText[i].m_dst);
    if (!SDL_RenderTexture(g.renderer, allMenuText[i].m_textTexture, NULL, &allMenuText[i].m_dst)) {
      SDL_Log("Failed to render MenuText: %s", SDL_GetError());
      return false;
    }
  }
  return true;
}

bool renderText(Graphics& g, TextHud& t) {
  int w = 0, h = 0;
  setText(g, t.m_lives, t.m_lives.m_string.c_str());
  setText(g, t.m_score, t.m_score.m_string.c_str());

  SDL_GetRenderOutputSize(g.renderer, &w, &h);

  SDL_GetTextureSize(t.m_lives.m_textTexture, &t.m_lives.m_dst.w, &t.m_lives.m_dst.h);
  SDL_GetTextureSize(t.m_score.m_textTexture, &t.m_score.m_dst.w, &t.m_score.m_dst.h);

  if (!SDL_RenderTexture(g.renderer, t.m_lives.m_textTexture, NULL, &t.m_score.m_dst)) {
    SDL_Log("Failed to set render Texture in Graphics call: %s", SDL_GetError());
    return false;
  }
  if (!SDL_RenderTexture(g.renderer, t.m_score.m_textTexture, NULL, &t.m_lives.m_dst)) {
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
  SDL_SetRenderLogicalPresentation(graphics.renderer, 360, Config::screenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

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

bool renderAllBricks(Graphics& graphics, AllBricks& b) {
  for (Brick& r : b.m_allBricks) {

    if (!r.alive) {
      continue;
    }
    float relativeY = r.m_brick.y - Config::Y_OFF_SET;
    Brick::Type type = static_cast<Brick::Type>(static_cast<int>(relativeY / pixelDataBrick::brickHeight));
    SDL_FRect src{getBrickIndex(type, r.m_currentHealth)};
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

void render(Graphics& graphics, Player& player, Ball& ball, AllBricks& b, TextHud& t) {
  renderAllBricks(graphics, b);
  renderPlayer(graphics, player);
  renderBall(graphics, ball);
  renderText(graphics, t);
}
void destroy(Graphics& graphics, UI& ui) {
  SDL_DestroyRenderer(graphics.renderer);
  graphics.renderer = nullptr;

  SDL_DestroyWindow(graphics.window);
  graphics.window = nullptr;

  SDL_DestroyTexture(graphics.spritePng);
  graphics.spritePng = nullptr;

  TTF_CloseFont(ui.m_endUI.m_font);
  ui.m_endUI.m_font = nullptr;

  TTF_CloseFont(ui.m_menu.m_font);
  ui.m_menu.m_font = nullptr;

  TTF_Quit();
}
