#ifndef GEOMETRYWARS_ENTITIES_ENEMY_BLADESPRITE_H
#define GEOMETRYWARS_ENTITIES_ENEMY_BLADESPRITE_H


// Project headers
#include "Core/EntitySystem/EntitySprite.h"

// Forward declarations
class TransformStack;


class BladeSprite : public EntitySprite
{
  public:
    BladeSprite();
    virtual void onIdle() override;
    virtual void onTransform(TransformStack&) override;

   private:
     static const float cRotationSpeed_;
     float rotation_;
};


#endif // GEOMETRYWARS_ENTITIES_ENEMY_BLADESPRITE_H