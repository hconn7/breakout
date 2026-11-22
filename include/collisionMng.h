#pragma once

#include "ball.h"
#include "brick.h"
#include "player.h"

class CollisionMng {
public:
  bool collidedWithBrick(Ball& ball, AllBricks& brick);
  void collidedWithPlayer(Ball& ball, Player& player);
  bool detectWallHitX(Ball& b);
  bool detectWallHitY(Ball& b);
}; // namespace CollisionMng
