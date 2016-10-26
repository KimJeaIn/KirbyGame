#pragma once

#include "../GameDev/GameDev.h"

struct Vector
{
	Vector();
	Vector(const float& _x, const float& _y);
	Vector(const Point& pt);

	float length() const;
	Vector normalize() const;

	Vector operator + (const Vector& o) const;
	Vector operator - (const Vector& o) const;

	template<typename T>
	Vector operator * (const T& scalar) const
	{
		return Vector(x*scalar, y*scalar);
	}

	operator Point ();

	float x;
	float y;
};