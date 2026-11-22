#include "ball.h"
#include "collisionMng.h"
#include "player.h"

struct Update {
  void update(Ball& b, float deltaTime, AllBricks& bricks, CollisionMng& c, Player& p);
};
