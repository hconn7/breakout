
#include "config.h"
#include "player.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <iostream>

bool update(Player& p, Uint64& time) {
  float speed{200.0f};

  bool quit{false};

  SDL_Event event{};
  SDL_zero(event);
  Uint64 currentTime = SDL_GetTicksNS();
  float deltaTime = (currentTime - time) / 1000000000.0f;
  time = currentTime;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      quit = true;
      return quit;
    }
  }
  if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
  }
  const bool* keys = SDL_GetKeyboardState(nullptr);
  if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
    if (p.posX > 0) {
      p.posX -= speed * deltaTime;
    }
  if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
    if (p.posX + 54 < 360) {
      p.posX += speed * deltaTime;
    }

  return false;
}
