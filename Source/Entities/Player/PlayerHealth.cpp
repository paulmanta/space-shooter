// Matching header
#include "Entities/Player/PlayerHealth.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/GameWorld/GameWorld.h"
#include "Entities/Camera/CameraMovement.h"


// ================================================================================================
//   Static attributes
// ------------------------------------------------------------------------------------------------

const int PlayerHealth::cMaxHealth_ = 10;


// ================================================================================================
//   Overridden functions
// ------------------------------------------------------------------------------------------------

void PlayerHealth::onInit()
{
    cameraMovement_ = &dynamic_cast<CameraMovement&>(GameWorld::Instance().camera().movement());
    currentHealth_ = cMaxHealth_;
}

void PlayerHealth::onEnemyCollision(const Entity&)
{
    if (currentHealth_ > 0) {
        currentHealth_ -= 1;
        cameraMovement_->onPlayerDamaged();
    }

    if (currentHealth_ == 0) {
        entity().enabled(false);
    }
}


// ================================================================================================
//   Getters
// ------------------------------------------------------------------------------------------------

int PlayerHealth::currentHealth() const { return currentHealth_; }
int PlayerHealth::maxHealth() const { return cMaxHealth_; }

float PlayerHealth::healthAmount() const
{
    return static_cast<float>(currentHealth_) / cMaxHealth_;
}