#pragma once

#include "gameentity.hpp"

class Bullet :public GameEntity
{
public:
  Bullet() = default;

  Bullet(Point2D origin, Point2D direction)
    : m_origin(origin)
    , m_direction(direction)
  {
    Position();
  }
  
  Bullet(Bullet const & obj)
    : m_origin(obj.m_origin)
    , m_direction(obj.m_direction)
  {}

  Bullet(Bullet && obj)
  {
    std::swap(m_origin, obj.m_origin);
    std::swap(m_direction, obj.m_direction);
  }

  Bullet & operator = (Bullet && obj)
  {
    std::swap(m_origin, obj.m_origin);
    std::swap(m_direction, obj.m_direction);
    return *this;
  }

  void Update()
  {
    Move();
  }

  void Move() override
  {
    m_position.Move(VectorSpeed());
    Origin();
  }

  Box2D const & GetPosition() const { return m_position; }
  Point2D const & GetOrigin() const { return m_origin; }
  Point2D const & GetDirection() const { return m_direction; }
  float const & GetSpeed() const { return m_speed; }
  float const & GetLength() const { return m_length; }
  float const & GetWidth() const { return m_width; }

  void SetPosition(Box2D && position)
  {
    m_position = std::move(position);
    Origin();
  }
  void SetOrigin(Point2D && origin)
  {
    m_origin = std::move(origin);
    Position();
  }
  void SetDirection(Point2D && direction) { m_direction = std::move(m_direction); }
  void SetSpeed(float const & speed) { m_speed = speed; }
  void SetLength(float const & length)
  {
    try
    {
      if (length < 1e-5) throw std::invalid_argument("The length can not be negative");
      m_length = length;
    }
    catch (const std::exception & ex)
    {
      std::cerr << ex.what();
    }
  }
  void SetWidth(float const & width)
  {
    try
    {
      if (width < 1e-5) throw std::invalid_argument("The width can not be negative");
      m_width = width;
    }
    catch (const std::exception & ex)
    {
      std::cerr << ex.what();
    }
  }

private:

  void Position()
  {
    m_position = {
      (m_origin.x() - m_length / 2.0f),
      (m_origin.y() - m_width / 2.0f),
      (m_origin.x() + m_length / 2.0f),
      (m_origin.y() + m_width / 2.0f) };
  }

  void Origin() { m_origin = m_position.Center(); }

  Point2D VectorSpeed() { return m_direction*m_speed; }

  Point2D m_origin = { 0.0f, 0.0f };
  Point2D m_direction = { 1.0f, 0.0f };
  Box2D m_position = { 0.0f, 0.0f, 0.1f, 0.1f };
  float m_speed = 1.0f;
  float m_length = 0.4f;
  float m_width = 0.2f;

};