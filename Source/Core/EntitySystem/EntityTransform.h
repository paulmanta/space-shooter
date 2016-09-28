#ifndef GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYTRANSFORM_H
#define GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYTRANSFORM_H


// Project headers
#include "Core/EntitySystem/EntityComponent.h"

// External libraries
#include <Framework/Point2D.h>


class EntityTransform : public EntityComponent
{
  public:
    EntityTransform();

    const Point2D& position() const;
    void position(const Point2D&);

    const Point2D& scale() const;
    void scale(const Point2D&);

    float rotation() const;
    void rotation(float);

  private:
    Point2D position_;
    Point2D scale_;
    float rotation_;
};


#endif // GEOMETRYWARS_CORE_ENTITYSYSTEM_ENTITYTRANSFORM_H