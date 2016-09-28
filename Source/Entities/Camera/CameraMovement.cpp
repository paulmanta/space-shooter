// Matching header
#include "Entities/Camera/CameraMovement.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntityTransform.h"
#include "Core/GameTime/GameTime.h"
#include "Core/GameWorld/GameWorld.h"
#include "Entities/Player/PlayerMovement.h"
#include "Math/VectorMath.h"

// Standard libraries
#include <algorithm>
#include <cmath>


// ================================================================================================
//   Static attributes
// ------------------------------------------------------------------------------------------------

const float CameraMovement::cShakeDuration_ = 1.5f;
const float CameraMovement::cShakeFrequency_ = 3.0f;
const float CameraMovement::cMaxShakeAmplitude_ = 20.0f;

const float CameraMovement::cMaxPlayerDistance_ = 80.0f; 
const float CameraMovement::cRecenterSpeed_ = 60.0f;
const float CameraMovement::cRemainCenteredSpeedThreshold_ = 0.1f;


// ================================================================================================
//   Initialization
// ------------------------------------------------------------------------------------------------

void CameraMovement::onInit()
{
    Entity& player = GameWorld::Instance().player();
    playerMovement_ = &dynamic_cast<PlayerMovement&>(player.movement());
    desiredPosition_ = player.transform().position();
    shakeStartTime_ = -cShakeDuration_;
    shouldRecenter_ = false;
    shouldStayCentered_ = false;
}


// ================================================================================================
//   Update and event functions
// ------------------------------------------------------------------------------------------------

void CameraMovement::onIdle()
{
    float t = GameTime::Instance().current();
    float dt = GameTime::Instance().delta();

    Point2D playerPos = GameWorld::Instance().player().transform().position();
    Point2D playerDir = playerPos - entity().transform().position();

    // If the camera should stay centered on the player, simply copy the player's position.
    // It stops following the player when his speed drops below a specified threshold.
    if (shouldStayCentered_)
    {
        desiredPosition_ = playerPos;
        shouldStayCentered_ = playerMovement_->speedAmount() > cRemainCenteredSpeedThreshold_;
    }
    // If the player is too far (and the camera needs to start recentering), or if we already
    // are in the process of recentering the camera, get closer to the player's position.
    else if (shouldRecenter_ || norm(playerDir) > cMaxPlayerDistance_)
    {
        shouldRecenter_ = true;
        float speed = playerMovement_->speed() + cRecenterSpeed_;
        desiredPosition_ = desiredPosition_ + clampNorm(playerDir, speed * dt);

        // After recentering on the player, the camera should stay centered for as long
        // as the player is still moving (i.e. until his speed drops below a threshold).
        if (desiredPosition_ == playerPos) {
            shouldStayCentered_ = true;
            shouldRecenter_ = false;
        }
    }    

    Point2D actualPosition = desiredPosition_;

    float shakeTime = t - shakeStartTime_;
    float shakeAmount = 0.0f; 

    if (shakeTime <= cShakeDuration_)
    {
        float sine = std::sin(shakeTime * cShakeFrequency_ * 6.2831f);
        float damping = std::max(1.0f - shakeTime / cShakeDuration_, 0.0f);
        actualPosition.x += sine * damping * cMaxShakeAmplitude_;
    }

    entity().transform().position(actualPosition);
}

void CameraMovement::onPlayerDamaged()
{
    shakeStartTime_ = GameTime::Instance().current();
}