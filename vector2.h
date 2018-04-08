#ifndef VECTOR2_H
#define VECTOR2_H


struct Vector2
{
    Vector2();
    Vector2(float x, float y);

    Vector2 operator - () const;

    const Vector2& operator += (const Vector2& vector2);
    const Vector2& operator -= (const Vector2& vector2);
    const Vector2& operator *= (int i);
    const Vector2& operator *= (float i);

    float length() const;

    float x;
    float y;
};

Vector2 operator + (const Vector2& left, const Vector2& right);
Vector2 operator - (const Vector2& left, const Vector2& right);

Vector2 operator * (float i, const Vector2& vector2);
Vector2 operator * (const Vector2& vector2, float i);

Vector2 operator * (int i, const Vector2& vector2);
Vector2 operator * (const Vector2& vector2, int i);

#endif // VECTOR2_H
