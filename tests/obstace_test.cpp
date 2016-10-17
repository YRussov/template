#include "obstacle.hpp"

#include "gtest/gtest.h"

TEST(obstacle_test, test_construction)
{
  Obstacle obstacle;

  EXPECT_EQ(obstacle1.GetObstacle(), Box2D(0.0f, 0.0f, 1.0f, 1.0f));
  EXPECT_EQ(obstacle.GetHealth(), 50.0);
}

TEST(obstacle_test, test_set)
{
  Obstacle obstacle;

  obstacle.SetHealth(30.0);
  EXPECT_EQ(obstacle.GetHealth(), 30.0);

  obstacle.SetObstacle(Point2D(50.0, 30.0), Point2D(100.0, 150.0));
  EXPECT_EQ(obstacle.GetObstacle(), Box2D(50.0, 30.0, 100.0, 150.0));
}
