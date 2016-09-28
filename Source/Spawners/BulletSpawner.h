#ifndef GEOMETRYWARS_SPAWNERS_BULLETSPAWNER_H
#define GEOMETRYWARS_SPAWNERS_BULLETSPAWNER_H


// Standard libraries
#include <memory>
#include <deque>

// Forward declarations
class Entity;


class BulletSpawner
{
  public:
    static BulletSpawner& Instance();
    void createBullets(int maxBullets);
    Entity& spawn();
    void unspawn(Entity&);

  private:
    BulletSpawner();
    ~BulletSpawner();
    BulletSpawner(const BulletSpawner&);
    const BulletSpawner& operator=(const BulletSpawner&);

  private:
    std::deque<std::shared_ptr<Entity>> enabled_;
    std::deque<std::shared_ptr<Entity>> disabled_;
};


#endif // GEOMETRYWARS_SPAWNERS_BULLETSPAWNER_H