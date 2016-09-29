// Project headers
#include "Core/GameScore/GameScore.h"
#include "Core/GameTime/GameTime.h"
#include "Core/GameWorld/GameWorld.h"
#include "Entities/FactoryFunctions.h"
#include "Spawners/BulletSpawner.h"
#include "Spawners/EnemySpawner.h"

// External libraries
#include <Framework/DrawingWindow.h>
#include <Framework/Visual2D.h>
#include <GL/freeglut.h>

// Standard libraries
#include <memory>

static const int cWindowWidth = 800;
static const int cWindowHeight = 500;

static std::shared_ptr<Visual2D> visual;

static GameScore& gameScore = GameScore::Instance();
static GameTime& gameTime = GameTime::Instance();
static GameWorld& gameWorld = GameWorld::Instance();

static EnemySpawner& enemySpawner = EnemySpawner::Instance();
static BulletSpawner& bulletSpawner = BulletSpawner::Instance();


void DrawingWindow::init()
{
    float xf1 = -DrawingWindow::width / 2.0f;
    float yf1 = -DrawingWindow::height / 2.0f;
    float xf2 = DrawingWindow::width / 2.0f;
    float yf2 = DrawingWindow::height / 2.0f;

    int xp1 = 0;
    int yp1 = 0;
    int xp2 = DrawingWindow::width;
    int yp2 = DrawingWindow::height;

    visual = std::make_shared<Visual2D>(xf1, yf1, xf2, yf2, xp1, yp1, xp2, yp2);
    DrawingWindow::addVisual2D(visual.get());

    gameTime.init();

    bulletSpawner.createBullets(100);
    enemySpawner.addEnemies(10, createSnakeEnemy);
    enemySpawner.addEnemies(10, createBladeEnemy);

    gameWorld.initPlayer(createPlayer());
    gameWorld.initCamera(createCamera());
    gameWorld.init(*visual);
}

void DrawingWindow::onIdle()
{
    gameTime.onIdle();
    enemySpawner.onIdle();
    gameWorld.onIdle();
    gameScore.onIdle();
}

void DrawingWindow::onKey(unsigned char key)
{
    gameWorld.onKeyDown(key);
}

void onKeyUp(unsigned char key, int x, int y)
{
    gameWorld.onKeyUp(key);
}

void onSpecialUp(int key, int x, int y)
{
    onKeyUp(key, x, y);
}

void DrawingWindow::onReshape(int width, int height)
{
	glutReshapeWindow(cWindowWidth, cWindowHeight);
}

void DrawingWindow::onMouse(int button, int state, int x, int y)
{
    // Empty
}

int main(int argc, char** argv)
{
    DrawingWindow window(argc, argv, cWindowWidth, cWindowHeight, 200, 200, "Geometry Wars");

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialUp);
    glutIgnoreKeyRepeat(1);

    DrawingWindow::init();
    DrawingWindow::run();

    return 0;
}
