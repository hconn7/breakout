#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <string>
struct Text {
  TTF_Font* m_font{nullptr};
  size_t m_text{};
  int m_length{};
  SDL_Texture* m_textTexture{nullptr};

  ~Text() = default;
};
