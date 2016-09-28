#ifndef GEOMETRYWARS_CORE_ENTITYSYTEM_ENTITYCOMPONENT_H
#define GEOMETRYWARS_CORE_ENTITYSYTEM_ENTITYCOMPONENT_H


// Forward declarations
class Entity;


class EntityComponent
{
  public:
    inline Entity& entity() { return *entity_; }
    inline const Entity& entity() const { return *entity_; } 

  private:
    friend Entity;
    Entity* entity_;
};


#endif // GEOMETRYWARS_CORE_ENTITYSYTEM_ENTITYCOMPONENT_H