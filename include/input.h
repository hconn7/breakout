#pragma once

#include "player.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <iostream>
struct Input {
  bool up{false};
  bool down{false};
  bool left{false};
  bool right{false};
  bool quit{false};
};

bool update(Player& p, Uint64& time);
