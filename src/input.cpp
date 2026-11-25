
#include "StateMng.h"
#include "UI.h"
#include "config.h"
#include "player.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <iostream>

bool handleInput(Player& p, PlayerState& ps, float deltaTime, UI& ui, SDL_Renderer* r, StateMng& state) {
  float speed{200.0f};

  bool quit{false};

  SDL_Event event{};
  SDL_zero(event);
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      quit = true;
      return quit;
    }

    Text& menuUI = ui.m_menu.m_textStart;
    Text& endUI = ui.m_endUI.m_textReplay;
    SDL_FPoint mousePos{event.motion.x, event.motion.y};
    SDL_ConvertEventToRenderCoordinates(r, &event);
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
      if (state.m_currentState == StateMng::State::START) {
        if (SDL_PointInRectFloat(&mousePos, &menuUI.m_dst)) {
          menuUI.isHovered = true;

        } else {
          menuUI.isHovered = false;
        }
      } else if (state.m_currentState == StateMng::State::END) {
        if (SDL_PointInRectFloat(&mousePos, &endUI.m_dst))
          endUI.isHovered = true;
        else {
          endUI.isHovered = false;
        }
      }
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
      SDL_FPoint clickPos{event.button.x, event.button.y};
      if (state.m_currentState == StateMng::State::START) {
        if (SDL_PointInRectFloat(&clickPos, &menuUI.m_dst)) {
          state.m_currentState = StateMng::State::LEVEL1;
        }
      } else if (state.m_currentState == StateMng::State::END) {
        if (SDL_PointInRectFloat(&clickPos, &endUI.m_dst)) {
          ps.m_lives = 3;
          ps.m_score = 0;
          state.m_currentState = StateMng::State::LEVEL1;
        }
      }
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
