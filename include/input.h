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

  bool update() {
    SDL_Event event{};
    SDL_zero(event);

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        quit = true;
        return quit;
      }
      if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
      }
      const bool* keys = SDL_GetKeyboardState(nullptr);
      if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
        std::cout << "You moved left";
      }
      if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        // player move
        std::cout << "You moved right";
      }
    }
    return false;
  }
};
