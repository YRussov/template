#pragma once
#include "box2d.hpp"
#include "ray2d.hpp"
#include "point2d.hpp"

class Space
{
public:
  Space() = default;

  float x_Size() const
  {
    return (m_max - m_min).x();
  }

  float y_Size() const  
  { 
    return (m_max - m_min).y();;
  }


private:
  //Box2D m_position = {10.0f, 10.0f, 100.0f, 100.0f};
  Point2D m_min = { 10.0f, 10.0f };
  Point2D m_max = { 100.0f, 100.0f };
};
