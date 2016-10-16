#include "gtest/gtest.h"
#include "ray2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(ray2d_test, test_construction)
{
  Ray2D r1;
  EXPECT_EQ(r1.origin(), Point2D(0.0f, 0.0f));
  EXPECT_EQ(r1.direction(), Point2D(0.0f, 1.0f));

  Ray2D r2 = { Point2D(1.0f, 2.0f), Point2D(1.0f, 0.0f) };
  EXPECT_EQ(r2.origin(), Point2D(1.0f, 2.0f));
  EXPECT_EQ(r2.direction(), Point2D(1.0f, 0.0f));

  Ray2D r3 = r2;
  EXPECT_EQ(r2, r3);
}

TEST(ray2d_test, test_initializer_list_float)
{
  Ray2D r1 = { 1.0f, 2.0f, 1.0f, 0.0f, 5.0f, 6.0f };
  EXPECT_EQ(r1.origin(), Point2D(1.0f, 2.0f));
  EXPECT_EQ(r1.direction(), Point2D(1.0f, 0.0f));
}

TEST(ray2d_test, test_initializer_list_Point2D)
{
  Ray2D r1 = { Point2D(1.0f, 2.0f), Point2D(1.0f, 0.0f) };
  EXPECT_EQ(r1.origin(), Point2D(1.0f, 2.0f));
  EXPECT_EQ(r1.direction(), Point2D(1.0f, 0.0f));
}

TEST(ray2d_test, test_move_constructor)
{
  Ray2D r1 = { Point2D(1.0f, 1.0f), Point2D(1.0f, 0.0f) };
  Ray2D r2 = { Point2D(0.0f, 0.0f), Point2D(0.0f, 1.0f) };
  r2 = std::move(r1);
  EXPECT_EQ(r2, Ray2D(Point2D(1.0f, 1.0f), Point2D(1.0f, 0.0f)));
  EXPECT_EQ(r1, Ray2D(Point2D(0.0f, 0.0f), Point2D(0.0f, 1.0f)));

  Ray2D r3(Ray2D(Point2D(1.0f, 1.0f), Point2D(1.0f, 0.0f)));
  EXPECT_EQ(r3, Ray2D(Point2D(1.0f, 1.0f), Point2D(1.0f, 0.0f)));
}

TEST(ray2d_test, test_assignment)
{
  Ray2D r1;
  r1 = { Point2D(1.2f, 2.3f), Point2D(3.4f, 4.5f) };
  EXPECT_EQ(r1, Ray2D(Point2D(1.2f, 2.3f), Point2D(3.4f, 4.5f)));
}

TEST(ray2d_test, test_move)
{
  Ray2D r1 = { Point2D(1.0f, 1.0f), Point2D(1.0f, 0.0f) };
  Point2D vect = { 3.0f, 2.0f };
  r1.Move(vect);
  EXPECT_EQ(r1, Ray2D(Point2D(4.0f, 3.0f), Point2D(1.0f, 0.0f)));
}

TEST(ray2D_test, test_Intersection)
{
  Ray2D r1 = { Point2D(2.0f, 1.0f), Point2D(1.0f, 1.0f) };
  Box2D b1 = { Point2D(3.0f, 3.0f), Point2D(5.0f, 5.0f) };
  EXPECT_EQ(Intersection(b1, r1), true);
  Ray2D r2 = { Point2D(2.0f, 1.0f), Point2D(3.0f, 1.0f) };
  EXPECT_EQ(Intersection(b1, r2), false);
  Ray2D r3 = { Point2D(2.0f, 1.0f), Point2D(1.0f, 5.0f) };
  EXPECT_EQ(Intersection(b1, r3), false);
}