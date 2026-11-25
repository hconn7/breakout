#include "StateMng.h"
#include "ball.h"
#include "collisionMng.h"
#include "player.h"
#include "text.h"

struct Update {
  void updateText(TextHud& t, PlayerState& p);
  void update(Ball& b, float deltaTime, std::vector<Brick>& bricks, CollisionMng& c, Player& p, PlayerState& pState, StateMng& state);
};
