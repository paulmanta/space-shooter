// Matching header
#include "Entities/Player/PlayerMovement.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/GameTime/GameTime.h"
#include "Core/GameWorld/GameWorld.h"
#include "Math/VectorMath.h"

// External libraries
#include <Framework/DrawingWindow.h>

// Standard libraries
#include <cmath>


// ================================================================================================
//   Static attributes
// ------------------------------------------------------------------------------------------------

const float PlayerMovement::cMaxSpeed_ = 350.0f; 
const float PlayerMovement::cMaxAcceleration_ = 300.0f;
const float PlayerMovement::cMaxAngularSpeed_ = 3.0f;
const float PlayerMovement::cBrakeFrictionFactor_ = 2.0f;
const float PlayerMovement::cLateralFrictionFactor_ = 3.0f;
const float PlayerMovement::cWallBounceSpeedFactor_ = 0.6f;


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

PlayerMovement::PlayerMovement()
    : velocity_(0.0f, 0.0f),
      angularSpeed_(0.0f),
      accelerating_(false)
{
    // Empty
}


// ================================================================================================
//   Update functions
// ------------------------------------------------------------------------------------------------

void PlayerMovement::onIdle()
{
    float dt = GameTime::Instance().delta();

    Point2D pos = entity().transform().position();
    float rot = entity().transform().rotation();

    Point2D acceleration(0.0f, 0.0f);
    Point2D breakFriction(0.0f, 0.0f);
    
    Point2D front = rotate(Point2D(0.0f, 1.0f), rot);
    Point2D right = rotate(front, -1.5707f);

    // Acceleration is applied when the user is either pressing the 'accelerate' button,
    // or the 'rotate' buttons. This makes it impossible for the player to rotate while
    // standing still, which looks odd.
    if (accelerating_ || std::abs(angularSpeed_) > 0.0f) {
        acceleration = cMaxAcceleration_ * front;
    }
    // When not accelerating, apply friction. This will cause the player to stop
    // after a while.
    else {
        breakFriction = -cBrakeFrictionFactor_ * velocity_;
        breakFriction = clampNorm(breakFriction, norm(velocity_) / dt);
    }

    // Also apply lateral friction which gives the player a tighter control of the ship.
    // A very large value for the lateral friction factor would cause the ship to not
    // drift at all; a value of zero causes it to drift a lot.
    Point2D lateralVelociy = dot(velocity_, right) * right;
    Point2D lateralFriction = -cLateralFrictionFactor_ * lateralVelociy;
    lateralFriction = clampNorm(lateralFriction, norm(lateralVelociy) / dt);

    velocity_ = velocity_ + dt * (acceleration + breakFriction + lateralFriction);
    velocity_ = clampNorm(velocity_, cMaxSpeed_);

    entity().transform().position(pos + dt * velocity_);
    entity().transform().rotation(rot + dt * angularSpeed_);
}

void PlayerMovement::onKeyDown(unsigned char key)
{
    if (key == KEY_UP) {
        accelerating_ = true;
    }
    else if (key == KEY_LEFT) {
        angularSpeed_ = cMaxAngularSpeed_;
    }
    else if (key == KEY_RIGHT) {
        angularSpeed_ = -cMaxAngularSpeed_;
    }
}

void PlayerMovement::onKeyUp(unsigned char key)
{
    if (key == KEY_UP) {
        accelerating_ = false;
    }
    else if (key == KEY_LEFT && angularSpeed_ > 0.0f) {
        angularSpeed_ = 0.0f;
    }
    else if (key == KEY_RIGHT && angularSpeed_ < 0.0f) {
        angularSpeed_ = 0.0f;
    }
}


// ================================================================================================
//   Collision events
// ------------------------------------------------------------------------------------------------

void PlayerMovement::onEnemyCollision(const Entity& enemy)
{
}

void PlayerMovement::onWallCollision()
{

    float wHalf = GameWorld::Instance().width() / 2.0f;
    float hHalf = GameWorld::Instance().height() / 2.0f;
    float r = entity().collider().scaledRadius();

    bool leftWall = entity().transform().position().x == -wHalf + r;
    bool rightWall = entity().transform().position().x == wHalf - r;
    bool topWall = entity().transform().position().y == hHalf - r;
    bool bottomWall = entity().transform().position().y == -hHalf + r;

    if (leftWall || rightWall) {
        velocity_.x *= -1.0f;
        velocity_ = cWallBounceSpeedFactor_ * velocity_;
    }
    else if (topWall || bottomWall) {
        velocity_.y *= -1.0f;
        velocity_ = cWallBounceSpeedFactor_ * velocity_; 
    }
}


// ================================================================================================
//   Getters, setters
// ------------------------------------------------------------------------------------------------

const Point2D& PlayerMovement::velocity() const { return velocity_; }
void PlayerMovement::velocity(const Point2D& vel) { velocity_ = vel; }

float PlayerMovement::speed() const { return norm(velocity_); }
float PlayerMovement::maxSpeed() const { return cMaxSpeed_; }

float PlayerMovement::speedAmount() const { return speed() / maxSpeed(); }