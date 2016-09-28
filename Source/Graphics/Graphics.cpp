// Matching header
#include "Graphics/Graphics.h"

// Project headers
#include "Math/VectorMath.h"

// External libraries
#include <Framework/Object2D.h>
#include <Framework/Point2D.h>
#include <Framework/DrawingWindow.h>
#include <Framework/Transform2D.h>
#include <Framework/Visual2D.h>

// Standard libraries
#include <memory>


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

Graphics::Graphics()
    : position_(0.0f, 0.0f)
{
    // Empty
}


// ================================================================================================
//   Initialization
// ------------------------------------------------------------------------------------------------

void Graphics::pushObject(std::shared_ptr<Object2D> object)
{
    objects_.push_back(object);
}

void Graphics::registerObjects(Visual2D& visual)
{
    for (auto& object : objects_) {
        DrawingWindow::addObject2D_to_Visual2D(object.get(), &visual);
    }
}


// ================================================================================================
//   Position
// ------------------------------------------------------------------------------------------------

const Point2D& Graphics::position() const
{
    return position_;
}

void Graphics::position(const Point2D& pos)
{
    Point2D delta = pos - position_;
    position_ = pos;

    for (auto& obj : objects_)
    {
        for (std::size_t i = 0; i < obj->points.size(); ++i) {
            *obj->points[i] = *obj->points[i] + delta;
        }
    }
}


// ================================================================================================
//   Apply transform
// ------------------------------------------------------------------------------------------------

void Graphics::applyTransform()
{
    for (auto& object : objects_) {
        Transform2D::applyTransform(object.get());
    }
}