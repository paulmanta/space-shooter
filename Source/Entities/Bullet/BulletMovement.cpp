// Matching header
#include "Entities/Bullet/BulletMovement.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntityTransform.h"
#include "Core/GameTime/GameTime.h"
#include "Math/VectorMath.h"


// ================================================================================================
//   Static attributes
// ------------------------------------------------------------------------------------------------

const float BulletMovement::cMovementSpeed_ = 600.0f;


// ================================================================================================
//   Overridden functions
// ------------------------------------------------------------------------------------------------

void BulletMovement::onIdle()
{
    float dt = GameTime::Instance().delta();
    Point2D front = rotate(Point2D(0.0f, 1.0f), entity().transform().rotation());
    Point2D deltaPosition = dt * (cMovementSpeed_ * front + playerVelocity_);
    entity().transform().position(entity().transform().position() + deltaPosition); 
}


// ================================================================================================
//   Setters
// ------------------------------------------------------------------------------------------------

void BulletMovement::playerVelocity(const Point2D& velocity)
{
    playerVelocity_ = velocity;
}