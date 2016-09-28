// Matching header
#include "Entities/Enemy/BladeSprite.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/GameTime/GameTime.h"
#include "Graphics/Graphics.h"
#include "Math/TransformStack.h"

// External libraries
#include <Framework/Circle2D.h>
#include <Framework/Color.h>
#include <Framework/Polygon2D.h>
#include <Framework/Transform2D.h>

// Standard libraries
#include <cmath>
#include <memory>

// ================================================================================================
//   Static attributes
// ------------------------------------------------------------------------------------------------

const float BladeSprite::cRotationSpeed_ = 8.0f;


// ================================================================================================
//   Initialization
// ------------------------------------------------------------------------------------------------

BladeSprite::BladeSprite()
    : rotation_(0.0f)
{
    Color color(0.6f, 0.2f, 0.2f);
    auto circle = std::make_shared<Circle2D>(Point2D(0.0f, 0.0f), 2.0f, color, true);

    auto blade1 = std::make_shared<Polygon2D>(color, true);
        blade1->addPoint(Point2D(0.0f, 2.0f));
        blade1->addPoint(Point2D(-8.0f, 10.0f));
        blade1->addPoint(Point2D(5.0f, 20.0f));

    auto blade2 = std::make_shared<Polygon2D>(color, true);
        blade2->addPoint(Point2D(2.0f, 0.0f));
        blade2->addPoint(Point2D(10.0f, 8.0f));
        blade2->addPoint(Point2D(20.0f, -5.0f));

    auto blade3 = std::make_shared<Polygon2D>(color, true);
        blade3->addPoint(Point2D(0.0f, -2.0f));
        blade3->addPoint(Point2D(8.0f, -10.0f));
        blade3->addPoint(Point2D(-5.0f, -20.0f));

    auto blade4 = std::make_shared<Polygon2D>(color, true);
        blade4->addPoint(Point2D(-2.0f, 0.0f));
        blade4->addPoint(Point2D(-10.0f, -8.0f));
        blade4->addPoint(Point2D(-20.0f, 5.0f));

    graphics_ = std::make_shared<Graphics>();
        graphics_->pushObject(circle);
        graphics_->pushObject(blade1);
        graphics_->pushObject(blade2);
        graphics_->pushObject(blade3);
        graphics_->pushObject(blade4);
}


// ================================================================================================
//   Update functions
// ------------------------------------------------------------------------------------------------

void BladeSprite::onIdle()
{
    rotation_ += cRotationSpeed_ * GameTime::Instance().delta();
    rotation_ = std::fmod(rotation_, 6.2831f); 
}

void BladeSprite::onTransform(TransformStack& transformStack)
{
    if (!graphics_) {
        return;
    }

    transformStack.push();
        transformStack.translate(entity().transform().position());   
        transformStack.rotate(rotation_);
        transformStack.scale(entity().transform().scale());
        
        Transform2D::loadIdentityMatrix();
        Transform2D::multiplyMatrix(transformStack.top().data);
        graphics_->applyTransform();
    transformStack.pop();
}
