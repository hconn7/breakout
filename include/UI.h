#pragma once

#include "player.h"
#include "text.h"
#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>
struct MenuUI {
  SDL_FRect m_dstRectStart;
  SDL_FRect m_dstRectHScore;
  SDL_FRect m_dstRectBreakout;
  Text m_textBreakout;
  Text m_textStart;
  Text m_textHighScore;
  TTF_Font* m_font{nullptr};

  ~MenuUI() {
    if (m_font) {
      TTF_CloseFont(m_font);
    }
  }
};
struct EndUI {

  SDL_FRect m_replayDst;
  SDL_FRect m_scoreObtainedDst;
  Text m_textReplay;
  Text m_textScore;
  TTF_Font* m_font{nullptr};

  ~EndUI() {
    if (m_font) {
      TTF_CloseFont(m_font);
    }
  }
};
struct UI {
  MenuUI m_menu;
  EndUI m_endUI;

  ~UI() = default;
};

bool setUIMenu(UI& ui, Text& t, SDL_Renderer* renderer, PlayerState& p);

inline void setDestRectTxt(Text& t, float a, float b, float c, float d) {
  t.m_dst = SDL_FRect(a, b, c, d);
}
