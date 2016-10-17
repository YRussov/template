#include "space.hpp"
#include "box2d.hpp"
#include "obstacle.hpp"
#include "point2d.hpp"

#include "gtest/gtest.h"

TEST(space_test, test_constructor)
{
  Space space;
  EXPECT_EQ(space.x_Size(), 90.0f);
  EXPECT_EQ(space.y_Size(), 90.0f);
}
