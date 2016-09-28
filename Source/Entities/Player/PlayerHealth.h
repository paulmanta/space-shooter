#ifndef GEOMETRYWARS_ENTITIES_PLAYER_PLAYERHEALTH_H
#define GEOMETRYWARS_ENTITIES_PLAYER_PLAYERHEALTH_H


// Project headers
#include "Core/EntitySystem/EntityHealth.h"

// Forward declarations
class Entity;
class CameraMovement;


class PlayerHealth : public EntityHealth
{
  public:
    virtual void onInit();
    virtual void onEnemyCollision(const Entity&);

    int currentHealth() const;
    int maxHealth() const;
    float healthAmount() const;

  private:
    static const int cMaxHealth_;

    CameraMovement* cameraMovement_;
    int currentHealth_;
};


#endif // GEOMETRYWARS_ENTITIES_PLAYER_PLAYERHEALTH_H