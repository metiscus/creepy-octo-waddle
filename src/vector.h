#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cmath>

class Vector2
{
public:
    float x;
    float y;

    Vector2(float ix = 0.f, float iy = 0.f)
    : x(ix)
    , y(iy) { }

    void Set(const float& x_, const float& y_)
    {
        this->x = x_;
        this->y = y_;
    }

    void Normalize()
    {
        float len = 1.0f / (sqrtf(x*x+y*y) + 0.00001f);
        x *= len;
        y *= len;
    }

    float Length() const
    {
        return sqrtf(x*x+y*y) + 0.00001f;
    }

    float Length2() const
    {
        return x*x+y*y;
    }

    Vector2 AsUnit() const
    {
        float invlen = 1.0f/Length();
        return Vector2(x*invlen, y*invlen);
    }

    float Dot(const Vector2& other) const
    {
        return x*other.x + y*other.y;
    }

    inline Vector2 operator*(const float& other) const
    {
        return Vector2(x*other, y*other);
    }

    inline Vector2 operator/(const float& other) const
    {
        float div  = 1.0f/(other + 0.00001f);
        return Vector2(x*div, y*div);
    }

    inline Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x+other.x, y+other.y);
    }

    inline Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x-other.x, y-other.y);
    }

    inline Vector2& operator*=(const float& other)
    {
        x *= other;
        y *= other;
        return *this;
    }

    inline Vector2& operator+=(const Vector2& other)
    {
        *this = *this + other;
        return *this;
    }

    inline Vector2& operator-=(const Vector2& other)
    {
        *this = *this - other;
        return *this;
    }

    inline Vector2& operator/=(const float& other)
    {
        float div = 1.0f/(other + 0.00001f);
        x *= div;
        y *= div;
        return *this;
    }
};

bool operator==(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const float& lhs, const Vector2& rhs);


#endif // VECTOR_H_INCLUDED
