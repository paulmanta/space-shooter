// Matching header
#include "Core/EntitySystem/Entity.h"

// Project headers
#include "Core/EntitySystem/EntityWeapon.h"
#include "Core/EntitySystem/EntityCollider.h"
#include "Core/EntitySystem/EntityHealth.h"
#include "Core/EntitySystem/EntityMovement.h"
#include "Core/EntitySystem/EntitySprite.h"
#include "Core/EntitySystem/EntityTransform.h"
#include "Math/TransformStack.h"

// External libraries
#include <Framework/Point2D.h>
#include <Framework/Visual2D.h>

// Standard libraries
#include <memory>


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

Entity::Entity(std::unique_ptr<EntityHealth> health,
               std::unique_ptr<EntityMovement> movement,
               std::unique_ptr<EntitySprite> sprite,
               std::unique_ptr<EntityWeapon> weapon)
    : enabled_(true),
      health_(std::move(health)),
      movement_(std::move(movement)),
      sprite_(std::move(sprite)),
      weapon_(std::move(weapon))
{
    collider_.entity_ = this;
    health_->entity_ = this;
    movement_->entity_ = this;
    sprite_->entity_ = this;
    transform_.entity_ = this;
    weapon_->entity_ = this;
}


// ================================================================================================
//   Initialization
// ------------------------------------------------------------------------------------------------

void Entity::onInit()
{
    if (!enabled_) {
        return;
    }

    health_->onInit();
    movement_->onInit();
    weapon_->onInit();
    sprite_->onInit();
}

void Entity::onRegisterSprite(Visual2D& visual)
{
    sprite_->onRegisterGraphics(visual);
}


// ================================================================================================
//   Update functions
// ------------------------------------------------------------------------------------------------

void Entity::onIdle()
{
    if (!enabled_) {
        return;
    }

    health_->onIdle();
    movement_->onIdle();
    weapon_->onIdle();
    sprite_->onIdle();
}

void Entity::onKeyDown(unsigned char key)
{
    if (!enabled_) {
        return;
    }

    health_->onKeyDown(key);
    movement_->onKeyDown(key);
    weapon_->onKeyDown(key);
    sprite_->onKeyDown(key);
}

void Entity::onKeyUp(unsigned char key)
{
    if (!enabled_) {
        return;
    }

    health_->onKeyUp(key);
    movement_->onKeyUp(key);
    weapon_->onKeyUp(key);
    sprite_->onKeyUp(key);
}

void Entity::onTransformSprite(TransformStack& transformStack)
{
    if (enabled_) {
        sprite_->onTransform(transformStack);
    }
    else {
        transformStack.push();
        transformStack.scale(Point2D(0.0f, 0.0f));
        sprite_->onTransform(transformStack);
        transformStack.pop();
    }
}


// ================================================================================================
//   Collision events
// ------------------------------------------------------------------------------------------------

void Entity::onBulletCollision(const Entity& bullet)
{
    if (!enabled_) {
        return;
    }

    health_->onBulletCollision(bullet);
    movement_->onBulletCollision(bullet);
    weapon_->onBulletCollision(bullet);
    sprite_->onBulletCollision(bullet);
}

void Entity::onEnemyCollision(const Entity& enemy)
{
    if (!enabled_) {
        return;
    }

    health_->onEnemyCollision(enemy);
    movement_->onEnemyCollision(enemy);
    weapon_->onEnemyCollision(enemy);
    sprite_->onEnemyCollision(enemy);
}

void Entity::onPlayerCollision()
{
    if (!enabled_) {
        return;
    }

    health_->onPlayerCollision();
    movement_->onPlayerCollision();
    weapon_->onPlayerCollision();
    sprite_->onPlayerCollision();
}

void Entity::onWallCollision()
{
    if (!enabled_) {
        return;
    }

    health_->onWallCollision();
    movement_->onWallCollision();
    weapon_->onWallCollision();
    sprite_->onWallCollision();
}


// ================================================================================================
//   Enabled
// ------------------------------------------------------------------------------------------------

void Entity::enabled(bool value) { enabled_ = value; }
bool Entity::enabled() const { return enabled_; }