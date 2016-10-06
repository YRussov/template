#pragma once

#include "point2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>

class Box2D
{

public:

	Box2D() = default;

	//  онструктор копировани€.
	Box2D(Box2D const & obj)
		: m_min(obj.m_min)
		, m_max(obj.m_max)
	{}

	//  онструктор с параметрами.
	Box2D(Point2D const & min, Point2D const & max)
		: m_min(min)
		, m_max(max)
	{
		if (max < min)
		{
			m_min = max;
			m_max = min;
		}
	}

	//  онструктор со списком инициализации.
	Box2D(std::initializer_list<float> const & lst)
	{
		Point2D * vals[] = { &m_min, &m_max };
		int const count = sizeof(vals) / sizeof(vals[0]);
		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, it += 2)
			*vals[i] = { *(it), *(it + 1) };

		if (*vals[1] < *vals[0])
		{
			Point2D v = m_min;
			m_min = m_max;
			m_max = v;
		}
	}

	Point2D Center()												// получить координату центра
	{
		return (m_max + m_min) / 2;
	}

	Point2D vertexLT() { return{ m_min[0], m_max[1] }; }			// vertex left top
	Point2D vertexRB() { return{ m_max[0], m_min[1] }; }			// vertex right bottom

	Point2D & min() { return m_min; }
	Point2D & max() { return m_max; }
	Point2D const & min() const { return m_min; }
	Point2D const & max() const { return m_max; }

	// ќператор присваивани€.
	Box2D & operator = (Box2D const & obj)
	{
		if (this == &obj) return *this;
		m_min = obj.m_min;
		m_max = obj.m_max;
		return *this;
	}

	// ќператор логического равенства.
	bool operator == (Box2D const & obj) const
	{
		return (m_min == obj.m_min && m_max == obj.m_max);
	}

	void Move(Point2D & vectorMove)									// сместить на вектор vectorMove
	{
		m_min += vectorMove;
		m_max += vectorMove;
	}

	bool Intersection(Point2D & min, Point2D & max) const			// проверить на пересечение с другим.
	{
		if (m_max[1] <= min[1] || m_min[1] >= max[1])
		{
			return false;
		}
		else if (m_max[0] <= min[0] || m_min[0] >= max[0])
		{
			return false;
		}
		return true;
	}

	~Box2D()
	{}

protected:


private:

	Point2D m_min = { 0.0f, 0.0f };
	Point2D m_max = { 0.0f, 0.0f };

};


