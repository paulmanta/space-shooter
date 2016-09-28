// Matching header
#include "Core/EntitySystem/EntityTransform.h"

// External libraries
#include <Framework/Point2D.h>

// Standard libraries
#include <cmath>


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

EntityTransform::EntityTransform()
    : position_(0.0f, 0.0f),
      scale_(1.0f, 1.0f),
      rotation_(0.0f)
{
    // Empty
}


// ================================================================================================
//   Getters and setters
// ------------------------------------------------------------------------------------------------

const Point2D& EntityTransform::position() const { return position_; }
void EntityTransform::position(const Point2D& pos) { position_ = pos; }

const Point2D& EntityTransform::scale() const { return scale_; }
void EntityTransform::scale(const Point2D& scale) { scale_ = scale; }

float EntityTransform::rotation() const { return rotation_; }

void EntityTransform::rotation(float rot)
{
    rot = std::fmod(rot, 6.2831f);
    rotation_ = rot < 0.0f ? rot + 6.2831f : rot;
}

