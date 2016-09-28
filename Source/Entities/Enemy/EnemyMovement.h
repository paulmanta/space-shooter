#ifndef GEOMETRYWARS_ENTITIES_ENEMY_ENEMYMOVEMENT_H
#define GEOMETRYWARS_ENTITIES_ENEMY_ENEMYMOVEMENT_H


// Project headers
#include "Core/EntitySystem/EntityMovement.h"

// External libraries
#include <Framework/Point2D.h>


class EnemyMovement : public EntityMovement
{
  public:
    virtual void onInit() override;
    virtual void onIdle() override;
    virtual void onEnemyCollision(const Entity&) override;

  private:
    static const float cMaxSpeed_;
    static const float cMaxAcceleration_;
    static const float cFrictionFactor_;
    static const float cEnemyRepulsionFactor_;

    Point2D velocity_;
    Point2D repulsion_;
};


#endif // GEOMETRYWARS_ENTITIES_ENEMY_ENEMYMOVEMENT_H