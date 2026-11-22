#include "ball.h"
#include "collisionMng.h"
#include "player.h"
#include "text.h"

struct Update {
  void update(Ball& b, float deltaTime, AllBricks& bricks, CollisionMng& c, Player& p, PlayerState& pState);
  void updateText(TextHud& t, PlayerState& p);
};
