#include "gtest/gtest.h"
#include "ray2d.hpp"
#include "box2d.hpp"

TEST(ray2d_test, test_construction)
{
  Ray2D Ob1;
  Point2D t1 = { 0.0f, 0.0f }, t2 = { 0.0f, 1.0f };
  EXPECT_EQ(Ob.origin(),t1);
  EXPECT_EQ(Ob.direction(),t2);

  Point2D t3 = { 1.0f, 2.0f }, t4 = { 6.0f, 4.0f };
  Ray2D Ob2(t3,t4);
  EXPECT_EQ(Ob2.origin(), t3);
  EXPECT_EQ(Ob2.direction(), t4);

  Ray2D Ob3(Ob2);
  EXPECT_EQ(Ob3,Ob2);

  Ray2D Ob4(1.0f,4.0f,2.0f,5.0f);
  Point2D t5 = { 1.0f, 4.0f }, t6 = { 2.0f, 5.0f };
  EXPECT_EQ(Ob4.origin(), t5);
  EXPECT_EQ(Ob4.direction(), t6);
}

TEST(ray2d_test, test_equality)
{
  Ray2D Ob5 = { 1.0f, 3.0f, 5.0f, 10.0f };
  Point2D t7 = { 1.0f, 3.0f }, t8 = { 5.0f, 10.0f };
  Ray2D Ob6 = { t7, t8 };
  EXPECT_EQ(Ob5, Ob6);
}

TEST(ray2d_test, test_non_equality)
{
  Ray2D Ob7 = { 1.0f, 3.0f, 5.0f, 10.0f };
  Point2D t9 = { 1.0f, 3.0f }, t10 = { 5.0f, 10.0f };
  Ray2D Ob8 = { t9, t10 };
  EXPECT_NE(Ob7, Ob8);
}

TEST(ray2d_test, test_square_brackets)
{
  Ray2D Ob9 = { 1.0f, 3.0f, 5.0f, 10.0f };
  Point2D t11 = { 1.0f, 3.0f }, t12 = { 5.0f, 10.0f }, t13;
  EXPECT_EQ(Ob9[0], t11);
  EXPECT_EQ(Ob9[1], t12);
  EXPECT_EQ(Ob9[2], t13);
}

TEST(ray2d_test, test_Intersection_segment)
{
  Ray2D Ob10 = { 2.0f, 6.0f, 6.0f, 5.0f };
  
  Point2D q1 = { 7.0f, 1.0f }, q2 = { 10.0f, 10.0f },
          q3 = { 1.0f, 1.0f }, q4 = { 100.0f, 4.0f },
          q5 = { -1.0f, -1.0f }, q6 = { -2.0f, -2.0f },
          q7 = { 1.0f, 1.0f }, q8 = { -2.0f, 7.0f };
		  
  EXPECT_EQ(Ob10.Intersection(q1, q2),true);
  EXPECT_EQ(Ob10.Intersection(q3, q4),true);
  EXPECT_EQ(Ob10.Intersection(q5, q6),false);
  EXPECT_EQ(Ob10.Intersection(q7, q8),false);
}

TEST(ray2d_test, test_Intersection_box2d)
{
  Ray2D Ob11 = { -3.0f, -4.0f, 2.0f, 3.0f };
  
  Box2D qt1 = { -1.0f, -1.0f, 4.0f, 2.0f },
        qt2 = { -5.0f, 1.0f, -3.0f, 2.0f },
        qt3 = { 2.0f, -4.0f, 5.0f, -1.0f },
		qt3 = { -1.0f, -2.0f, 10.0f, 10.0f };
		
  EXPECT_EQ( Ob11 % qt1 ,true);
  EXPECT_EQ( Ob11 % qt2 ,false);
  EXPECT_EQ( Ob11 % qt3 ,false);
  EXPECT_EQ( Ob11 % qt4 ,true);
}