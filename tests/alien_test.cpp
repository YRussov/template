#include "alien.hpp"

#include "gtest/gtest.h"

TEST(alien_test, test_construction)
{
  Alien alien;
  EXPECT_EQ(alien.GetAlien(), Box2D(0.0f, 0.0f, 1.0f, 1.0f));
  EXPECT_EQ(alien.GetSpeed(), 1.0);
  EXPECT_EQ(alien.GetHealth(), 100.0);
}

TEST(alien_test, test_set)
{
  Alien alien;

  alien.SetAlien(Box2D(50.0, 30.0, 100.0, 150.0));
  EXPECT_EQ(alien.GetAlien(), Box2D(50.0, 30.0, 100.0, 150.0));

  alien.SetHealth(50.0);
  EXPECT_EQ(alien.GetHealth(), 50.0);

  alien.SetSpeed(100.0);
  EXPECT_EQ(alien.GetSpeed(), 100.0);
}

TEST(alien_test, test_health)
{
  Alien alien;

  alien.Damage(80);
  EXPECT_EQ(alien.GetHealth(), 20);
}
