#pragma once

#include "gameentity.hpp"
#include "bullet.hpp"

class Gun :public GameEntity
{
public:

  Gun() = default;

  Gun(int ammo) :m_ammo(ammo) {}

  Gun(Box2D && position) :m_position(std::move(position)) {}

  Gun(Gun const & obj) :m_ammo(obj.m_ammo) {}

  Gun(Gun && obj) { std::swap(m_ammo, obj.m_ammo); }

  Gun & operator = (Gun && obj)
  {
    std::swap(m_ammo, obj.m_ammo);
    return *this;
  }

  void SetAmmo(unsigned int && ammo) { m_ammo = std::move(ammo); }
  void SetDirection(Point2D && direction) { m_direction = std::move(direction); }
  void SetPosition(Box2D && position) { m_position = std::move(position); }

  unsigned int GetAmmo() const { return m_ammo; }
  Point2D GetDirection() const { return m_direction; }
  Box2D GetPosition() const { return m_position; }

  Bullet Shot()
  {
    if (m_ammo > 0)
    {
      m_ammo--;
      Bullet bullet(m_position.Center(), m_direction);
      return bullet;
    }
    return;
  }

  void Move() override {}

private:

  unsigned int m_ammo = 10;
  Point2D m_direction = { 1.0f, 0.0f };
  Box2D m_position = { 0.0f, 0.0f, 1.0f, 1.0f };

};