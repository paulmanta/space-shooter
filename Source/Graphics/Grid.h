#ifndef GEOMETRYWARS_GRAPHICS_GRID_H
#define GEOMETRYWARS_GRAPHICS_GRID_H

// Project headers
#include "Graphics/Graphics.h"

// Forward declarations
class Color;


class Grid : public Graphics
{
  public:
    Grid(int numRows, int numCols, float lineSpacing,
         const Color& lineColor, const Color& backgroundColor);

    float width() const;
    float height() const;

  private:
    float width_;
    float height_;
};


#endif // GEOMETRYWARS_GRAPHICS_GRID_H