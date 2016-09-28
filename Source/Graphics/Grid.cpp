// Matching header
#include "Graphics/Grid.h"

// External libraries
#include <Framework/Color.h>
#include <Framework/Line2D.h>
#include <Framework/Rectangle2d.h>


// ================================================================================================
//   Constructor
// ------------------------------------------------------------------------------------------------

Grid::Grid(int numRows, int numCols, float lineSpacing,
           const Color& lineColor, const Color& backgroundColor)
{
    width_ = numCols * lineSpacing;
    height_ = numRows * lineSpacing;

    Point2D pt1(-width_ / 2.0f, height_ / 2.0f);
    Point2D pt2(width_ / 2.0f, height_ / 2.0f);

    for (int r = 0; r <= numRows; ++r) {
        pushObject(std::make_shared<Line2D>(pt1, pt2, lineColor));
        pt1.y -= lineSpacing;
        pt2.y -= lineSpacing;
    }

    pt1.x = -width_ / 2.0f; pt1.y = height_ / 2.0f;
    pt2.x = -width_ / 2.0f; pt2.y = -height_ / 2.0f;

    for (int c = 0; c <= numCols; ++c) {
        pushObject(std::make_shared<Line2D>(pt1, pt2, lineColor));
        pt1.x += lineSpacing;
        pt2.x += lineSpacing;
    }

    pushObject(std::make_shared<Rectangle2D>(
        Point2D(-width_ / 2.0f, -height_ / 2.0f),
        width_, height_, backgroundColor, true));
}


// ================================================================================================
//   Getters
// ------------------------------------------------------------------------------------------------

float Grid::width() const { return width_; }
float Grid::height() const { return height_; }