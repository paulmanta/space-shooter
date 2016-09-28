#ifndef GEOMETRYWARS_ENTITIES_ENEMY_SNAKESPRITE_H
#define GEOMETRYWARS_ENTITIES_ENEMY_SNAKESPRITE_H


// Project headers
#include "Core/EntitySystem/EntitySprite.h"

// External libraries
#include <Framework/Color.h>

// Standard libraries
#include <memory>

// Forward declarations
class FuzzyCircle;
class TransformStack;
class Visual2D;


class SnakeSprite : public EntitySprite
{
  public:
    SnakeSprite();
    virtual void onIdle() override;
    virtual void onRegisterGraphics(Visual2D&) override;
    virtual void onTransform(TransformStack&) override;

  private:
    static const float cBodyRadius_;
    static const float cTailRadiusRatio_;
    static const int cTailLength_;
    static const Color cColor_; 

    std::shared_ptr<FuzzyCircle> body_;
    std::vector<std::shared_ptr<FuzzyCircle>> tail_;
};


#endif // GEOMETRYWARS_ENTITIES_ENEMY_SNAKESPRITE_H