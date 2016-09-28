// Matching header
#include "Math/TransformStack.h"

// External libraries
#include <Framework/Point2D.h>
#include <Framework/Transform2D.h>

// Standard libraries
#include <stack>


// ================================================================================================
//   Identity matrix
// ------------------------------------------------------------------------------------------------

const Float3x3 TransformStack::cIdentity_ = {{
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}    
}};


// ================================================================================================
//   Push, pop, top
// ------------------------------------------------------------------------------------------------

void TransformStack::push()
{
    stack_.push(stack_.empty() ? cIdentity_ : stack_.top());
}

void TransformStack::pop()  { stack_.pop(); }
Float3x3& TransformStack::top() { return stack_.top(); }
const Float3x3& TransformStack::top() const { return stack_.top(); }


// ================================================================================================
//   Translate, rotate, scale
// ------------------------------------------------------------------------------------------------

void TransformStack::translate(const Point2D& translation)
{
    Transform2D::loadIdentityMatrix();
    Transform2D::translateMatrix(translation.x, translation.y);
    Transform2D::multiplyMatrix(top().data);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            top().data[i][j] = Transform2D::TransformMatrix[i][j];
        }
    }
}

void TransformStack::scale(const Point2D& scale)
{
    Transform2D::loadIdentityMatrix();
    Transform2D::scaleMatrix(scale.x, scale.y);
    Transform2D::multiplyMatrix(top().data);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            top().data[i][j] = Transform2D::TransformMatrix[i][j];
        }
    }
}

void TransformStack::rotate(float rotation)
{
    Transform2D::loadIdentityMatrix();
    Transform2D::rotateMatrix(rotation);
    Transform2D::multiplyMatrix(top().data);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            top().data[i][j] = Transform2D::TransformMatrix[i][j];
        }
    }
}