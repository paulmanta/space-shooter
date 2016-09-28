#ifndef GEOMETRYWARS_ENTITIES_CAMERA_CAMERAMOVEMENT_H
#define GEOMETRYWARS_ENTITIES_CAMERA_CAMERAMOVEMENT_H


// Project headers
#include "Core/EntitySystem/EntityMovement.h"

// External libraries
#include <Framework/Point2D.h>

// Forward declarations
class PlayerMovement;


class CameraMovement : public EntityMovement
{
  public:
    virtual void onInit() override;
    virtual void onIdle() override;
    void onPlayerDamaged();

  private:
    static const float cShakeDuration_;
    static const float cShakeFrequency_;
    static const float cMaxShakeAmplitude_;

    static const float cMaxPlayerDistance_;
    static const float cRecenterSpeed_;
    static const float cRemainCenteredSpeedThreshold_;

    PlayerMovement* playerMovement_;

    Point2D desiredPosition_;
    float shakeStartTime_;

    bool shouldRecenter_;
    bool shouldStayCentered_;
};


#endif // GEOMETRYWARS_ENTITIES_CAMERA_CAMERAMOVEMENT_H