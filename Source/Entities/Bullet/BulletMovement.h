#ifndef GEOMETRYWARS_ENTITIES_BULLET_BULLETMOVEMENT_H
#define GEOMETRYWARS_ENTITIES_BULLET_BULLETMOVEMENT_H


// Project headers
#include "Core/EntitySystem/EntityMovement.h"

// External libraries
#include <Framework/Point2D.h>


class BulletMovement : public EntityMovement
{
  public:
    void playerVelocity(const Point2D&);
    virtual void onIdle() override;

  private:
    static const float cMovementSpeed_;
    Point2D playerVelocity_;
};


#endif // GEOMETRYWARS_ENTITIES_BULLET_BULLETMOVEMENT_H