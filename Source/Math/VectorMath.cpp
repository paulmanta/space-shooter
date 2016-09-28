// Matching header
#include "Math/VectorMath.h"

// External libraries
#include <Framework/Point2D.h>

// Standard libraries
#include <cmath>


// ================================================================================================
//   Operators
// ------------------------------------------------------------------------------------------------

bool operator==(const Point2D& u, const Point2D& v)
{
    return u.x == v.x && u.y == v.y;
}

bool operator!=(const Point2D& u, const Point2D& v)
{
    return !(u == v);
}

Point2D operator+(const Point2D& u, const Point2D& v)
{
    return Point2D(u.x + v.x, u.y + v.y);
}

Point2D operator-(const Point2D& u, const Point2D& v)
{
    return Point2D(u.x - v.x, u.y - v.y);
}

Point2D operator*(float a, const Point2D& u)
{
    return Point2D(a * u.x, a * u.y);
}

Point2D operator/(float a, const Point2D& u)
{
    return Point2D(a / u.x, a / u.y);
}


// ================================================================================================
//   Functions
// ------------------------------------------------------------------------------------------------

float norm2(const Point2D& v)
{
    return (v.x * v.x) + (v.y * v.y);
}

float norm(const Point2D& v)
{
    return std::sqrt(norm2(v));
}

Point2D clampNorm(const Point2D& v, float n)
{
    float n2 = norm2(v);
    return n2 <= n * n ? v : n / std::sqrt(n2) * v;
}

Point2D resize(const Point2D& v, float n)
{
    float n2 = norm2(v);
    return (n2 == 0.0f || n2 == n * n) ? v : n / std::sqrt(n2) * v;
}

Point2D rotate(const Point2D& v, float angle)
{
    float cs = std::cos(angle);
    float sn = std::sin(angle);

    float x = v.x * cs - v.y * sn;
    float y = v.x * sn + v.y * cs;

    return Point2D(x, y);
}

float dot(const Point2D& u, const Point2D& v)
{
    return (u.x * v.x) + (u.y * v.y);
}