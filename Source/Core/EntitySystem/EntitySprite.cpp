// Matching header
#include "Core/EntitySystem/EntitySprite.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Graphics/Graphics.h"
#include "Math/TransformStack.h"

// External libraries
#include <Framework/DrawingWindow.h>
#include <Framework/Transform2D.h>
#include <Framework/Visual2D.h>

// Standard libraries
#include <memory>
#include <vector>


// ================================================================================================
//   Constructors
// ------------------------------------------------------------------------------------------------

EntitySprite::EntitySprite()
{
    // Empty
}

EntitySprite::EntitySprite(std::shared_ptr<Graphics> graphics)
    : graphics_(graphics)
{
    // Empty
}


// ================================================================================================
//   Member functions
// ------------------------------------------------------------------------------------------------

void EntitySprite::onRegisterGraphics(Visual2D& visual)
{
    if (graphics_) {
        graphics_->registerObjects(visual);
    }
}

void EntitySprite::onTransform(TransformStack& transformStack)
{
    if (!graphics_) {
        return;
    }

    transformStack.push();
        transformStack.translate(entity().transform().position());
        transformStack.rotate(entity().transform().rotation());
        transformStack.scale(entity().transform().scale());
        
        Transform2D::loadIdentityMatrix();
        Transform2D::multiplyMatrix(transformStack.top().data);
        graphics_->applyTransform();
    transformStack.pop();
}