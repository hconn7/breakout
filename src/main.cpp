#include "StateMng.h"
#include "UI.h"
#include "ball.h"
#include "brick.h"
#include "collisionMng.h"
#include "graphics.h"
#include "input.h"
#include "levelDat.h"
#include "player.h"
#include "system.h"
#include "text.h"
#include "update.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <cassert>

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
  Level level;

  readPlayerData(playerState);
  if (!system.initSystem(graphics)) {
    return 1;
  }

  loadLevels('1', level);
  loadLevels('2', level);
  loadLevels('3', level);
  loadBricks(bricks, level.m_lvl1);
  loadBricks(bricks, level.m_lvl2);
  loadBricks(bricks, level.m_lvl3);
  assert(bricks.m_allBrickslvl2.size() != 0);
  assert(bricks.m_allBrickslvl3.size() != 0);

  if (!system.initFont(text, textHud)) {
    return 1;
  }
  readPlayerData(playerState);
  writeLevelToBinary();
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

    if (handleInput(player, playerState, deltaTime, ui, graphics.renderer, stateMng)) {
      break;
    }

    SDL_RenderClear(graphics.renderer);
    switch (stateMng.m_currentState) {
    case StateMng::State::START:
      renderStartMenu(graphics, ui);
      break;
    case StateMng::State::LEVEL1:
      update.update(ball, deltaTime, bricks.m_allBrickslvl1, collision, player, playerState, stateMng);
      update.updateText(textHud, playerState);
      render(graphics, player, ball, bricks.m_allBrickslvl1, textHud);
      break;
    case StateMng::State::LEVEL2:
      update.update(ball, deltaTime, bricks.m_allBrickslvl2, collision, player, playerState, stateMng);
      update.updateText(textHud, playerState);
      render(graphics, player, ball, bricks.m_allBrickslvl2, textHud);
      break;
    case StateMng::State::LEVEL3:
      update.update(ball, deltaTime, bricks.m_allBrickslvl3, collision, player, playerState, stateMng);
      update.updateText(textHud, playerState);
      render(graphics, player, ball, bricks.m_allBrickslvl3, textHud);
      break;
    case StateMng::State::END:
      renderEndScreen(graphics.renderer, ui);
      setUIMenu(ui, text, graphics.renderer, playerState);

      break;
    }

    SDL_RenderPresent(graphics.renderer);
  }
  destroy(graphics, ui);
}
