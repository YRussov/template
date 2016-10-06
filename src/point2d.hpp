#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

float const kEps = 1e-5;

class Point2D
{

public:

	// Разрешаем конструирование по умолчанию.
	Point2D() = default;

	// Конструктор копирования.
	Point2D(Point2D const & obj)
		: m_x(obj.m_x)
		, m_y(obj.m_y)
	{}

	// Конструктор с параметрами.
	Point2D(float x, float y)
		: m_x(x)
		, m_y(y)
	{}


	// Добавим конструирование через initializer_list
	// Конструктор со списком инициализации.
	Point2D(std::initializer_list<float> const & lst)
	{
		float * vals[] = { &m_x, &m_y };
		int const count = sizeof(vals) / sizeof(vals[0]);
		auto it = lst.begin();
		for (int i = 0; i < count && it != lst.end(); i++, ++it)
			*vals[i] = *it;
	}


	// Добавим полезные методы в public-секцию
	// Оператор логического равенства.
	bool operator == (Point2D const & obj) const
	{
		return EqualWithEps(m_x, obj.m_x) && EqualWithEps(m_y, obj.m_y);
	}
	float & x() { return m_x; }
	float & y() { return m_y; }
	float const & x() const { return m_x; }
	float const & y() const { return m_y; }


	// Добавим оператор присваивания
	// Оператор присваивания.
	Point2D & operator = (Point2D const & obj)
	{
		if (this == &obj) return *this;
		m_x = obj.m_x;
		m_y = obj.m_y;
		return *this;
	}


	// Добавим ещё логических операторов
	// Оператор логического неравенства.
	bool operator != (Point2D const & obj) const
	{
		return !operator==(obj);
	}
	// Оператор меньше.
	bool operator < (Point2D const & obj) const
	{
		if (m_x < obj.m_x) return true;
		return m_y < obj.m_y;
	}


	// Добавим математические операторы
	// Сложение.
	Point2D operator + (Point2D const & obj) const
	{
		return{ m_x + obj.m_x, m_y + obj.m_y };
	}
	// Вычитание.
	Point2D operator - (Point2D const & obj) const
	{
		return{ m_x - obj.m_x, m_y - obj.m_y };
	}
	// Математическое отрицание.
	Point2D operator - () const
	{
		return{ -m_x, -m_y };
	}
	// Умножение на число.
	Point2D operator * (float scale) const
	{
		return{ m_x * scale, m_y * scale };
	}
	// Деление на число.
	Point2D operator / (float scale) const
	{
		//TODO: обработать деление на 0.
		return{ m_x / scale, m_y / scale };
	}


	// Добавим математические операторы
	Point2D & operator += (Point2D const & obj)
	{
		m_x += obj.m_x;
		m_y += obj.m_y;
		return *this;
	}
	Point2D & operator -= (Point2D const & obj)
	{
		m_x -= obj.m_x;
		m_y -= obj.m_y;
		return *this;
	}
	Point2D & operator *= (float scale)
	{
		m_x *= scale;
		m_y *= scale;
		return *this;
	}
	Point2D & operator /= (float scale)
	{
		//TODO: обработать деление на 0.
		m_x /= scale;
		m_y /= scale;
		return *this;
	}


	// Переопределим оператор[]
	// Переопределение оператора [].
	float operator [] (unsigned int index) const
	{
		if (index >= 2) return 0.0f;
		return index == 0 ? m_x : m_y;
	}


	// Переопределим оператор() для внутренней структуры
	// Добавим внутреннюю сущность для вычисления хэша.
	struct Hash
	{
		size_t operator()(Point2D const & p) const
		{
			auto hasher = std::hash<float>();
			return (hasher(p.x()) ^ (hasher(p.y()) << 1));
		}
	};


	// Переопределим оператор << для std::ostream и Point2D
	friend std::ostream & operator << (std::ostream & os, Point2D const & obj)
	{
		os << "Point2D {" << obj.x() << ", " << obj.y() << "}";
		return os;
	}

private:

	bool EqualWithEps(float v1, float v2) const
	{
		return fabs(v1 - v2) < kEps;
	}

	float m_x = 0.0f, m_y = 0.0f;

};
