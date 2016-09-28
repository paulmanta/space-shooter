#ifndef GEOMETRYWARS_SPAWNERS_ENEMYSPAWNER_H
#define GEOMETRYWARS_SPAWNERS_ENEMYSPAWNER_H


// Standard libraries
#include <memory>
#include <deque>

// Forward declarations
class Entity;


class EnemySpawner
{
  public:
    static EnemySpawner& Instance();
    void addEnemies(std::size_t numEnemies, std::shared_ptr<Entity> (*create)());
    void onIdle();
    void unspawn(Entity&);

  private:
    EnemySpawner();
    ~EnemySpawner();
    EnemySpawner(const EnemySpawner&);
    const EnemySpawner& operator=(const EnemySpawner&);

  private:
    static const float cEnemySpawnRate_;
    static const float cSpawnPlayerDistance_;
    static const float cMaxSpawnSpread_;

    std::deque<std::shared_ptr<Entity>> disabled_;
    std::deque<std::shared_ptr<Entity>> enabled_;
    float timeLastSpawn_;
};


#endif // GEOMETRYWARS_SPAWNERS_ENEMYSPAWNER_H