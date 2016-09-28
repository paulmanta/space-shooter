// Matching header
#include "Entities/Enemy/EnemyHealth.h"

// Project headers
#include "Core/GameScore/GameScore.h"
#include "Spawners/EnemySpawner.h"


// ================================================================================================
//   Collision events
// ------------------------------------------------------------------------------------------------

void EnemyHealth::onBulletCollision(const Entity&)
{
    GameScore::Instance().onEnemyKilled();
    EnemySpawner::Instance().unspawn(entity());
}

void EnemyHealth::onPlayerCollision()
{
    EnemySpawner::Instance().unspawn(entity());
}
