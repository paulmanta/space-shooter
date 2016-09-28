#ifndef GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYCOLLIDER_H
#define GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYCOLLIDER_H


// Project headers
#include "Core/EntitySystem/EntityComponent.h"

// Forward declarations
class Entity;


class EntityCollider : public EntityComponent
{
  public:
    EntityCollider();

    void radius(float);
    float radius() const;
    float scaledRadius() const;

    void collisionsEnabled(bool);
    bool collisionsEnabled() const;

  private:
    float radius_;
    bool collisionsEnabled_;
};


#endif // GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYCOLLIDER_H