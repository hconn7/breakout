#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_stdinc.h>

struct Audio {
  SDL_AudioStream* m_audioStream;
  Uint8* wavData{nullptr};
  Uint32 audioLength{0};

  ~Audio() {
    if (m_audioStream) {
      SDL_DestroyAudioStream(m_audioStream);
    }

    if (wavData) {
      wavData = nullptr;
    }
  };
};
