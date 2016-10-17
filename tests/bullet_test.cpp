#include "gtest/gtest.h"
#include "bullet.hpp"
#include <sstream>
#include <unordered_set>

TEST(bullet_test, bullet_construction)
{
  Bullet bullet1;
  EXPECT_EQ(bullet1.GetPosition(), Box2D(Point2D{ 0.0f, 0.0f }, Point2D{ 1.0f, 1.0f }));
  EXPECT_EQ(bullet1.GetOrigin(), Point2D( 0.0f, 0.0f ));
  EXPECT_EQ(bullet1.GetDirection(), Point2D( 1.0f, 0.0f ));

  Bullet bullet2 = { Point2D (5.0f, 5.0f), Point2D (1.0f, 0.0f) };
  EXPECT_EQ(bullet2.GetPosition(), Box2D(Point2D{ 4.5f, 4.5f }, Point2D{ 5.5f, 5.5f }));
  EXPECT_EQ(bullet2.GetOrigin(), Point2D(5.0f, 5.0f));
  EXPECT_EQ(bullet2.GetDirection(), Point2D(1.0f, 0.0f));

}
