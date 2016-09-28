#ifndef GEOMETRYWARS_ENTITIES_PLAYER_PLAYERMOVEMENT_H
#define GEOMETRYWARS_ENTITIES_PLAYER_PLAYERMOVEMENT_H


// Project headers
#include "Core/EntitySystem/EntityMovement.h"

// External libraries
#include <Framework/Point2D.h>

// Forward declarations
class Entity;


class PlayerMovement : public EntityMovement
{
  public:
    PlayerMovement();

    virtual void onIdle();
    virtual void onKeyDown(unsigned char);
    virtual void onKeyUp(unsigned char);

    virtual void onEnemyCollision(const Entity&);
    virtual void onWallCollision();

    const Point2D& velocity() const;
    void velocity(const Point2D&);

    float speed() const;
    float maxSpeed() const;
    float speedAmount() const;

  private:
    static const float cMaxSpeed_;
    static const float cMaxAcceleration_;
    static const float cMaxAngularSpeed_;
    static const float cBrakeFrictionFactor_;
    static const float cLateralFrictionFactor_;
    static const float cWallBounceSpeedFactor_;

    Point2D velocity_;
    bool accelerating_;
    float angularSpeed_;
};


#endif // GEOMETRYWARS_ENTITIES_PLAYER_PLAYERMOVEMENT_H