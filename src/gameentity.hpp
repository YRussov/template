#pragma once

#include "box2d.hpp"
#include "ray2d.hpp"

class GameEntity
{
public:

  virtual ~GameEntity() = default;

  virtual void Move() = 0;

protected:


};
