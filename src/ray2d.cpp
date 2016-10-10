#pragma once

#include "ray2d.hpp"
#include <initializer_list>

Ray2D::Ray2D(Point2D origin, Point2D direction)
  : m_origin(origin), m_direction(direction)
{}

Ray2D::Ray2D(Ray2D const & obj)
  : m_origin(obj.m_origin), m_direction(obj.m_direction)
{}

Ray2D::Ray2D(float f1, float f2, float f3, float f4)
  : m_origin(f1,f2), m_direction(f3,f4)
{}

bool Ray2D::operator == (Ray2D const & obj) const
{
  return (m_origin == obj.m_origin) && (m_direction == obj.m_direction);
}

Point2D & Ray2D::origin() { return m_origin; }
Point2D & Ray2D::direction() { return m_direction; }

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

Ray2D & Ray2D::operator = (Ray2D const & obj)
{
  if (this == &obj) return *this;
  m_origin = obj.m_origin;
  m_direction = obj.m_direction;
  return *this;
}

bool Ray2D::operator != (Ray2D const & obj) const
{
  return !Ray2D::operator == (obj);
}

Point2D Ray2D::operator [] (unsigned int index) const
{
  if (index >= 2) return { 0.0f, 0.0f };
  return index == 0 ? m_origin : m_direction;
}

float Ray2D::Det(float ** m) {
  return m[0][0]*m[1][1]-m[0][1]*m[1][0];
}

float ** Ray2D::ColumnReplace(float ** m, float * replace, int column) {

  float ** matrix = new float*[2];
  for(int i=0;i<2;i++)
    matrix[i]=new float[2];

  for(int i=0;i<2;i++)
    for(int j=0;j<2;j++)
      matrix[i][j] = m[i][j];
 
  for (int i = 0; i < 2; i++){
    matrix[i][column] = replace[i];
  }
  return matrix;
}

bool Ray2D::Intersection(Point2D a, Point2D b)
{
  float ** matrix = new float*[2];
  for(int i=0;i<2;i++)
    matrix[i]=new float[2];

  float hyp = sqrt(m_direction.x() * m_direction.x() + m_direction.y() * m_direction.y());
  float cos = m_direction.x() / hyp;
  float sin = m_direction.y() / hyp;

  matrix[0][0] = b.x() - a.x();
  matrix[0][1] = - cos;
  matrix[1][0] = b.y() - a.y();
  matrix[1][1] = -sin;

  float res[2];
  res[0] = -( a.x() - m_origin.x() );
  res[1] = -( a.y() - m_origin.y() );

  if (Det(matrix) == 0) { return false; }

  float** m1 = ColumnReplace(matrix,res,0);
  float** m2 = ColumnReplace(matrix,res,1);

  float T1 = Det(m1) / Det(matrix);
  float T2 = Det(m2) / Det(matrix);

  for (int i = 0; i < 2; i++)
  {
    delete [] matrix[i];
    delete [] m1[i];
    delete [] m2[i];
  }

  if( T2 >= 0 && ( T1 >= 0 && T1 <= 1 ))
    return true;
  else
    return false;
}

// Пересечение прямоугольника лучем
bool Ray2D::operator % (Box2D & obj)
{
  Point2D p1 = obj.p1(), p2 = { obj.p1().x(), obj.p2().y() },
          p3 = obj.p2(), p4 = { obj.p2().x(), obj.p1().y() };

  return Intersection(p1,p2) || Intersection(p2,p3) || Intersection(p3,p4) || Intersection(p4,p1);
}