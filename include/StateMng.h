struct StateMng {
  enum class State {
    START,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    GAMPEPLAY,
    END
  };

  State m_currentState;
};
