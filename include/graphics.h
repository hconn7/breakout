#pragma once

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
};

bool initFont(Text& t, Graphics& g);
bool initGraphics(Graphics& graphics);
void destroy(Graphics& graphics);
void render(Graphics& graphics, Player& player, Ball& ball, AllBricks& allBricks, Text& t);
bool loadSpritePng(Graphics& graphics);
bool renderSpritePng(Graphics& graphics);
bool renderAllBricks(Graphics& graphics, AllBricks& b);
bool renderPlayer(Graphics& graphics, Player& player);
