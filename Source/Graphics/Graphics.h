#ifndef GEOMETRYWARS_GRAPHICS_GRAPHICS_H
#define GEOMETRYWARS_GRAPHICS_GRAPHICS_H


// External libraries
#include <Framework/Point2D.h>

// Standard libraries
#include <memory>
#include <vector>

// Forward declarations
class Object2D;
class Visual2D;


class Graphics
{
  public:
    Graphics();
    
    void pushObject(std::shared_ptr<Object2D>);
    void registerObjects(Visual2D&);

    void position(const Point2D&);
    const Point2D& position() const;

    void applyTransform();

  private:
    std::vector<std::shared_ptr<Object2D>> objects_;
    Point2D position_;
};


#endif // GEOMETRYWARS_GRAPHICS_GRAPHICS_H