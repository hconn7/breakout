#include "update.h"
#include "StateMng.h"
#include "ball.h"
#include "brick.h"
#include "collisionMng.h"
#include "player.h"
#include <format>

void Update::update(Ball& b, float deltaTime, std::vector<Brick>& bricks, CollisionMng& c, Player& p, PlayerState& pState, StateMng& state) {
  //  SDL_Log("Ball X: %f\n", b.posX);
  // SDL_Log("Ball Y: %f\n", b.posY);
  if (pState.m_lives == 0) {
    if (pState.m_Highscore <= pState.m_score) {
      pState.m_Highscore = pState.m_score;
      writePlayerData(pState, pState.m_Highscore);
    }
    state.m_currentState = StateMng::State::END;
  }
  if (c.collidedWithBrick(b, bricks)) {
    pState.m_score += 10;
  }
  c.collidedWithPlayer(b, p);
  c.detectWallHitX(b);
  if (c.detectWallHitY(b)) {
    pState.m_lives -= 1;
  }
  if (allBricksDead(bricks)) {
    if (state.m_currentState == StateMng::State::LEVEL1) {
      state.m_currentState = StateMng::State::LEVEL2;
    } else if (state.m_currentState == StateMng::State::LEVEL2) {
      state.m_currentState = StateMng::State::LEVEL3;
    } else {
      state.m_currentState = StateMng::State::END;
    }
  }

  b.posX += b.speedX * deltaTime;
  b.posY += b.speedY * deltaTime;
}

void Update::updateText(TextHud& t, PlayerState& p) {

  t.m_score.m_string = std::format("Score: {}", p.m_score);
  std::string livesText;
  for (int i = 0; i < p.m_lives; i++) {
    livesText += "*";
  }
  t.m_lives.m_string = std::format("Lives: {}", livesText);
}
