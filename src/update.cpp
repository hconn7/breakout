#include "update.h"
#include "ball.h"
#include "brick.h"
#include "collisionMng.h"
#include "player.h"
#include <format>

void Update::update(Ball& b, float deltaTime, AllBricks& bricks, CollisionMng& c, Player& p, PlayerState& pState) {
  //  SDL_Log("Ball X: %f\n", b.posX);
  // SDL_Log("Ball Y: %f\n", b.posY);
  if (c.collidedWithBrick(b, bricks)) {
    pState.m_score += 10;
  }
  c.collidedWithPlayer(b, p);
  c.detectWallHitX(b);
  if (c.detectWallHitY(b)) {
    pState.m_lives -= 1;
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
