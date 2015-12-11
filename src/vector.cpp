#include "vector.h"

bool operator==(const Vector& lhs, const Vector& rhs)
{
    if((fabs(lhs.x-rhs.x) < 0.00001f) &&
       (fabs(lhs.y-rhs.y) < 0.00001f)   )
    {
	return true;
    }
    return false;
}

Vector operator*(const float& lhs, const Vector& rhs)
{
    return Vector(rhs.x*lhs, rhs.y*lhs);
}


// Vector Triple Product
Vector TripleProduct(const Vector& a, const Vector& b, const Vector& c)
{
    return b * (a.Dot(c)) - c * (a.Dot(b));
}
