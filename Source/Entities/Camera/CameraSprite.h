#ifndef GEOMETRYWARS_ENTITIES_CAMERA_CAMERASPRITE_H
#define GEOMETRYWARS_ENTITIES_CAMERA_CAMERASPRITE_H

// Project headers
#include "Core/EntitySystem/EntitySprite.h"

// Standard libraries
#include <memory>
#include <string>

// Forward declarations
class FilledBar;
class PlayerWeapon;
class PlayerHealth;
class Text;
class TransformStack;
class Visual2D;


class CameraSprite : public EntitySprite
{
  public:
    virtual void onInit() override;
    virtual void onRegisterGraphics(Visual2D&) override;

    virtual void onIdle() override;
    virtual void onTransform(TransformStack&) override;

  private:
    static const int cMaxScoreDigits_;
    static const char cScoreThousandsSeparator_;

    std::string getFormattedScore();

    const PlayerWeapon* playerWeapon_;
    const PlayerHealth* playerHealth_;

    std::shared_ptr<FilledBar> ammoBar_;
    std::shared_ptr<FilledBar> healthBar_;
    std::shared_ptr<Text> score_;
};


#endif // GEOMETRYWARS_ENTITIES_CAMERA_CAMERASPRITE_H