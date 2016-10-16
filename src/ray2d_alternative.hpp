#pragma once

#include <ostream>
#include <initializer_list>
#include <cmath>
#include "point2d.hpp"
#include "box2d.hpp"

class Ray2D
{

public:

  Ray2D() = default;

  Ray2D(Ray2D const & obj)
    : m_origin(obj.m_origin)
    , m_direction(obj.m_direction)
  {}

  Ray2D(Point2D const & p_origin, Point2D const & p_direction)
    : m_origin(p_origin)
    , m_direction(p_direction)
  {}

  Ray2D(std::initializer_list<float> const & lst)
  {
    Point2D * vals[] = { &m_origin, &m_direction };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    int j = lst.size();
    for (int i = 0; i < count && it != lst.end(); i++, it += 2)
      *vals[i] = { Coordinates(*(it), j), Coordinates(*(it + 1), j) };
  }

  Ray2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_origin, &m_direction };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, it++)
      *vals[i] = *(it);
  }

  Point2D const & origin() const { return m_origin; }
  Point2D const & direction() const { return m_direction; }

  Ray2D(Ray2D && obj)
  {
    std::swap(m_origin, obj.m_origin);
    std::swap(m_direction, obj.m_direction);
  }

  Ray2D & operator = (Ray2D && obj)
  {
    std::swap(m_origin, obj.m_origin);
    std::swap(m_direction, obj.m_direction);
    return *this;
  }

  Ray2D & operator = (Ray2D const & obj)
  {
    if (this == &obj) return *this;
    m_origin = obj.m_origin;
    m_direction = obj.m_direction;
    return *this;
  }

  bool operator == (Ray2D const & obj) const
  {
    return (m_origin == obj.m_origin) && (m_direction == obj.m_direction);
  }

  bool operator != (Ray2D const & obj)
  {
    return !operator == (obj);
  }

  Ray2D & Move(Point2D const & vectorMove)
  {
    m_origin += vectorMove;
    return *this;
  }

  Ray2D & Move(float x, float y)
  {
    m_origin.x() += x;
    m_origin.y() += y;
    return *this;
  }

  bool Ray2D::Intersection(Point2D a, Point2D b)
  {
    // Finding coeff
    float a1 = a.y() - b.y();
    float a2 = m_origin.y() - m_direction.y();
    float b1 = b.x() - a.x();
    float b2 = m_direction.x() - m_origin.x();
    float c1 = a.x()*b.y() - b.x()*a.y();
    float c2 = m_origin.x()*m_direction.y() - m_direction.x()*m_origin.x();

    // Finding intersection point
    float x = (c2*b1 - c1*b2) / (a1*b2 - a2*b1);
    float y = -c1 / b1 - (a1*c2*b1 - a1*c1*b2) / (b1*a1*b2 - b1*a2*b1);

    return ((x > a.x()) && (x < b.x()) && (y > a.y()) && (y < b.y()));
  }


private:
  Point2D m_origin = { 0.0f, 0.0f };
  Point2D m_direction = { 0.0f, 1.0f };

  float Coordinates(float a, int & count)
  {
    return (count-- > 0) ? a : 0.0f;
  }
};
