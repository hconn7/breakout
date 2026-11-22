#pragma once

#include "audio.h"
#include "graphics.h"

struct System {
  Audio m_audio{nullptr};
  Graphics m_graphics{nullptr};

  bool initSystem(Graphics& g);
  bool loadAudio(Audio& a);
  bool loadSpritePng(Graphics& a);
};
