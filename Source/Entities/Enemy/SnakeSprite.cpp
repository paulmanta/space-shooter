// Matching header
#include "Entities/Enemy/SnakeSprite.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Graphics/FuzzyCircle.h"
#include "Math/TransformStack.h"
#include "Math/VectorMath.h"

// External libraries
#include <Framework/Transform2D.h>

// Standard libraries
#include <cmath>
#include <memory>


// ================================================================================================
//   Static attributes
// ------------------------------------------------------------------------------------------------

const float SnakeSprite::cBodyRadius_ = 15.0f;
const float SnakeSprite::cTailRadiusRatio_ = 0.75f;
const int SnakeSprite::cTailLength_ = 5;
const Color SnakeSprite::cColor_(1.0f, 0.6f, 0.0f);


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

SnakeSprite::SnakeSprite()
{
    body_ = std::make_shared<FuzzyCircle>(cBodyRadius_, cColor_);
    graphics_ = body_;

    for (int i = 0; i < cTailLength_; ++i)
    {
        float radius = cBodyRadius_ * std::pow(cTailRadiusRatio_, i + 1);
        Point2D position = (i + 1.0f) * Point2D(0.0f, -2.0f * cBodyRadius_);
        tail_.push_back(std::make_shared<FuzzyCircle>(radius, cColor_));
        tail_.back()->position(position);
    }
}


// ================================================================================================
//   Overridden functions
// ---------------------------------------------------------------------------

void SnakeSprite::onIdle()
{
    Point2D prevPosition = entity().transform().position();
    float prevRadius = body_->innerRadius();

    for (std::size_t i = 0; i < tail_.size(); ++i)
    {
        Point2D thisPosition = tail_[i]->position();
        float thisRadius = tail_[i]->innerRadius();

        Point2D direction = thisPosition - prevPosition;
        direction = resize(direction, thisRadius + prevRadius);

        tail_[i]->position(prevPosition + direction);

        prevPosition = tail_[i]->position();
        prevRadius = thisRadius;
    }
}

void SnakeSprite::onRegisterGraphics(Visual2D& visual)
{
    EntitySprite::onRegisterGraphics(visual);

    for (auto geom : tail_) {
        geom->registerObjects(visual);
    }
}

void SnakeSprite::onTransform(TransformStack& transformStack)
{
    EntitySprite::onTransform(transformStack);

    transformStack.push();
        transformStack.translate(entity().transform().position());
        transformStack.scale(entity().transform().scale());
        transformStack.translate(-1.0f * entity().transform().position());

        Transform2D::loadIdentityMatrix();
        Transform2D::multiplyMatrix(transformStack.top().data);

        for (auto geometry : tail_) {
            geometry->applyTransform();
        }
    transformStack.pop();
}