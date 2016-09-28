// Matching header
#include "Graphics/FilledBar.h"

// External libraries
#include <Framework/Color.h>
#include <Framework/Rectangle2d.h>

// Standard libraries
#include <stdexcept>


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

FilledBar::FilledBar(const Color& color, float width, float height)
    : amount_(1.0f),
      width_(width),
      height_(height)
{
    rectangle_ = std::make_shared<Rectangle2D>(Point2D(0.0f, 0.0f), width, height, color, true);
    pushObject(rectangle_);
}


// ================================================================================================
//   Getters and setters
// ------------------------------------------------------------------------------------------------

float FilledBar::amount() const { return amount_; }
float FilledBar::width() const { return width_; }
float FilledBar::height() const { return height_; }

void FilledBar::amount(float value)
{
    if (value < 0.0f || value > 1.0f) {
        throw std::invalid_argument("Amount must be in the closed interval [0, 1].");
    }
    
    rectangle_->points[1]->x = rectangle_->points[0]->x + (width_ * value);
    rectangle_->points[2]->x = rectangle_->points[3]->x + (width_ * value);
    amount_ = value;
}