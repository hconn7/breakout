#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

struct Text {
  TTF_Font* m_font{nullptr};
  int m_length{};
  SDL_Texture* m_textTexture{nullptr};
  std::string m_string;
  SDL_FRect m_dst;
  bool isHovered{false};

  ~Text() = default;
};

struct TextHud {
  Text m_score{};
  Text m_lives{};
  int m_length{2};
};

void setTextDst(TextHud& t);
bool createTextTexture(Text& t, SDL_Renderer* r);
