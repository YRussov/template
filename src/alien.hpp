#pragma once
#include "box2d.hpp"
#include "ray2d.hpp"
#include "point2d.hpp"
#include "gameentity.hpp"

class Alien : public GameEntity
{
public:

  Alien() = default;

  void Damage (float const & damage)
  {
    if (m_healt - damage > 0)
        m_health = m_health - damage;
    else
      m_health = 0; 
  }

  void PositionAlien(Box2D const & position)
  {
    m_position = position;
  }

  Box2D GetPosition() const
  {
    return m_position;
  }
  
  void Move() override
  {
  try
    {
      m_position.Move(m_position.Center + m_direction * m_speed);
    }
  catch (std::exception const & ex)
    {
    }
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
