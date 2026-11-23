#pragma once

#include "audio.h"
#include "graphics.h"
#include "text.h"

struct System {
  Audio m_audio{nullptr};
  Graphics m_graphics{};

  bool initSystem(Graphics& g);
  bool loadAudio(Audio& a);
  bool loadSpritePng(Graphics& a);
  bool initFont(Text& t, TextHud& txtH);
};
