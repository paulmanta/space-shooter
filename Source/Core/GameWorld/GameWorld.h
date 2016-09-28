#ifndef GEOMETRYWARS_CORE_GAMEWORLD_GAMEWORLD_H
#define GEOMETRYWARS_CORE_GAMEWORLD_GAMEWORLD_H


// Project headers
#include "Math/TransformStack.h"

// Standard libraries
#include <memory>
#include <vector>

// Forward declarations
class Entity;
class Grid;
class Visual2D;

class GameWorld
{
  public:
    static GameWorld& Instance();

    void init(Visual2D&);

    void initPlayer(std::shared_ptr<Entity>);
    void initCamera(std::shared_ptr<Entity>);

    void addBullet(std::shared_ptr<Entity>);
    void addEnemy(std::shared_ptr<Entity>);

    void onIdle();
    void onKeyUp(unsigned char);
    void onKeyDown(unsigned char);
    
    float width() const;
    float height() const;

    Entity& player();
    Entity& camera();

  private:
    GameWorld();
    ~GameWorld();
    GameWorld(const GameWorld&);
    const GameWorld& operator=(const GameWorld&);
    
    void updateEntities();
    void boundCoords(Entity&); 
    void checkCollisions();
    bool collisionOccured(const Entity&, const Entity&);
    void applyTransforms();

  private:
    TransformStack transformStack_;

    std::shared_ptr<Entity> player_;
    std::shared_ptr<Entity> camera_;
    
    std::vector<std::shared_ptr<Entity>> enemies_;
    std::vector<std::shared_ptr<Entity>> bullets_;

    std::shared_ptr<Grid> grid_;
};


#endif // GEOMETRYWARS_CORE_GAMEWORLD_GAMEWORLD_H