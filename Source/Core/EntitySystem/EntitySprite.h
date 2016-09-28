#ifndef GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYSPRITE_H
#define GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYSPRITE_H


// Project headers
#include "Core/EntitySystem/EntityComponent.h"

// Standard libraries
#include <memory>
#include <vector>

// Forward declarations
class Entity;
class Graphics;
class TransformStack;
class Visual2D;


class EntitySprite : public EntityComponent
{
  public:
    EntitySprite();
    EntitySprite(std::shared_ptr<Graphics>);
    virtual ~EntitySprite() {}
    
    virtual void onInit() {}
    virtual void onRegisterGraphics(Visual2D&);

    virtual void onIdle() {}
    virtual void onKeyDown(unsigned char) {}
    virtual void onKeyUp(unsigned char) {}
    virtual void onTransform(TransformStack&);

    virtual void onBulletCollision(const Entity&) {}
    virtual void onEnemyCollision(const Entity&) {}
    virtual void onPlayerCollision() {}
    virtual void onWallCollision() {}

  protected:
    std::shared_ptr<Graphics> graphics_;
};


#endif // GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYSPRITE_H