#include "Vector2.h"

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(int _val)
{
	this->x = _val;
	this->y = _val;
}

Vector2::Vector2(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
}

Vector2::~Vector2()
{
}

void Vector2::SetXY(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
}

Vector2 Vector2::UpLeft() const
{
	return Vector2(-1, -1);
}

Vector2 Vector2::Up() const
{
	return Vector2(0, -1);
}

Vector2 Vector2::UpRight() const
{
	return Vector2(1, -1);
}

Vector2 Vector2::Right() const
{
	return Vector2(1, 0);
}

Vector2 Vector2::BotRight() const
{
	return Vector2(1, 1);
}

Vector2 Vector2::Down() const
{
	return Vector2(0, 1);
}

Vector2 Vector2::BotLeft() const
{
	return Vector2(-1, 1);
}

Vector2 Vector2::Left() const
{
	return Vector2(-1, 0);
}

Vector2 Vector2::Zero() const
{
	return Vector2( 0.f );
}


Vector2 Vector2::operator+(const Vector2 &rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}


