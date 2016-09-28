// Matching header
#include "Core/GameWorld/GameWorld.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntitySprite.h"
#include "Core/EntitySystem/EntityTransform.h"
#include "Graphics/Grid.h"
#include "Math/VectorMath.h"

// External libraries
#include <Framework/Transform2D.h>
#include <Framework/Visual2D.h>

// Standard libraries
#include <algorithm>
#include <cassert>
#include <memory>


// ================================================================================================
//   Singleton implementation
// ------------------------------------------------------------------------------------------------

GameWorld& GameWorld::Instance()
{
    static GameWorld instance;
    return instance;
}

GameWorld::GameWorld() {}
GameWorld::~GameWorld() {}
GameWorld::GameWorld(const GameWorld&) {}
const GameWorld& GameWorld::operator=(const GameWorld&) { return *this; }


// ================================================================================================
//   Initialization
//- -----------------------------------------------------------------------------------------------

void GameWorld::init(Visual2D& visual)
{
    assert(player_);
    assert(camera_);

    camera_->onInit();
    camera_->onRegisterSprite(visual);

    player_->onInit();
    player_->onRegisterSprite(visual);

    for (auto enemy : enemies_) {
        enemy->onInit();
        enemy->onRegisterSprite(visual);
    }

    for (auto bullet : bullets_) {
        bullet->onInit();
        bullet->onRegisterSprite(visual);
    }

    grid_ = std::make_shared<Grid>(8, 16, 100.0f, Color(0.6f, 0.6f, 0.6f), Color(0, 0, 0));
    grid_->registerObjects(visual);
}

void GameWorld::initPlayer(std::shared_ptr<Entity> player)
{
    assert(!player_);
    player_ = player;
}

void GameWorld::initCamera(std::shared_ptr<Entity> camera)
{
    assert(!camera_);
    camera_ = camera;
}

void GameWorld::addBullet(std::shared_ptr<Entity> bullet)
{
    bullets_.push_back(bullet);
}

void GameWorld::addEnemy(std::shared_ptr<Entity> enemy)
{
    enemies_.push_back(enemy);
}


// ================================================================================================
//   Public update functions
// ------------------------------------------------------------------------------------------------

void GameWorld::onIdle()
{
    updateEntities();
    checkCollisions();
    applyTransforms();
}

void GameWorld::onKeyDown(unsigned char key)
{
    player_->onKeyDown(key);
    camera_->onKeyDown(key);

    for (auto enemy : enemies_) {
        enemy->onKeyDown(key);
    }

    for (auto bullet : bullets_) {
        bullet->onKeyDown(key);
    }
}

void GameWorld::onKeyUp(unsigned char key)
{
    player_->onKeyUp(key);
    camera_->onKeyUp(key);

    for (auto enemy : enemies_) {
        enemy->onKeyUp(key);
    }

    for (auto bullet : bullets_) {
        bullet->onKeyUp(key);
    }
}


// ================================================================================================
//   Private update functions
// ------------------------------------------------------------------------------------------------

void GameWorld::updateEntities()
{
    player_->onIdle();
    boundCoords(*player_);

    for (auto enemy : enemies_) {
        enemy->onIdle();
        boundCoords(*enemy);
    }

    for (auto bullet : bullets_) {
        bullet->onIdle();
        boundCoords(*bullet);
    }

    // Don't check to see if the camera's position is within the bounds of the world
    // as for the other entities. This allows for some nicer effects to to take place
    // (like the camera shaking) even when it is close to the edge of the world.
    camera_->onIdle();
    //boundCoords(*camera);
}

void GameWorld::boundCoords(Entity& entity)
{
    float xLower = -width() / 2.0f;
    float yLower = -height() / 2.0f;

    float xUpper = width() / 2.0f;
    float yUpper = height() / 2.0f;

    float x = entity.transform().position().x;
    x = std::min(x, xUpper - entity.collider().scaledRadius());
    x = std::max(x, xLower + entity.collider().scaledRadius());

    float y = entity.transform().position().y;
    y = std::min(y, yUpper - entity.collider().scaledRadius());
    y = std::max(y, yLower + entity.collider().scaledRadius());

    if (entity.transform().position().x != x || entity.transform().position().y != y) {
        entity.transform().position(Point2D(x, y));
        entity.onWallCollision();
    }
}

void GameWorld::applyTransforms()
{
    transformStack_.push();
        transformStack_.rotate(-camera_->transform().rotation());
        transformStack_.scale(1.0f / camera_->transform().scale());
        transformStack_.translate(-1.0f * camera_->transform().position());
        
        player_->onTransformSprite(transformStack_);
        camera_->onTransformSprite(transformStack_);

        for (auto enemy : enemies_) {
            enemy->onTransformSprite(transformStack_);
        }

        for (auto bullet : bullets_) {
            bullet->onTransformSprite(transformStack_);
        }

        Transform2D::loadIdentityMatrix();
        Transform2D::multiplyMatrix(transformStack_.top().data);
        grid_->applyTransform();
    transformStack_.pop();
}


void GameWorld::checkCollisions()
{
    for (auto enemy : enemies_) {
        if (collisionOccured(*player_, *enemy)) {
            player_->onEnemyCollision(*enemy);
            enemy->onPlayerCollision();
        }
    }

    for (auto enemy : enemies_) {
        for (auto bullet : bullets_) {
            if (collisionOccured(*enemy, *bullet)) {
                enemy->onBulletCollision(*bullet);
                bullet->onEnemyCollision(*enemy);
            }
        }
    }

    for (auto enemy1 : enemies_) {
        for (auto enemy2 : enemies_) {
            if (collisionOccured(*enemy1, *enemy2)) {
                enemy1->onEnemyCollision(*enemy2);
                enemy2->onEnemyCollision(*enemy1);
            }
        }
    }
}

bool GameWorld::collisionOccured(const Entity& a, const Entity& b)
{
    if (&a == &b) {
        return false;
    }

    if (!a.enabled() || !b.enabled()) {
        return false;
    }

    if (!a.collider().collisionsEnabled() || !b.collider().collisionsEnabled()) {
        return false;
    }

    float distance = norm(a.transform().position() - b.transform().position());
    float collisionDistance = a.collider().scaledRadius() + b.collider().scaledRadius();
    return distance <= collisionDistance;
}


// ================================================================================================
//   Getters
// ------------------------------------------------------------------------------------------------

Entity& GameWorld::player() { return *player_; }
Entity& GameWorld::camera() { return *camera_; }

float GameWorld::width() const { return grid_->width(); }
float GameWorld::height() const { return grid_->height(); }