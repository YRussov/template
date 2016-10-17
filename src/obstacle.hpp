#pragma once
#include "box2d.hpp"
#include "ray2d.hpp"
#include "point2d.hpp"

class Obstacle
{
public:
  Obstacle() = default;
  
  Obstacle(Point2D const & min, Point2D const & max) : m_min(min), m_max(max) {}

  void SetObstacle(Point2D const & min, Point2D const & max)
  {
    m_min = min;
    m_max = max;
  }

  Box2D GetObstacle() const
  {
    Box2D m_obstacle = Box2D(m_min, m_max);
    return m_obstacle;
  }

  void SetHealth (float health)
  {
    m_health = health;
  }

  void Damage (float const & damage)
  {
    if (m_healt - damage > 0)
      { m_health = m_health - damage; }
    else
      m_health = 0;
  }

private:
  Point2D m_min = { 0.0f, 0.0f };
  Point2D m_max = { 1.0f, 1.0f };
  float m_health = 50.0f;
};
