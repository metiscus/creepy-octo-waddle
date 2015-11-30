#include "vector.h"

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    if((fabs(lhs.x-rhs.x) < 0.00001f) &&
       (fabs(lhs.y-rhs.y) < 0.00001f)   )
    {
	return true;
    }
    return false;
}

Vector2 operator*(const float& lhs, const Vector2& rhs)
{
    return Vector2(rhs.x*lhs, rhs.y*lhs);
}
