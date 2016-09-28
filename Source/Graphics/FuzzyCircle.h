#ifndef GEOMETRYWARS_GRAPHICS_FUZZYCIRCLE_H
#define GEOMETRYWARS_GRAPHICS_FUZZYCIRCLE_H

// Project headers
#include "Graphics/Graphics.h"

// External libraries
#include <Framework/Color.h>


class FuzzyCircle : public Graphics
{
  public:
    FuzzyCircle(float innerRadius, Color color);
    float innerRadius() const;
    float outerRadius() const;

  private:
    float innerRadius_;
    float outerRadius_;
};


#endif // GEOMETRYWARS_GRAPHICS_FUZZYCIRCLE_H