#pragma once

#include "UI.h"
#include "ball.h"
#include "brick.h"
#include "player.h"
#include "text.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <vector>

struct Graphics {
  SDL_Renderer* renderer{nullptr};
  SDL_Window* window{nullptr};
  SDL_Texture* spritePng{nullptr};

  Graphics() = default;

  ~Graphics() {
    if (spritePng) {
      SDL_DestroyTexture(spritePng);
    }
    if (renderer) {
      SDL_DestroyRenderer(renderer);
    }
    if (window) {
      SDL_DestroyWindow(window);
    }
  }

  Graphics(const Graphics&) = delete;

  Graphics& operator=(const Graphics&) = delete;
};

bool initFont(Text& t, Graphics& g);
bool initGraphics(Graphics& graphics);
void destroy(Graphics& graphics, UI& ui);
void render(Graphics& graphics, Player& player, Ball& ball, std::vector<Brick>&, TextHud& t);
bool loadSpritePng(Graphics& graphics);
bool renderSpritePng(Graphics& graphics);
bool renderAllBricks(Graphics& graphics, AllBricks& b);
bool renderPlayer(Graphics& graphics, Player& player);
bool renderStartMenu(Graphics& g, UI& ui);
bool renderEndScreen(SDL_Renderer* renderer, UI& ui);
