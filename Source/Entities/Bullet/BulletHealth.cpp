// Matching header
#include "Entities/Bullet/BulletHealth.h"

// Project headers
#include "Spawners/BulletSpawner.h"


// ================================================================================================
//   Overridden functions
// ------------------------------------------------------------------------------------------------

void BulletHealth::onEnemyCollision(const Entity&)
{
    BulletSpawner::Instance().unspawn(entity());
}

void BulletHealth::onWallCollision()
{
    BulletSpawner::Instance().unspawn(entity());
}