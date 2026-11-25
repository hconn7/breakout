
#include "levelDat.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <cassert>
#include <iostream>
#include <string>

const char*
    levels{

        "12"
        "OOOOOOOOOO"
        "YYYYYYYYYY"
        "*"
        "24"
        "OOOOOOOOOO"
        "YYYYYYYYYY"
        "PPPPPPPPPP"
        "BBBBBBBBBB"
        "*"
        "36"
        "OOOOOOOOOO"
        "YYYYYYYYYY"
        "PPPPPPPPPP"
        "BBBBBBBBBB"
        "GGGGGGGGGG"
        "RRRRRRRRRR"
        "*"};

bool writeLevelToBinary() {
  std::string levelPath = std::string(SDL_GetBasePath()) + "levelDat/levelData.bin";

  SDL_IOStream* file = SDL_IOFromFile(levelPath.c_str(), "wb");
  if (!file) {
    SDL_Log("couldn't load file %s", SDL_GetError());
    return false;
  }
  size_t written = SDL_WriteIO(file, levels, SDL_strlen(levels));
  SDL_CloseIO(file);
  return written == SDL_strlen(levels);
}

bool loadLevels(const char& lvl, Level& l) {
  std::string levelPath = std::string(SDL_GetBasePath()) + "levelDat/levelData.bin";
  size_t fileSize{};
  char* data = static_cast<char*>(SDL_LoadFile(levelPath.c_str(), &fileSize));

  if (!data) {
    SDL_Log("couldn't load file for read: %s", SDL_GetError());
    return false;
  }

  std::string levelData(data, fileSize);
  std::string levelData1;
  std::string levelData2;
  std::string levelData3;
  for (size_t c = 0; c < levelData.size(); c++) {
    std::cout << levelData[c] << '\n';
    if (levelData[c] == '1') {
      while (levelData[c] != '*') {
        levelData1 += levelData[c];
        c++;
      }
    } else if (levelData[c] == '2') {
      SDL_Log("2 FOUND\n");
      while (levelData[c] != '*') {
        SDL_Log("ADDING %c IN LEVELDATA 2 \n", levelData[c]);
        levelData2 += levelData[c];
        c++;
      }
    } else if (levelData[c] == '3') {
      SDL_Log("3 FOUND\n");
      SDL_Log("AT SECOND LEVEL LOAD %c\n", levelData[c]);
      while (levelData[c] != '*') {
        levelData3 += levelData[c];
        c++;
      }
    }
  }

  SDL_free(data);
  l.m_lvl1 = std::move(levelData1);
  l.m_lvl2 = std::move(levelData2);
  l.m_lvl3 = std::move(levelData3);

  assert(l.m_lvl1.size() != 0);
  assert(l.m_lvl2.size() != 0);
  assert(l.m_lvl3.size() != 0);
  return true;
}
