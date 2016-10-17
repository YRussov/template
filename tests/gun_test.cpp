#include "gtest/gtest.h"
#include "gun.hpp"
#include <sstream>
#include <unordered_set>

TEST(gun_test, gun_construction)
{
  Gun gun1;
  EXPECT_EQ(gun1.GetAmmo(), 10);

  Gun gun2 = { 20 };
  EXPECT_EQ(gun2.GetAmmo(), 20);

  Gun gun3 = gun2;
  EXPECT_EQ(gun2, gun3);
}

TEST(gun_test, test_move_constructor)
{
  Gun gun1 = {15};
  Gun gun2 = {20};
  gun2 = std::move(gun1);
  EXPECT_EQ(gun2, 15);
  EXPECT_EQ(gun1, 20);

  Gun gun3(5);
  EXPECT_EQ(gun3, 5);
}

TEST(gun_test, test_shot)
{
  Gun gun1 = { 20 };
  gun1.Shot(Point2D{1.0f, 0.0f});
  EXPECT_EQ(gun1.GetAmmo(), 19);
}