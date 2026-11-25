#pragma once
#include <string>
struct Level {
  std::string m_lvl1;
  std::string m_lvl2;
  std::string m_lvl3;
};
bool writeLevelToBinary();

bool loadLevels(const char& lvl, Level& l);
