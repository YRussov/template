#pragma once

#include "box2d.hpp"
#include "point2d.hpp"
#include "ray2d.hpp"
#include "gun.hpp"

class Bullet : public Box2D
{
public:
  Bullet() = default;

  Bullet(Point2D origin, Point2D direction)
    : m_origin(origin)
    , m_direction(direction)
  {
    Position();
  }

  void Update()
  {

  }

  void Motion()
  {
    m_origin += VectorSpeed();
  }

private:

  void Position()
  {
    m_position = {
      (m_origin.x() - m_position.Length() / 2.0f), 
      (m_origin.y() - m_position.Width() / 2.0f), 
      (m_origin.x() + m_position.Length() / 2.0f), 
      (m_origin.y() + m_position.Width() / 2.0f) };
  }

  Point2D VectorSpeed() { return m_direction*m_speed; }

  Box2D m_position = { Point2D{0.0f, 0.0f}, Point2D{1.0f, 1.0f} };
  Point2D m_origin = { 0.0f, 0.0f };
  Point2D m_direction = { 1.0f, 0.0f };
  float m_speed = 0.1f;

};