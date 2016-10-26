#include "Vector.h"

Vector::Vector()
: x(1.f), y(0.f)
{
}
Vector::Vector(const float& _x, const float& _y)
: x(_x), y(_y)
{
}
Vector::Vector(const Point& pt)
: x(pt.x), y(pt.y)
{
}

float Vector::length() const
{
	return sqrt(x*x + y*y);
}
Vector Vector::normalize() const
{
	return Vector(x/length(), y/length());
}

Vector Vector::operator + (const Vector& o) const
{
	return Vector(x + o.x, y + o.y);
}
Vector Vector::operator - (const Vector& o) const
{
	return Vector(x - o.x, y - o.y);
}
Vector::operator Point ()
{
	return Point(LONG(x), LONG(y));
}
