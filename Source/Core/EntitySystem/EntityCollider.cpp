// Matching header
#include "Core/EntitySystem/EntityCollider.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntityTransform.h"

// Standard libraries
#include <algorithm>
#include <stdexcept>


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

EntityCollider::EntityCollider()
    : radius_(0.0f),
      collisionsEnabled_(true)
{
    // Empty
}


// ================================================================================================
//   Collision radius
// ------------------------------------------------------------------------------------------------

void EntityCollider::radius(float r)
{
    if (r < 0.0f) {
        throw std::invalid_argument("Collider radius cannot be negative.");
    }
    radius_ = r;
}

float EntityCollider::radius() const
{
    return radius_;
}

float EntityCollider::scaledRadius() const
{
    float maxScale = std::max(entity().transform().scale().x, entity().transform().scale().y);
    return radius_ * maxScale;
}


// ================================================================================================
//   Collisions enabled
// ------------------------------------------------------------------------------------------------

void EntityCollider::collisionsEnabled(bool value)
{
    collisionsEnabled_ = value;
}

bool EntityCollider::collisionsEnabled() const
{
    return collisionsEnabled_;
}

