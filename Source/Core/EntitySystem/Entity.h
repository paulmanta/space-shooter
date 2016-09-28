#ifndef GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITY_H
#define GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITY_H


// Project headers
#include "Core/EntitySystem/EntityCollider.h"
#include "Core/EntitySystem/EntityTransform.h"

// Standard libraries
#include <memory>

// Forward declarations
class EntityWeapon;
class EntityHealth;
class EntityMovement;
class EntitySprite;
class TransformStack;
class Visual2D;


#define INLINE_COMPONENT_GETTERS(TYPE, NAME, MEMBER)      \
    inline TYPE& NAME() { return MEMBER; }                \
    inline const TYPE& NAME() const { return MEMBER; }

#define INLINE_COMPONENT_PTR_GETTERS(TYPE, NAME, MEMBER)  \
    inline TYPE& NAME() { return *MEMBER; }               \
    inline const TYPE& NAME() const { return *MEMBER; }


class Entity
{
  public:
    Entity(std::unique_ptr<EntityHealth>,
           std::unique_ptr<EntityMovement>,
           std::unique_ptr<EntitySprite>,
           std::unique_ptr<EntityWeapon>);

    void enabled(bool);
    bool enabled() const;

    void onInit();
    void onRegisterSprite(Visual2D&);

    void onIdle();
    void onKeyDown(unsigned char);
    void onKeyUp(unsigned char);
    void onTransformSprite(TransformStack&);

    void onBulletCollision(const Entity&);
    void onEnemyCollision(const Entity&);
    void onPlayerCollision();
    void onWallCollision();

    INLINE_COMPONENT_GETTERS(EntityCollider, collider, collider_)
    INLINE_COMPONENT_GETTERS(EntityTransform, transform, transform_)
    INLINE_COMPONENT_PTR_GETTERS(EntityHealth, health, health_)
    INLINE_COMPONENT_PTR_GETTERS(EntityMovement, movement, movement_)
    INLINE_COMPONENT_PTR_GETTERS(EntitySprite, sprite, sprite_)
    INLINE_COMPONENT_PTR_GETTERS(EntityWeapon, weapon, weapon_)

  private:
    bool enabled_;

    EntityTransform transform_;
    EntityCollider collider_;
    
    std::unique_ptr<EntityHealth> health_;
    std::unique_ptr<EntityMovement> movement_;
    std::unique_ptr<EntitySprite> sprite_;
    std::unique_ptr<EntityWeapon> weapon_;
};


#undef INLINE_COMPONENT_GETTERS
#undef INLINE_COMPONENT_PTR_GETTERS


#endif // GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITY_H