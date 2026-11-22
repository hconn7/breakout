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

  if (!system.initSystem(graphics)) {
    return 0;
  }

  makeAllBricks(bricks);

  if (!system.initFont(text, textHud)) {
    return 1;
  }
  setTextDst(textHud);
  system.loadAudio(audio);
  system.loadSpritePng(graphics);

  Uint64 time = SDL_GetTicksNS();
  while (true) {

    Uint64 currentTime = SDL_GetTicksNS();
    float deltaTime = (currentTime - time) / 1000000000.0f;
    time = currentTime;

    if (handleInput(player, deltaTime)) {
      break;
    }
    update.update(ball, deltaTime, bricks, collision, player, playerState);
    update.updateText(textHud, playerState);
    SDL_RenderClear(graphics.renderer);
    render(graphics, player, ball, bricks, textHud);
    SDL_RenderPresent(graphics.renderer);
  }
  destroy(graphics);
}
