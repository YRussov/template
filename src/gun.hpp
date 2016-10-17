#pragma once

#include <iostream>
#include <utility>
#include "box2d.hpp"
#include "point2d.hpp"
#include "ray2d.hpp"
#include "bullet.hpp"

class Gun
{
public:

  Gun() = default;
  Gun(int ammo) :m_ammo(ammo) {}

  Gun(Gun const & obj) :m_ammo(obj.m_ammo) {}

  Gun(Gun && obj)
  {
    std::swap(m_ammo, obj.m_ammo);
  }

  Gun & operator = (Gun && obj)
  {
    std::swap(m_ammo, obj.m_ammo);
    return *this;
  }

  int GetAmmo() const 
  {
    return m_ammo;
  }

  void operator + (int bullets)
  {
    m_ammo += bullets;
  }

  void operator - (int bullets)
  {
    m_ammo -= bullets;
  }

  Gun & operator = (Gun const & gun)
  {
    if (this == &gun) return *this;
    m_ammo = gun.GetAmmo();
    return *this;
  }

  bool operator == (Gun const & gun) const
  {
    return m_ammo == gun.m_ammo;
  }

  friend std::ostream & operator << (std::ostream & os, Gun const & gun)
  {
    os << "Gun {" << gun.GetAmmo() << "}";
    return os;
  }

  void Update()
  {

  }

  Bullet Shot(Point2D direction)
  {
    if (m_ammo > 0)
    {
      m_ammo--;
      Bullet bullet = Bullet(m_position.Center(), direction);
      return bullet;
    }
  }

private:

  unsigned int m_ammo = 10;
  Box2D m_position = { Point2D{ 0.0f, 0.0f }, Point2D{ 1.0f, 1.0f } };
};