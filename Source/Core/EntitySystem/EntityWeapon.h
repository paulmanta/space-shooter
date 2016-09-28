#ifndef GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYWEAPON_H
#define GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYWEAPON_H


// Project headers
#include "Core/EntitySystem/EntityComponent.h"

// Standard libraries
#include <memory>

// Forward declarations
class Entity;


class EntityWeapon : public EntityComponent
{
  public:
    virtual ~EntityWeapon() {}

    virtual void onInit() {}

    virtual void onIdle() {}
    virtual void onKeyDown(unsigned char) {}
    virtual void onKeyUp(unsigned char) {}

    virtual void onBulletCollision(const Entity&) {}
    virtual void onEnemyCollision(const Entity&) {}
    virtual void onPlayerCollision() {}
    virtual void onWallCollision() {}
};


#endif // GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYWEAPON_H