#ifndef GEOMETRYWARS_ENTITIES_PLAYER_PLAYERWEAPON_H
#define GEOMETRYWARS_ENTITIES_PLAYER_PLAYERWEAPON_H


// Project headers
#include "Core/EntitySystem/EntityWeapon.h"

// External libraries
#include <Framework/Point2D.h>


class PlayerWeapon : public EntityWeapon
{
  public:
    virtual void onInit();
    virtual void onIdle();
    virtual void onKeyDown(unsigned char);
    virtual void onKeyUp(unsigned char);

    int ammoCapacity() const;
    int currentAmmo() const;
    float ammoAmount() const;

  private:
    static const int cAmmoCapacity_;
    static const float cAmmoRefillRate_;
    static const float cAmmoRefillDelay_;
    static const float cFiringPeriod_;
    static const Point2D cBulletSpawnPositionOffset_;

    float currentAmmo_;
    float lastShotTime_;
    bool shooting_;
};


#endif // GEOMETRYWARS_ENTITIES_PLAYER_PLAYERWEAPON_H