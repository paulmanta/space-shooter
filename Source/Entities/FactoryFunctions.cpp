// Matching header
#include "Entities/FactoryFunctions.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntityWeapon.h"
#include "Core/EntitySystem/EntityHealth.h"
#include "Core/EntitySystem/EntitySprite.h"

#include "Entities/Bullet/BulletHealth.h"
#include "Entities/Bullet/BulletMovement.h"

#include "Entities/Camera/CameraMovement.h"
#include "Entities/Camera/CameraSprite.h"

#include "Entities/Enemy/BladeSprite.h"
#include "Entities/Enemy/EnemyHealth.h"
#include "Entities/Enemy/EnemyMovement.h"
#include "Entities/Enemy/SnakeSprite.h"

#include "Entities/Player/PlayerHealth.h"
#include "Entities/Player/PlayerMovement.h"
#include "Entities/Player/PlayerWeapon.h"

#include "Graphics/Graphics.h"

// External libraries
#include <Framework/Point2D.h>
#include <Framework/Polygon2D.h>
#include <Framework/Rectangle2d.h>

// Standard libraries
#include <memory>


// ================================================================================================
//   Player
// ------------------------------------------------------------------------------------------------

std::shared_ptr<Entity> createPlayer()
{
    auto poly0 = std::make_shared<Polygon2D>(Color(0.5f, 0.5f, 0.5f), true);
        poly0->addPoint(Point2D(0.0f, 15.0f));
        poly0->addPoint(Point2D(20.0f, 0.0f));
        poly0->addPoint(Point2D(10.0f, -20.0f));
        poly0->addPoint(Point2D(0.0f, -15.0f));
        poly0->addPoint(Point2D(-10.0f, -20.0f));
        poly0->addPoint(Point2D(-20.0f, 0.0f));

    auto poly1 = std::make_shared<Polygon2D>(Color(0.1f, 0.3f, 1.0f), true);
        poly1->addPoint(Point2D(0.0f, 21.0f));
        poly1->addPoint(Point2D(21.0f, 0.0f));
        poly1->addPoint(Point2D(24.0f, -26.0f));
        poly1->addPoint(Point2D(0.0f, -16.0f));
        poly1->addPoint(Point2D(-24.0f, -26.0f));
        poly1->addPoint(Point2D(-21.0f, 0.0f));

    auto ship = std::shared_ptr<Graphics>(new Graphics());
        ship->pushObject(poly0);
        ship->pushObject(poly1);

    auto player = std::make_shared<Entity>(
        std::unique_ptr<EntityHealth>(new PlayerHealth()),
        std::unique_ptr<EntityMovement>(new PlayerMovement()),
        std::unique_ptr<EntitySprite>(new EntitySprite(ship)),
        std::unique_ptr<EntityWeapon>(new PlayerWeapon())
    );

    player->collider().radius(20.0f);
    player->transform().scale(Point2D(0.9f, 0.9f));
    return player;
}


// ================================================================================================
//   Bullet
// ------------------------------------------------------------------------------------------------

std::shared_ptr<Entity> createBullet()
{
    auto rect0 = std::make_shared<Rectangle2D>(
        Point2D(-1.5f, -15.0f), 3.0f, 15.0f, Color(1.0f, 1.0f, 0.0f), true);
        
    auto rect1 = std::make_shared<Rectangle2D>(
        Point2D(-3.0f, -15.0f), 6.0f, 15.0f, Color(0.0f, 1.0f, 0.0f), true);

    auto geometry = std::make_shared<Graphics>();
        geometry->pushObject(rect0);
        geometry->pushObject(rect1);

    return std::make_shared<Entity>(
        std::unique_ptr<EntityHealth>(new BulletHealth()),
        std::unique_ptr<EntityMovement>(new BulletMovement()),
        std::unique_ptr<EntitySprite>(new EntitySprite(geometry)),
        std::unique_ptr<EntityWeapon>(new EntityWeapon())
    );
}


// ================================================================================================
//   Camera
// ------------------------------------------------------------------------------------------------

std::shared_ptr<Entity> createCamera()
{
    return std::make_shared<Entity>(
        std::unique_ptr<EntityHealth>(new EntityHealth()),
        std::unique_ptr<EntityMovement>(new CameraMovement()),
        std::unique_ptr<EntitySprite>(new CameraSprite()),
        std::unique_ptr<EntityWeapon>(new EntityWeapon())
    );
}

// ================================================================================================
//   Enemies
// ------------------------------------------------------------------------------------------------

std::shared_ptr<Entity> createSnakeEnemy()
{
    auto enemy = std::make_shared<Entity>(
        std::unique_ptr<EntityHealth>(new EnemyHealth()),
        std::unique_ptr<EntityMovement>(new EnemyMovement()),
        std::unique_ptr<EntitySprite>(new SnakeSprite()),
        std::unique_ptr<EntityWeapon>(new EntityWeapon())
    );
    
    enemy->collider().radius(19.0f);
    return enemy;
}

std::shared_ptr<Entity> createBladeEnemy()
{
    auto enemy = std::make_shared<Entity>(
        std::unique_ptr<EntityHealth>(new EnemyHealth()),
        std::unique_ptr<EntityMovement>(new EnemyMovement()),
        std::unique_ptr<EntitySprite>(new BladeSprite()),
        std::unique_ptr<EntityWeapon>(new EntityWeapon())
    );

    enemy->collider().radius(23.0f);
    enemy->transform().scale(Point2D(1.2f, 1.2f));
    return enemy;
}