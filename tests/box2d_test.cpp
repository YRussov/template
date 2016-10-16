#include "gtest/gtest.h"
#include "box2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(box2d_test, test_construction)
{
  Box2D b1;
  EXPECT_EQ(b1.boxMin(), Point2D(0.0f, 0.0f));
  EXPECT_EQ(b1.boxMax(), Point2D(0.0f, 0.0f));

  Box2D b2 = { Point2D(1.2f, 2.4f), Point2D(3.6f, 4.8f) };
  EXPECT_EQ(b2.boxMin(), Point2D(1.2f, 2.4f));
  EXPECT_EQ(b2.boxMax(), Point2D(3.6f, 4.8f));

  Box2D b3 = b2;
  EXPECT_EQ(b2, b3);
}

TEST(box2d_test, test_initializer_list_float)
{
  Box2D b1 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
  EXPECT_EQ(b1.boxMin(), Point2D(1.0f, 2.0f));
  EXPECT_EQ(b1.boxMax(), Point2D(3.0f, 4.0f));

  Box2D b2 = { 1.0f, 2.0f };
  EXPECT_EQ(b2.boxMin(), Point2D(0.0f, 0.0f));
  EXPECT_EQ(b2.boxMax(), Point2D(1.0f, 2.0f));

  Box2D b3 = { 1.0f, 2.0f, 3.0f };
  EXPECT_EQ(b3.boxMin(), Point2D(1.0f, 0.0f));
  EXPECT_EQ(b3.boxMax(), Point2D(3.0f, 2.0f));
}

TEST(box2d_test, test_initializer_list_Point2D)
{
  Box2D b1 = { Point2D(1.0f, 2.0f), Point2D(3.0f, 4.0f) };
  EXPECT_EQ(b1.boxMin(), Point2D(1.0f, 2.0f));
  EXPECT_EQ(b1.boxMax(), Point2D(3.0f, 4.0f));

  Box2D b2 = { Point2D(1.0f, 2.0f) };
  EXPECT_EQ(b2.boxMin(), Point2D(0.0f, 0.0f));
  EXPECT_EQ(b2.boxMax(), Point2D(1.0f, 2.0f));
}

TEST(box2d_test, test_move_constructor)
{
  Box2D b1 = { Point2D(1.0f, 1.0f), Point2D(5.0f, 3.0f) };
  Box2D b2 = { Point2D(0.0f, 0.0f), Point2D(4.0f, 4.0f) };
  b2 = std::move(b1);
  EXPECT_EQ(b2, Box2D(Point2D(1.0f, 1.0f), Point2D(5.0f, 3.0f)));
  EXPECT_EQ(b1, Box2D(Point2D(0.0f, 0.0f), Point2D(4.0f, 4.0f)));

  Box2D b3(Box2D(Point2D(1.0f, 1.0f), Point2D(5.0f, 3.0f)));
  EXPECT_EQ(b3, Box2D(Point2D(1.0f, 1.0f), Point2D(5.0f, 3.0f)));
}

TEST(box2d_test, test_assignment)
{
  Box2D b1;
  b1 = { Point2D(1.2f, 2.3f), Point2D(3.4f, 4.5f) };
  EXPECT_EQ(b1, Box2D(Point2D(1.2f, 2.3f), Point2D(3.4f, 4.5f)));
}

TEST(box2d_test, test_move)
{
  Box2D b1 = { Point2D(1.0f, 1.0f), Point2D(5.0f, 3.0f) };
  Point2D vect = { 2.5f, 3.5f };
  b1.Move(vect);
  EXPECT_EQ(b1, Box2D(Point2D(3.5f, 4.5f), Point2D(7.5f, 6.5f)));
}

TEST(box2d_test, test_center)
{
  Box2D b1 = { Point2D(1.0f, 1.0f), Point2D(5.0f, 3.0f) };
  EXPECT_EQ(b1.Center(), Point2D(3.0f, 2.0f));
}

TEST(box2d_test, test_vertex)
{
  Box2D b1 = { Point2D(1.0f, 1.0f), Point2D(5.0f, 3.0f) };
  EXPECT_EQ(b1.vertexLT(), Point2D(1.0f, 3.0f));
  EXPECT_EQ(b1.vertexRB(), Point2D(5.0f, 1.0f));
}

TEST(box2d_test, test_Intersection_1)
{
  Box2D b1 = { Point2D(0.0f, 0.0f), Point2D(4.0f, 2.0f) };
  EXPECT_EQ(b1.Intersection(Point2D(2.0f, 1.0f), Point2D(6.0f, 3.0f)), true);
  EXPECT_EQ(b1.Intersection(Point2D(4.0f, 2.0f), Point2D(8.0f, 4.0f)), false);
  EXPECT_EQ(b1.Intersection(Point2D(5.0f, 3.0f), Point2D(9.0f, 5.0f)), false);
}

TEST(Box2D_test, test_Intersection_2)
{
  Box2D b1 = { Point2D(0.0f, 0.0f), Point2D(4.0f, 2.0f) };
  Box2D b2 = { Point2D(2.0f, 1.0f), Point2D(6.0f, 3.0f) };
  EXPECT_EQ(Intersection(b1, b2), true);
  b2.Move(Point2D(2.0f, 1.0f));
  EXPECT_EQ(Intersection(b1, b2), false);
  b2.Move(Point2D(1.0f, 1.0f));
  EXPECT_EQ(Intersection(b1, b2), false);
}