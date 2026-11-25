#include "player.h"
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <cassert>
#include <iostream>
#include <iterator>
#include <string>

bool writePlayerData(PlayerState& p, int score) {
  std::string playerDat = std::string(SDL_GetBasePath()) + "playerDat/playerDat.bin";
  SDL_IOStream* file = SDL_IOFromFile(playerDat.c_str(), "w+b");
  if (!file) {
    SDL_Log("Player Data File Not Opened: %s", SDL_GetError());
    return false;
  }

  size_t written = SDL_WriteIO(file, &p.m_score, sizeof(score));
  SDL_CloseIO(file);
  if (written != sizeof(p.m_Highscore)) {
    SDL_Log("Failed to write complete player data: %s", SDL_GetError());
    return false;
  }
  p.m_Highscore = score;
  return true;
}

bool readPlayerData(PlayerState& p) {
  std::string playerDat = std::string(SDL_GetBasePath()) + "playerDat/playerDat.bin";

  SDL_IOStream* file = SDL_IOFromFile(playerDat.c_str(), "r+b");
  if (!file) {
    SDL_Log("Player Data File Not Opened to Write: %s", SDL_GetError());
    return false;
  }
  Sint64 totalSize = SDL_GetIOSize(file);
  if (totalSize < static_cast<Sint64>(sizeof(Sint32))) {
    SDL_CloseIO(file);
    return false;
  }

  Sint32 score = 0;
  SDL_ReadS32LE(file, &score);
  p.m_Highscore = score;
  return true;
}
