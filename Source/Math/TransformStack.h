#ifndef GEOMETRYWARS_MATH_TRANSFORMSTACK_H
#define GEOMETRYWARS_MATH_TRANSFORMSTACK_H


// Standard libraries
#include <stack>

// Forward declarations
class Point2D;


struct Float3x3 {
    float data[3][3];
};


class TransformStack
{
public:
    void push();
    void pop();

    Float3x3& top();
    const Float3x3& top() const;

    void rotate(float);
    void translate(const Point2D&);
    void scale(const Point2D&);

private:
    static const Float3x3 cIdentity_;
    std::stack<Float3x3> stack_;
};


#endif // GEOMETRYWARS_MATH_TRANSFORMSTACK_H