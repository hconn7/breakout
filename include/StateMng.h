#pragma once
struct StateMng {
  enum class State {
    START,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    END,
    MAX_LEVELS
  };

  State m_currentState;
};
