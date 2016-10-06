#pragma once

#include <ostream>
#include <cmath>
#include "point2d.hpp"
#include "box2d.hpp"

class Matrix
{
public:
  Matrix() = default;
  Matrix(float m00, float m01, float m10, float m11)
    : m_m00(m00), m_m01(m01), m_m10(m10), m_m11(m11)
  {}
  float & m00() { return m_m00; }
  float & m01() { return m_m01; }
  float & m10() { return m_m10; }
  float & m11() { return m_m11; }

  Matrix & operator = (Matrix const & obj)
  {
    if (this == &obj) return *this;
    m_m00 = obj.m_m00;
    m_m01 = obj.m_m01;
    m_m10 = obj.m_m10;
    m_m11 = obj.m_m11;
    return *this;
  }

  float Det() const
  {
    return m_m00 * m_m11 - m_m01 * m_m10;
  }

  void ColumnReplace(float * replace, int column)
  {
    if (column == 0) { m_m00 = replace[0]; m_m10 = replace[1]; }
    if (column == 1) { m_m01 = replace[0]; m_m11 = replace[1]; }
  }
private:
  float m_m00 = 0.0f, m_m01 = 0.0f, m_m10 = 0.0f, m_m11 = 0.0f;
};

class Ray2D
{
public:
  Ray2D() = default;
  
  Ray2D(Point2D const & origin, Point2D const & direction);

  Ray2D(Ray2D const & obj);

  Ray2D(float f1, float f2, float f3, float f4);

  Point2D const & origin();
  
  Point2D const & direction();

  bool operator == (Ray2D const & obj) const;

  bool operator != (Ray2D const & obj) const;

  Point2D operator [] (unsigned int index) const;

  Ray2D & operator = (Ray2D const & obj);

  bool Intersection(Point2D a, Point2D b);

  bool operator % (Box2D & obj);

private:
  Point2D m_origin = { 0.0f, 0.0f }, m_direction = { 0.0f, 1.0f };
};