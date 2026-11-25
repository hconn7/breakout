#pragma once

#include "ball.h"
#include "brick.h"
#include "player.h"
#include <span>

class CollisionMng {
public:
  bool collidedWithBrick(Ball& ball, std::vector<Brick>& brick);
  void collidedWithPlayer(Ball& ball, Player& player);
  bool detectWallHitX(Ball& b);
  bool detectWallHitY(Ball& b);
}; // namespace CollisionMng
