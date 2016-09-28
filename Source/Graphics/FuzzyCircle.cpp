// Matching header
#include "Graphics/FuzzyCircle.h"

// External libraries
#include <Framework/Circle2D.h>
#include <Framework/Color.h>
#include <Framework/Point2D.h>

// Standard libraries
#include <memory>


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

FuzzyCircle::FuzzyCircle(float innerRadius, Color color)
{
    float deltaRadius = 0.05f * innerRadius;
    int numCircles = 6;

    innerRadius_ = innerRadius;
    outerRadius_ = innerRadius + (numCircles - 1) * deltaRadius;
    
    for (int i = 0; i < numCircles; ++i)
    {
        Point2D c = Point2D(0.0f, 0.0f);
        float r = innerRadius + i * deltaRadius;

        auto circle = std::make_shared<Circle2D>(c, r, color, true);
        pushObject(circle);

        color.r *= 0.7f;
        color.g *= 0.7f;
        color.b *= 0.7f;
    }
}


// ================================================================================================
//   Getters
// ------------------------------------------------------------------------------------------------

float FuzzyCircle::innerRadius() const { return innerRadius_; }
float FuzzyCircle::outerRadius() const { return outerRadius_; }