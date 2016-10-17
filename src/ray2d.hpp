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

  Ray2D(Point2D const & origin, Point2D const & direction)
    : m_origin(origin)
    , m_direction(direction)
  {
    Normalization();
  }

  Ray2D(std::initializer_list<float> const & lst)
  {
    Point2D * vals[] = { &m_origin, &m_direction };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    int j = lst.size();
    for (int i = 0; i < count && it != lst.end(); i++, it += 2)
      *vals[i] = { Coordinates(*(it), j), Coordinates(*(it + 1), j) };
    Normalization();
  }

  Ray2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_origin, &m_direction };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, it++)
      *vals[i] = *(it);
    Normalization();
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

  friend bool Intersection(Box2D const & box, Ray2D const & ray)
  {
    float arr[4] = {
      atan2(box.boxMin() - ray.origin()),
      atan2(box.boxMax() - ray.origin()),
      atan2(box.vertexLT() - ray.origin()),
      atan2(box.vertexRB() - ray.origin()) };

    float a = atan2(ray.direction());
    float max_atan = arr[0];
    float min_atan = arr[0];

    for (int i = 1; i < 4; i++)
    {
      if (max_atan < arr[i]) max_atan = arr[i];
      if (min_atan > arr[i]) min_atan = arr[i];
    }

    return (a < max_atan && a > min_atan);
  }

  friend bool Intersection(Ray2D const & ray, Box2D const & box) { return Intersection(box, ray); }

private:

  Point2D m_origin = { 0.0f, 0.0f };
  Point2D m_direction = { 0.0f, 1.0f };

  float Coordinates(float a, int & count)
  {
    return (count-- > 0) ? a : 1.0f;
  }

  void Normalization()
  {
    float lng = Length();
    m_direction.x() /= lng;
    m_direction.y() /= lng;
  }

  float const Length() const
  {
    return sqrt(m_direction.x() * m_direction.x() + m_direction.y() * m_direction.y());
  }
};
