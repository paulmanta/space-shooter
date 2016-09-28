#ifndef GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYHEALTH_H
#define GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYHEALTH_H


// Project headers
#include "Core/EntitySystem/EntityComponent.h"

// Standard libraries
#include <memory>

// Forward declarations
class Entity;


class EntityHealth : public EntityComponent
{
  public:
    virtual ~EntityHealth() {}
    
    virtual void onInit() {}

    virtual void onIdle() {}
    virtual void onKeyDown(unsigned char) {}
    virtual void onKeyUp(unsigned char) {}

    virtual void onBulletCollision(const Entity&) {}
    virtual void onEnemyCollision(const Entity&) {}
    virtual void onPlayerCollision() {}
    virtual void onWallCollision() {}
};


#endif // GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYHEALTH_H