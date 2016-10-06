#include "gtest/gtest.h"
#include "box2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(box2d_test, test_construction)
{
	Box2D b1;
	Point2D p1 = { 0.0f, 0.0f };
	Point2D p2 = { 0.0f, 0.0f };
	EXPECT_EQ(b1.min(), p1);
	EXPECT_EQ(b1.max(), p2);

	Point2D p3 = { 1.2f, 2.4f };
	Point2D p4 = { 3.6f, 4.8f };
	Box2D b2 = {p3, p4};
	EXPECT_EQ(b2.min(), p3);
	EXPECT_EQ(b2.max(), p4);
	Box2D b3 = b2;
	EXPECT_EQ(b2, b3);
}

TEST(box2d_test, test_initializer_list)
{
	Box2D b1 = { 1.0f, 2.0f, 3.0f , 4.0f, 5.0f, 6.0f };
	Point2D p1 = { 1.0f, 2.0f };
	Point2D p2 = { 3.0f, 4.0f };
	EXPECT_EQ(b1.min(), p1);
	EXPECT_EQ(b1.max(), p2);
	Box2D b2 = { 1.0f, 2.0f };
	Point2D p3 = { 1.0f, 2.0f };
	Point2D p4 = { 0.0f, 0.0f };
	EXPECT_EQ(b2.min(), p4);
	EXPECT_EQ(b2.max(), p3);
}

TEST(box2d_test, test_assignment)
{
	Point2D p1 = { 1.2f, 2.3f };
	Point2D p2 = { 3.4f, 4.5f };
	Box2D b1;
	b1 = { p1, p2 };
	EXPECT_EQ(b1, Box2D(p1, p2));
}

TEST(box2d_test, test_move)
{
	Point2D p1 = { 1.0f, 1.0f };
	Point2D p2 = { 5.0f, 3.0f };
	Box2D b1 = { p1, p2 };
	Point2D vect = { 2.5f, 3.5f };
	Point2D p3 = { 3.5f, 4.5f };
	Point2D p4 = { 7.5f, 6.5f };
	b1.Move(vect);
	EXPECT_EQ(b1, Box2D(p3, p4));
}

TEST(box2d_test, test_center)
{
	Point2D p1 = { 1.0f, 1.0f };
	Point2D p2 = { 5.0f, 3.0f };
	Point2D p3 = { 3.0f, 2.0f };
	Box2D b1 = { p1, p2 };
	EXPECT_EQ(b1.Center(), p3);
}

TEST(box2d_test, test_vertex)
{
	Point2D p1 = { 1.0f, 1.0f };
	Point2D p2 = { 5.0f, 3.0f };
	Box2D b1 = { p1, p2 };
	Point2D p3 = { 1.0f, 3.0f };
	Point2D p4 = { 5.0f, 1.0f };
	EXPECT_EQ(b1.vertexLT(), p3);
	EXPECT_EQ(b1.vertexRB(), p4);

}

TEST(Box2D_test, test_Intersection)
{
	Box2D b1 = { Point2D(0.0f, 0.0f), Point2D(4.0f, 2.0f) };
	Box2D b2 = { Point2D(2.0f, 1.0f), Point2D(6.0f, 3.0f) };
	EXPECT_EQ(Intersection(b1, b2), true);
	b2.Move(Point2D(2.0f, 1.0f));
	EXPECT_EQ(Intersection(b1, b2), false);
	b2.Move(Point2D(1.0f, 1.0f));
	EXPECT_EQ(Intersection(b1, b2), false);
}