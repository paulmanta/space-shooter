#ifndef GEOMETRYWARS_ENTITIES_ENEMY_ENEMYHEALTH_H
#define GEOMETRYWARS_ENTITIES_ENEMY_ENEMYHEALTH_H


// Project headers
#include "Core/EntitySystem/EntityHealth.h"

// Forward declarations
class Entity;


class EnemyHealth : public EntityHealth
{
  public:
    virtual void onBulletCollision(const Entity&) override;
    virtual void onPlayerCollision() override;
};


#endif // GEOMETRYWARS_ENTITIES_ENEMY_ENEMYHEALTH_H