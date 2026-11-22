#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_stdinc.h>

struct Audio {
  SDL_AudioStream* m_audioStream;
  Uint8* wavData{nullptr};
  Uint32 audioLength{0};
};
