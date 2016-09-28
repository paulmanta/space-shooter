// Matching header
#include "Core/GameScore/GameScore.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/GameTime/GameTime.h"
#include "Core/GameWorld/GameWorld.h"


// ================================================================================================
//   Sitatic attributes
// ------------------------------------------------------------------------------------------------

const int GameScore::cEnemyKilledPoints_ = 100;
const float GameScore::cNoKillsPenaltyRate_ = 10.0f;
const float GameScore::cNoKillsPenaltyDelay_ = 4.0f;


// ================================================================================================
//   Singleton implementation
// ------------------------------------------------------------------------------------------------

GameScore& GameScore::Instance()
{
    static GameScore instance;
    return instance;
}

GameScore::GameScore()
    : currentScore_(0),
      timeLastKill_(-cNoKillsPenaltyDelay_),
      timeLastPenalty_(0.0f)
{
    // Empty
}

GameScore::~GameScore() {}
GameScore::GameScore(const GameScore&) {}
const GameScore& GameScore::operator=(const GameScore&) { return *this; }


// ================================================================================================
//   Update functions
// ------------------------------------------------------------------------------------------------

void GameScore::onIdle()
{
    if (!GameWorld::Instance().player().enabled()) {
        return;  // Don't penalize if the player has been killed
    }

    if (GameTime::Instance().current() - timeLastKill_ > cNoKillsPenaltyDelay_)
    {
        float timePassed = GameTime::Instance().current() - timeLastPenalty_;
        int numPenalties = static_cast<int>(timePassed * cNoKillsPenaltyRate_);

        currentScore_ -= numPenalties;
        currentScore_ = currentScore_ < 0 ? 0 : currentScore_;

        timeLastPenalty_ += numPenalties / cNoKillsPenaltyRate_; 
    }
}

void GameScore::onEnemyKilled()
{
    currentScore_ += cEnemyKilledPoints_;
    timeLastKill_ = timeLastPenalty_ = GameTime::Instance().current();
}


// ================================================================================================
//   Getters
// ------------------------------------------------------------------------------------------------

int GameScore::currentScore() const
{
    return currentScore_;
}