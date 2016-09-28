// Matching header
#include "Entities/Enemy/EnemyMovement.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntityTransform.h"
#include "Core/GameTime/GameTime.h"
#include "Core/GameWorld/GameWorld.h"
#include "Math/VectorMath.h"

// External libraries
#include <Framework/Point2D.h>


// ================================================================================================
//   Static attributes
// ------------------------------------------------------------------------------------------------

const float EnemyMovement::cMaxSpeed_ = 150.0f;
const float EnemyMovement::cMaxAcceleration_ = 200.0f;
const float EnemyMovement::cFrictionFactor_ = 1.0f;
const float EnemyMovement::cEnemyRepulsionFactor_ = 20.0f;


// ================================================================================================
//   Overridden functions
// ------------------------------------------------------------------------------------------------

void EnemyMovement::onInit()
{
    velocity_ = Point2D(0.0f, 0.0f);
    repulsion_ = Point2D(0.0f, 0.0f);
}

void EnemyMovement::onIdle()
{
    float dt = GameTime::Instance().delta();
    const Entity& player = GameWorld::Instance().player();

    Point2D playerPos = player.transform().position();
    Point2D enemyPos = entity().transform().position();

    Point2D playerDir = resize(playerPos - enemyPos, 1.0f);
    Point2D acceleration_ = cMaxAcceleration_ * playerDir;

    Point2D goodVelocity = dot(playerDir, velocity_) * playerDir;
    Point2D badVelocity = velocity_ - goodVelocity;

    Point2D friction = -cFrictionFactor_ * badVelocity;
    friction = clampNorm(friction, norm(badVelocity) / dt);

    velocity_ = clampNorm(velocity_ + dt * (acceleration_ + friction), cMaxSpeed_);
    entity().transform().position(enemyPos + dt * (velocity_ + repulsion_));
    repulsion_ = Point2D(0.0f, 0.0f);
}

void EnemyMovement::onEnemyCollision(const Entity& other)
{
    Point2D newRepulsion = entity().transform().position() - other.transform().position();
    newRepulsion = resize(newRepulsion, cEnemyRepulsionFactor_);
    repulsion_ = repulsion_ + newRepulsion;
}