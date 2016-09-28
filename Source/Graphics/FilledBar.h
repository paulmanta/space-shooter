#ifndef GEOMETRYWARS_GRAPHICS_FILLEDBAR_H
#define GEOMETRYWARS_GRAPHICS_FILLEDBAR_H


// Project headers
#include "Graphics/Graphics.h"

// Standard libraries
#include <memory>

// Forward declarations
class Rectangle2D;


class FilledBar : public Graphics
{
  public:
    FilledBar(const Color&, float width, float height);
    
    float amount() const;
    void amount(float);

    float width() const;
    float height() const;

  private:
    std::shared_ptr<Rectangle2D> rectangle_;
    float width_;
    float height_;
    float amount_;    
};


#endif // GEOMETRYWARS_GRAPHICS_FILLEDBAR_H
