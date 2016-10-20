#pragma once

#include "point2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>

class Box2D
{

public:

  Box2D() = default;

  Box2D(Box2D const & obj)
    : m_min(obj.m_min)
    , m_max(obj.m_max)
  {}

  Box2D(Point2D const & min, Point2D const & max)
    : m_min(min)
    , m_max(max)
  {
    CheckMaxMin();
  }

  Box2D(std::initializer_list<float> const & lst)
  {
    Point2D * vals[] = { &m_min, &m_max };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    int j = lst.size();
    for (int i = 0; i < count && it != lst.end(); i++, it += 2)
      *vals[i] = { Coordinates(*(it), j), Coordinates(*(it + 1), j) };
    CheckMaxMin();
  }

  Box2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_min, &m_max };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, it++)
      *vals[i] = *(it);
    CheckMaxMin();
  }

  Box2D(Box2D && obj)
  {
    std::swap(m_min, obj.m_min);
    std::swap(m_max, obj.m_max);
  }

  Box2D & operator = (Box2D && obj)
  {
    std::swap(m_min, obj.m_min);
    std::swap(m_max, obj.m_max);
    return *this;
  }

  Point2D const & Center() const { return (m_max + m_min) / 2; }

  Point2D const & vertexLT() const { return{ m_min[0], m_max[1] }; }
  Point2D const & vertexRB() const { return{ m_max[0], m_min[1] }; }
  Point2D const & boxMin() const { return m_min; }
  Point2D const & boxMax() const { return m_max; }

  float const & Length() const { return m_max.x() - m_min.x(); }
  float const & Width() const { return m_max.y() - m_min.y(); }

  Box2D & operator = (Box2D const & obj)
  {
    if (this == &obj) return *this;
    m_min = obj.m_min;
    m_max = obj.m_max;
    return *this;
  }

  bool operator == (Box2D const & obj) const
  {
    return (m_min == obj.m_min && m_max == obj.m_max);
  }

  void Move(Point2D & vectorMove)
  {
    m_min += vectorMove;
    m_max += vectorMove;
  }

  bool Intersection(Point2D & min, Point2D & max) const
  {
    return !(m_max[1] <= min[1] || m_min[1] >= max[1] || m_max[0] <= min[0] || m_min[0] >= max[0]);
  }

  friend bool Intersection(Box2D const & obj1, Box2D const & obj2)
  {
    return !(obj1.m_max.y() <= obj2.m_min.y() || obj1.m_min.y() >= obj2.m_max.y() || obj1.m_max.x() <= obj2.m_min.x() || obj1.m_min.x() >= obj2.m_max.x());
  }

private:

  Point2D m_min = { 0.0f, 0.0f };
  Point2D m_max = { 0.0f, 0.0f };

  void CheckMaxMin()
  {
    if (m_max.x() < m_min.x()) std::swap(m_max.x(), m_min.x());
    if (m_max.y() < m_min.y()) std::swap(m_max.y(), m_min.y());
  }

  float Coordinates(float a, int & count)
  {
    return (count-- > 0) ? a : 0.0f;
  }
};