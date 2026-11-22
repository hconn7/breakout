#include "update.h"
#include "ball.h"
#include "brick.h"
#include "collisionMng.h"
#include "player.h"

// namespace Update

void Update::update(Ball& b, float deltaTime, AllBricks& bricks, CollisionMng& c, Player& p) {
  //  SDL_Log("Ball X: %f\n", b.posX);
  // SDL_Log("Ball Y: %f\n", b.posY);
  c.collidedWithBrick(b, bricks);
  c.collidedWithPlayer(b, p);
  c.detectWallHitX(b);
  c.detectWallHitY(b);

  b.posX += b.speedX * deltaTime;
  b.posY += b.speedY * deltaTime;
}
