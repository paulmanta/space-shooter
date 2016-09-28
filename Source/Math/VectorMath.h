#ifndef GEOMETRYWARS_MATH_MATH_H
#define GEOMETRYWARS_MATH_MATH_H

// External libraries
#include <Framework/Point2D.h>


bool operator==(const Point2D&, const Point2D&);
bool operator!=(const Point2D&, const Point2D&);

Point2D operator+(const Point2D&, const Point2D&);
Point2D operator-(const Point2D&, const Point2D&);

Point2D operator*(float, const Point2D&);
Point2D operator/(float, const Point2D&);

float dot(const Point2D&, const Point2D&);

float norm2(const Point2D&);
float norm(const Point2D&);

Point2D clampNorm(const Point2D&, float);
Point2D resize(const Point2D&, float);
Point2D rotate(const Point2D&, float);

#endif // GEOMETRYWARS_MATH_MATH_H