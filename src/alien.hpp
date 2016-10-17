#pragma once
#include "box2d.hpp"
#include "ray2d.hpp"
#include "point2d.hpp"

class Alien
{
public:
  Alien() = default;

  Alien * CreateAlien() const
  {
    Point2D origin = m_position.Center();
    Alien * alien = new Alien(origin);
    return alien;
  }

  void Damage (float const & damage)
  {
    if (m_healt - damage > 0)
      { m_health = m_health - damage; }
    else
      m_health = 0; 
  }

  void SetAlien(Box2D m_position const & position)
  {
    m_position = position;
  }

  Box2D GetAlien() const
  {
    return m_position;
  }
  
  void Move()
  {
    m_position.Move(m_position.Center + m_direction * m_speed);
  }

  void SetHealth (float health)
  {
    m_health = health;
  }

  void SetSpeed(float speed)
  {
    m_speed = speed;
  }

  float GetSpeed() const
  {
    return m_speed;
  }

  float GetHealth() const
  {
    return m_health;
  }

private:
  Box2D m_position = {0.0f, 0.0f, 1.0f, 1.0f};
  Ray2D m_direction = {0.0f, 0.0f, 1.0f, 1.0f};
  float m_health = 100.0f;
  float m_speed = 1.0f;
};
