// Matching header
#include "Entities/Player/PlayerWeapon.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntityTransform.h"
#include "Core/GameTime/GameTime.h"
#include "Entities/Bullet/BulletMovement.h"
#include "Entities/Player/PlayerMovement.h"
#include "Spawners/BulletSpawner.h"
#include "Math/VectorMath.h"

// External libraries
#include <Framework/Point2D.h>

// Standard libraries
#include <algorithm>
#include <memory>


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

const int PlayerWeapon::cAmmoCapacity_ = 100;
const float PlayerWeapon::cAmmoRefillDelay_ = 0.8f;
const float PlayerWeapon::cAmmoRefillRate_ = 20.0f;
const float PlayerWeapon::cFiringPeriod_ = 0.1f;


// ================================================================================================
//   Initialization
// ------------------------------------------------------------------------------------------------

void PlayerWeapon::onInit()
{
    currentAmmo_ = static_cast<float>(cAmmoCapacity_);
    lastShotTime_ = std::min(-cAmmoRefillDelay_, -cFiringPeriod_);
    shooting_ = false;
}


// ================================================================================================
//   Update functions
// ------------------------------------------------------------------------------------------------

void PlayerWeapon::onIdle()
{
    float t = GameTime::Instance().current();
    float dt = GameTime::Instance().delta();

    if (shooting_ && t - lastShotTime_ >= cFiringPeriod_ && currentAmmo_ >= 1.0f)
    {
        Entity& bullet = BulletSpawner::Instance().spawn();
        bullet.transform().position(entity().transform().position());
        bullet.transform().rotation(entity().transform().rotation());
        
        PlayerMovement& playerMovement = dynamic_cast<PlayerMovement&>(entity().movement());
        BulletMovement& bulletMovement = dynamic_cast<BulletMovement&>(bullet.movement());
        bulletMovement.playerVelocity(playerMovement.velocity());

        lastShotTime_ = t;
        currentAmmo_ -= 1.0f;
    }
    else if (t - lastShotTime_ >= cAmmoRefillDelay_ && currentAmmo_ < cAmmoCapacity_)
    {
        currentAmmo_ += cAmmoRefillRate_ * dt;
        currentAmmo_ = std::min(currentAmmo_, static_cast<float>(cAmmoCapacity_));
    }
}

void PlayerWeapon::onKeyDown(unsigned char key)
{
    if (key == 'z' || key == 'Z') {
        shooting_ = true;
    }
}

void PlayerWeapon::onKeyUp(unsigned char key)
{
    if (key == 'z' || key == 'Z') {
        shooting_ = false;
    }
}


// ================================================================================================
//   Getters
// ------------------------------------------------------------------------------------------------

int PlayerWeapon::ammoCapacity() const { return cAmmoCapacity_; }
int PlayerWeapon::currentAmmo() const { return static_cast<int>(currentAmmo_); }
float PlayerWeapon::ammoAmount() const { return currentAmmo_ / cAmmoCapacity_; }
