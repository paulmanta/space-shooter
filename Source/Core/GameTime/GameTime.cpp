// Matching header
#include "Core/GameTime/GameTime.h"

// External libraries
#include <GL/freeglut.h>


// ================================================================================================
//   Singleton implementation
// ------------------------------------------------------------------------------------------------

GameTime& GameTime::Instance()
{
    static GameTime instance;
    return instance;
}

GameTime::GameTime() {}
GameTime::~GameTime() {}
GameTime::GameTime(const GameTime&) {}
const GameTime& GameTime::operator=(const GameTime&) { return *this; }


// ================================================================================================
//   Init and update
// ------------------------------------------------------------------------------------------------

void GameTime::init()
{
    initTime_ = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    lastUpdateTime_ = 0.0f;
    deltaTime_ = 0.0f;
}

void GameTime::onIdle()
{
    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f - initTime_;
    deltaTime_ = time - lastUpdateTime_;
    lastUpdateTime_ = time;
}


// ================================================================================================
//   Getters
// ------------------------------------------------------------------------------------------------

float GameTime::current() const { return lastUpdateTime_; }
float GameTime::delta() const { return deltaTime_; }


