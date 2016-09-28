// Matching header
#include "Spawners/BulletSpawner.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/GameWorld/GameWorld.h"
#include "Entities/FactoryFunctions.h"

// Standard libraries
#include <algorithm>
#include <cassert>
#include <memory>


// ================================================================================================
//   Singeton implementation
// ------------------------------------------------------------------------------------------------

BulletSpawner& BulletSpawner::Instance()
{
    static BulletSpawner instance;
    return instance;
} 

BulletSpawner::BulletSpawner() {}
BulletSpawner::~BulletSpawner() {}
BulletSpawner::BulletSpawner(const BulletSpawner&) {}
const BulletSpawner& BulletSpawner::operator=(const BulletSpawner&) { return *this; }


// ================================================================================================
//   Initialization
// ------------------------------------------------------------------------------------------------

void BulletSpawner::createBullets(int maxBullets)
{
    for (int i = 0; i < maxBullets; ++i)
    {
        auto bullet = createBullet();
        bullet->enabled(false);

        disabled_.push_back(bullet);
        GameWorld::Instance().addBullet(bullet);
    }
}


// ================================================================================================
//   Spawn, unspawn
// ------------------------------------------------------------------------------------------------

Entity& BulletSpawner::spawn()
{
    if (!disabled_.empty())
    {
        auto bullet = disabled_.back();
        disabled_.pop_back();

        assert(!bullet->enabled());
        bullet->enabled(true);
        bullet->onInit();

        enabled_.push_back(bullet);
        return *bullet;
    }
    else
    {
        enabled_.push_back(enabled_.front());
        enabled_.pop_front();
        return *enabled_.back();
    }
}

void BulletSpawner::unspawn(Entity& bullet)
{
    auto it = std::find_if(enabled_.begin(), enabled_.end(),
        [&bullet](const std::shared_ptr<Entity>& other) -> bool {
            return other.get() == &bullet;
        }
    );

    assert(it != enabled_.end());
    assert((*it)->enabled());
    
    (*it)->enabled(false);
    disabled_.push_back(*it);
    enabled_.erase(it);
}