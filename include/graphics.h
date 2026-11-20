#pragma once

#include "player.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

struct Graphics {
  SDL_Renderer* renderer{nullptr};
  SDL_Window* window{nullptr};
  SDL_Texture* spritePng{nullptr};
};

bool init(Graphics& graphics);
void destroy(Graphics& graphics);
void render(Graphics& graphics, Player& player);
bool loadSpritePng(Graphics& graphics);
bool renderSpritePng(Graphics& graphics);
bool renderAllBick(Graphics& graphics);
bool renderPlayer(Graphics& graphics, Player& player);
