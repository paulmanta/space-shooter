#ifndef GEOMETRYWARS_ENTITIES_FACTORYFUNCTIONS_H
#define GEOMETRYWARS_ENTITIES_FACTORYFUNCTIONS_H


// Standard libraries
#include <memory>

// Forward declarations
class Entity;


std::shared_ptr<Entity> createPlayer();
std::shared_ptr<Entity> createBullet();

std::shared_ptr<Entity> createSnakeEnemy();
std::shared_ptr<Entity> createBladeEnemy();

std::shared_ptr<Entity> createCamera();


#endif // GEOMETRYWARS_ENTITIES_FACTORYFUNCTIONS_H