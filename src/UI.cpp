#include "UI.h"
#include "config.h"
#include "player.h"
#include "text.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>

bool setUIMenu(UI& ui, Text& t, SDL_Renderer* renderer, PlayerState& p) {

  MenuUI menuUI{};
  EndUI endUI{};
  // SET FONTS
  menuUI.m_textBreakout.m_font = t.m_font;
  menuUI.m_textHighScore.m_font = t.m_font;
  menuUI.m_textStart.m_font = t.m_font;

  endUI.m_textReplay.m_font = t.m_font;
  endUI.m_textScore.m_font = t.m_font;
  // SET STRINGS
  menuUI.m_textBreakout.m_string = "Breakout";
  menuUI.m_textStart.m_string = "Start Game";
  menuUI.m_textHighScore.m_string = "High Score: " + std::to_string(p.m_score);

  endUI.m_textScore.m_string = "High Score";
  endUI.m_textReplay.m_string = "Replay";

  // GIVE TO CPU
  if (!createTextTexture(menuUI.m_textStart, renderer)) {
    SDL_Log("Couldn't create texture: %s", SDL_GetError());
    return false;
  }
  if (!createTextTexture(menuUI.m_textHighScore, renderer)) {
    SDL_Log("Couldn't create texture: %s", SDL_GetError());
    return false;
  }
  if (!createTextTexture(menuUI.m_textBreakout, renderer)) {
    SDL_Log("Couldn't create texture: %s", SDL_GetError());
    return false;
  }

  if (!createTextTexture(endUI.m_textScore, renderer)) {
    SDL_Log("Couldn't create texture: %s", SDL_GetError());
    return false;
  }
  if (!createTextTexture(endUI.m_textReplay, renderer)) {
    SDL_Log("Couldn't create texture: %s", SDL_GetError());
    return false;
  }

  // SET DISPLAY RECT
  setDestRectTxt(menuUI.m_textStart, 100, 300, menuUI.m_textStart.m_dst.w, menuUI.m_textStart.m_dst.h);
  setDestRectTxt(menuUI.m_textHighScore, 180, 400, menuUI.m_textHighScore.m_dst.w, menuUI.m_textHighScore.m_dst.h);
  setDestRectTxt(menuUI.m_textBreakout, 180, 200, menuUI.m_textBreakout.m_dst.w, menuUI.m_textBreakout.m_dst.h);

  setDestRectTxt(endUI.m_textReplay, 100, 100, 0, 0);
  setDestRectTxt(endUI.m_textScore, 300, 100, 100, 100);
  // GET TEXTURE WIDTH/HEIGHT

  Text& highScore = ui.m_menu.m_textHighScore;

  Text& start = ui.m_menu.m_textStart;
  Text& breakout = ui.m_menu.m_textBreakout;

  SDL_GetTextureSize(highScore.m_textTexture, &highScore.m_dst.w, &highScore.m_dst.h);
  SDL_GetTextureSize(start.m_textTexture, &start.m_dst.w, &start.m_dst.h);
  SDL_GetTextureSize(breakout.m_textTexture, &breakout.m_dst.w, &breakout.m_dst.h);

  // SCALE UI
  float floatScaleMainBreakout = 2.0f;
  float floatScaleStart = 1.3f;
  float floatScaleScore = 1.2f;

  menuUI.m_textBreakout.m_dst.w *= floatScaleMainBreakout;
  menuUI.m_textBreakout.m_dst.h *= floatScaleMainBreakout;

  menuUI.m_textStart.m_dst.w *= floatScaleStart;
  menuUI.m_textStart.m_dst.h *= floatScaleStart;

  menuUI.m_textHighScore.m_dst.w *= floatScaleScore;
  menuUI.m_textHighScore.m_dst.h *= floatScaleScore;

  menuUI.m_textBreakout.m_dst.x = (Config::screenWidth - menuUI.m_textBreakout.m_dst.w) / 2.0f;
  menuUI.m_textBreakout.m_dst.y = (Config::screenHeight - menuUI.m_textBreakout.m_dst.h) / 2.0f - 130;

  menuUI.m_textStart.m_dst.x = (Config::screenWidth - menuUI.m_textStart.m_dst.w) / 2.0f;
  menuUI.m_textStart.m_dst.y = ((Config::screenHeight - menuUI.m_textStart.m_dst.h) / 2.0f);

  menuUI.m_textHighScore.m_dst.x = (Config::screenWidth - menuUI.m_textHighScore.m_dst.w) / 2.0f;
  menuUI.m_textHighScore.m_dst.y = ((Config::screenHeight - menuUI.m_textHighScore.m_dst.h) / 2.0f) + 130;
  //
  // ASSIGN TO META UI
  ui.m_endUI = endUI;
  ui.m_menu = menuUI;
  return true;
}
