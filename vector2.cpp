#include "vector2.h"
#include <cmath>

Vector2::Vector2() : x(0.0f), y(0.0f)
{
}

Vector2::Vector2(float x, float y) : x(x) , y(y)
{
}

Vector2::Vector2(const Vector2& vector2) : x(vector2.x), y(vector2.y)
{
}

//---------------------------------------------------------

const Vector2& Vector2::operator = (const Vector2& vector2)
{
    x = vector2.x;
    y = vector2.y;
    return *this;
}

Vector2 Vector2::operator + (const Vector2& vector2) const
{
    return Vector2(x + vector2.x, y + vector2.y);
}

Vector2 Vector2::operator - (const Vector2& vector2) const
{
    return Vector2(x - vector2.x, y - vector2.y);
}

const Vector2& Vector2::operator += (const Vector2& vector2)
{
    x += vector2.x;
    y += vector2.y;
    return *this;
}

const Vector2& Vector2::operator -= (const Vector2& vector2)
{
    x -= vector2.x;
    y -= vector2.y;
    return *this;
}

const Vector2& Vector2::operator *= (int i)
{
    x *= i;
    y *= i;
    return *this;
}

const Vector2& Vector2::operator *= (float i)
{
    x *= i;
    y *= i;
    return *this;
}

//---------------------------------------------------------

float Vector2::length() const
{
    return sqrt(x * x + y * y);
}

//---------------------------------------------------------

Vector2 operator * (float i, const Vector2& vector2)
{
    return Vector2(i * vector2.x, i * vector2.y);
}

Vector2 operator * (const Vector2& vector2, float i)
{
    return Vector2(i * vector2.x, i * vector2.y);
}

Vector2 operator * (int i, const Vector2& vector2)
{
    return Vector2(i * vector2.x, i * vector2.y);
}

Vector2 operator * (const Vector2& vector2, int i)
{
    return Vector2(i * vector2.x, i * vector2.y);
}
