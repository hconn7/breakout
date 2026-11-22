
#include "system.h"
#include "config.h"
#include "graphics.h"
#include "text.h"
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_init.h>
#include <cstdio>
#include <cstdlib>

bool System::initSystem(Graphics& g) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    SDL_Log("Error loading Sub Systems %s", SDL_GetError());
    return false;
  }
  if (!SDL_CreateWindowAndRenderer("Breakout", 360, Config::screenHeight, 0, &g.window, &g.renderer)) {
    SDL_Log("Error init renderer and window%s", SDL_GetError());
    return false;
  }
  SDL_SetRenderVSync(g.renderer, 1);

  return true;
}
bool System::loadAudio(Audio& a) {
  char* wavPath{};
  SDL_AudioSpec spec;

  asprintf(&wavPath, "%s/assets/breakout_retro_song.wav", SDL_GetBasePath());

  if (!SDL_LoadWAV(wavPath, &spec, &a.wavData, &a.audioLength)) {
    SDL_Log("Couldn't load wav: %s", SDL_GetError());
    return false;
  }

  SDL_free(wavPath);

  a.m_audioStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
  {
    if (!a.m_audioStream) {
      SDL_Log("Couldn't load steam: %s", SDL_GetError());
      return false;
    }
  }
  SDL_PutAudioStreamData(a.m_audioStream, a.wavData, a.audioLength);
  SDL_SetAudioStreamGain(a.m_audioStream, 0.2f);
  SDL_ResumeAudioStreamDevice(a.m_audioStream);
  return true;
}
bool System::loadSpritePng(Graphics& g) {

  SDL_Surface* surface{nullptr};
  char* png_path = {nullptr};

  SDL_asprintf(&png_path, "%sassets/spritesheet-breakout_1.png", SDL_GetBasePath());
  surface = SDL_LoadPNG(png_path);
  SDL_SetRenderLogicalPresentation(g.renderer, 360, Config::screenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

  SDL_free(png_path);
  g.spritePng = SDL_CreateTextureFromSurface(g.renderer, surface);

  return true;
}
bool System::initFont(Text& t, TextHud& txtH) {
  char* fontPath{};
  if (!TTF_Init()) {
    SDL_Log("Couldn't init SDL_ttf: %s\n", SDL_GetError());
    return false;
  }
  asprintf(&fontPath, "%sassets/PressStart2P-Regular.ttf", SDL_GetBasePath());
  t.m_font = TTF_OpenFont(fontPath, 18.0f);
  free(fontPath);
  if (!t.m_font) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    return false;
  }
  txtH.m_lives.m_font = t.m_font;
  txtH.m_score.m_font = t.m_font;

  return true;
}
