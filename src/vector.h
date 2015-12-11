#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cmath>

class Vector
{
public:
    float x;
    float y;
    float z;

    Vector(float ix = 0.f, float iy = 0.f,  float iz = 0.f)
    : x(ix)
    , y(iy)
    , z(iz) { }


    void Set(const float& x_, const float& y_, const float& z_)
    {
        this->x = x_;
        this->y = y_;
        this->z = z_;
    }

    void Normalize()
    {
        float len = 1.0f / (sqrtf(x*x+y*y+z*z) + 0.00001f);
        x *= len;
        y *= len;
        z *= len;
    }

    float Length() const
    {
        return sqrtf(x*x+y*y+z*z) + 0.00001f;
    }

    float Length2() const
    {
        return x*x+y*y+z*z;
    }

    Vector AsUnit() const
    {
        float invlen = 1.0f/Length();
        return Vector(x*invlen, y*invlen, z*invlen);
    }

    float Dot(const Vector& other) const
    {
        return x*other.x + y*other.y + z*other.z;
    }

    inline Vector operator*(const float& other) const
    {
        return Vector(x*other, y*other, z*other);
    }

    inline Vector operator/(const float& other) const
    {
        float div  = 1.0f/(other + 0.00001f);
        return Vector(x*div, y*div, z*div);
    }

    inline Vector operator+(const Vector& other) const
    {
        return Vector(x+other.x, y+other.y, z+other.z);
    }

    inline Vector operator-(const Vector& other) const
    {
        return Vector(x-other.x, y-other.y, z-other.z);
    }

    inline Vector& operator*=(const float& other)
    {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    inline Vector& operator+=(const Vector& other)
    {
        *this = *this + other;
        return *this;
    }

    inline Vector& operator-=(const Vector& other)
    {
        *this = *this - other;
        return *this;
    }

    inline Vector& operator/=(const float& other)
    {
        float div = 1.0f/(other + 0.00001f);
        x *= div;
        y *= div;
        z *= div;
        return *this;
    }
};

bool operator==(const Vector& lhs, const Vector& rhs);
Vector operator*(const float& lhs, const Vector& rhs);
Vector TripleProduct(const Vector& a, const Vector& b, const Vector& c);

#endif // VECTOR_H_INCLUDED
