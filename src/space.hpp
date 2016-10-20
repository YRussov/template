#pragma once
#include "box2d.hpp"
#include "ray2d.hpp"
#include "point2d.hpp"
#include "gameentity.hpp"
#include <list>

class Space
{
public:
  Space() = default;

  std::list<GameEntity*> const & List() const
  {
    return m_list;
  }

  float x_Size() const
  {
    return ( m_position.boxMax().x() - m_position.boxMin().x() );
  }

  float y_Size() const  
  { 
    return ( m_position.boxMax().y() - m_position.boxMin().y() );
  }


private:
  Box2D m_position = {10.0f, 10.0f, 100.0f, 100.0f};
  std::list<GameEntity*> m_list;
};
