#include "StateMng.h"
#include "UI.h"
#include "ball.h"
#include "brick.h"
#include "collisionMng.h"
#include "graphics.h"
#include "input.h"
#include "player.h"
#include "system.h"
#include "text.h"
#include "update.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

int main() {
  Graphics graphics{};
  Player player{};
  Ball ball{};
  AllBricks bricks{};
  CollisionMng collision{};
  Update update;
  System system;
  Audio audio;
  Text text;
  TextHud textHud;
  PlayerState playerState;
  StateMng stateMng;

  if (!system.initSystem(graphics)) {
    return 1;
  }

  makeAllBricks(bricks);

  if (!system.initFont(text, textHud)) {
    return 1;
  }

  setTextDst(textHud);
  system.loadAudio(audio);
  system.loadSpritePng(graphics);
  UI ui{};
  stateMng.m_currentState = StateMng::State::START;
  setUIMenu(ui, text, graphics.renderer, playerState);

  Uint64 time = SDL_GetTicksNS();
  while (true) {
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    SDL_RenderClear(graphics.renderer);
    Uint64 currentTime = SDL_GetTicksNS();
    float deltaTime = (currentTime - time) / 1000000000.0f;
    time = currentTime;

    if (handleInput(player, deltaTime)) {
      break;
    }

    SDL_RenderClear(graphics.renderer);
    switch (stateMng.m_currentState) {
    case StateMng::State::START:
      renderStartMenu(graphics, ui);
      break;
    case StateMng::State::LEVEL1:
      update.update(ball, deltaTime, bricks, collision, player, playerState);
      update.updateText(textHud, playerState);
      render(graphics, player, ball, bricks, textHud);
      break;
    }

    SDL_RenderPresent(graphics.renderer);
  }
  destroy(graphics, ui);
}
