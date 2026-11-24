#include "text.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

void setTextDst(TextHud& t) {
  t.m_score.m_dst = {10, 20, 30, 30};
  t.m_lives.m_dst = {200, 20, 30, 30};
}

bool createTextTexture(Text& t, SDL_Renderer* r) {
  SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};
  SDL_Surface* textSurface = TTF_RenderText_Blended(t.m_font, t.m_string.c_str(), t.m_length, color);
  if (textSurface) {
    t.m_textTexture = SDL_CreateTextureFromSurface(r, textSurface);
    t.m_dst.w = static_cast<float>(textSurface->w);
    t.m_dst.h = static_cast<float>(textSurface->h);
    SDL_DestroySurface(textSurface);
  }
  if (!t.m_textTexture) {
    SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    return false;
  }
  return true;
}
