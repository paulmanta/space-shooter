// Matching header
#include "Spawners/EnemySpawner.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/GameTime/GameTime.h"
#include "Core/GameWorld/GameWorld.h"
#include "Entities/FactoryFunctions.h"
#include "Math/VectorMath.h"

// External libraries
#include <Framework/Point2D.h>

// Standard libraries
#include <algorithm>
#include <cassert>


// ================================================================================================
//   Static attributes
// ------------------------------------------------------------------------------------------------

const float EnemySpawner::cEnemySpawnRate_ = 1.0f;
const float EnemySpawner::cSpawnPlayerDistance_ = 600.0f;
const float EnemySpawner::cMaxSpawnSpread_ = 40.0f;


// ================================================================================================
//   Singeton implementation
// ------------------------------------------------------------------------------------------------

EnemySpawner& EnemySpawner::Instance()
{
    static EnemySpawner instance;
    return instance;
} 

EnemySpawner::EnemySpawner()
    : timeLastSpawn_(0.0f)
{
    // Empty
}

EnemySpawner::~EnemySpawner() {}
EnemySpawner::EnemySpawner(const EnemySpawner&) {}
const EnemySpawner& EnemySpawner::operator=(const EnemySpawner&) { return *this; }


// ================================================================================================
//   Create enemies
// -----------------------------------------------------------------------------------------------

void EnemySpawner::addEnemies(std::size_t numEnemies, std::shared_ptr<Entity> (*create)())
{
    for (std::size_t i = 0; i < numEnemies; ++i) {
        disabled_.push_back(create());
        disabled_.back()->enabled(false);
        GameWorld::Instance().addEnemy(disabled_.back());
    }
}


// ================================================================================================
//   Update functions
// ------------------------------------------------------------------------------------------------

void EnemySpawner::onIdle()
{
    float timePassed = GameTime::Instance().current() - timeLastSpawn_;
    std::size_t numEnemies = static_cast<std::size_t>(timePassed * cEnemySpawnRate_);
    numEnemies = std::min(numEnemies, disabled_.size());
    timeLastSpawn_ += numEnemies / cEnemySpawnRate_;

    Point2D playerPos = GameWorld::Instance().player().transform().position();
    Point2D spawnDir(playerPos.x < 0.0f ? 1.0f : -1.0f, playerPos.y < 0.0f ? 1.0f : -1.0f);
    spawnDir = resize(spawnDir, cSpawnPlayerDistance_);

    Point2D spawnSpread = rotate(spawnDir, -1.5705f);
    spawnSpread = resize(spawnSpread, 1.0f);

    for (std::size_t i = 0; i < numEnemies; ++i)
    {
        auto enemy = disabled_.front();
        disabled_.pop_front();

        assert(!enemy->enabled());
        enemy->enabled(true);
        enemy->onInit();
        
        float randomSpread = static_cast<float>(rand()) / RAND_MAX;
        randomSpread = (randomSpread * 2.0f * cMaxSpawnSpread_) - cMaxSpawnSpread_;
        enemy->transform().position(playerPos + spawnDir + randomSpread * spawnSpread);
        
        enabled_.push_back(enemy);
    }
}

void EnemySpawner::unspawn(Entity& enemy)
{
    auto it = std::find_if(enabled_.begin(), enabled_.end(),
        [&enemy](const std::shared_ptr<Entity>& other) -> bool {
            return other.get() == &enemy;
        }
    );

    assert(it != enabled_.end());
    assert((*it)->enabled());
    
    (*it)->enabled(false);
    disabled_.push_back(*it);
    enabled_.erase(it);
}