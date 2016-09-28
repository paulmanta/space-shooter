#ifndef GEOMETRWARS_ENTITIES_BULLET_BULLETHEALTH_H
#define GEOMETRWARS_ENTITIES_BULLET_BULLETHEALTH_H


// Project headers
#include "Core/EntitySystem/EntityHealth.h"

// Forward declarations
class Entity;


class BulletHealth : public EntityHealth
{
  public:
    virtual void onEnemyCollision(const Entity&) override;
    virtual void onWallCollision() override;
};


#endif // GEOMETRWARS_ENTITIES_BULLET_BULLETHEALTH_H