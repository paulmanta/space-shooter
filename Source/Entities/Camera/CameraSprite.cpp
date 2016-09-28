// Matching header
#include "Entities/Camera/CameraSprite.h"

// Project headers
#include "Core/EntitySystem/Entity.h"
#include "Core/GameScore/GameScore.h"
#include "Core/GameWorld/GameWorld.h"
#include "Entities/Player/PlayerWeapon.h"
#include "Entities/Player/PlayerHealth.h"
#include "Graphics/FilledBar.h"

// External libraries
#include <Framework/DrawingWindow.h>
#include <Framework/Text.h>
#include <Framework/Transform2D.h>
#include <Framework/Visual2D.h>

// Standard libraries
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>


// ================================================================================================
//   Static attributes
// ------------------------------------------------------------------------------------------------

const int CameraSprite::cMaxScoreDigits_ = 7;
const char CameraSprite::cScoreThousandsSeparator_ = ',';


// ================================================================================================
//   Initialization
// ------------------------------------------------------------------------------------------------

void CameraSprite::onInit()
{
    Entity& player = GameWorld::Instance().player();
    playerWeapon_ = &dynamic_cast<PlayerWeapon&>(player.weapon());
    playerHealth_ = &dynamic_cast<PlayerHealth&>(player.health());

    int w = DrawingWindow::width;
    int h = DrawingWindow::height;

    ammoBar_ = std::make_shared<FilledBar>(Color(0.5, 1.0f, 0.0f), w * 0.2f, h * 0.03f);
    ammoBar_->position(Point2D(w / 2.0f - ammoBar_->width() - w * 0.03f,
                               h / 2.0f - ammoBar_->height() - 50.0f));

    healthBar_ = std::make_shared<FilledBar>(Color(1.0f, 0.3f, 0.0f), w * 0.2f, h * 0.03f);
    healthBar_->position(Point2D(w / 2.0f - healthBar_->width() - w * 0.03f,
                                 h / 2.0f - healthBar_->height() - 20.0f));

    score_ = std::make_shared<Text>(getFormattedScore());
    score_->pos = Point2D(-w / 2.0f + 20.0f, h / 2.0f - 40.0f);
    score_->color = Color(1.0f, 1.0f, 1.0f);
    score_->font = BITMAP_TIMES_ROMAN_24;
}

void CameraSprite::onRegisterGraphics(Visual2D& visual)
{
    ammoBar_->registerObjects(visual);
    healthBar_->registerObjects(visual);
    DrawingWindow::addText_to_Visual2D(score_.get(), &visual);
}


// ================================================================================================
//   Overridden functions
// ------------------------------------------------------------------------------------------------

void CameraSprite::onIdle()
{
    ammoBar_->amount(playerWeapon_->ammoAmount());
    healthBar_->amount(playerHealth_->healthAmount());
    score_->text = getFormattedScore();
}

void CameraSprite::onTransform(TransformStack& transformStack)
{
    Transform2D::loadIdentityMatrix();
    ammoBar_->applyTransform();
    healthBar_->applyTransform();
}


// ================================================================================================
//   Private functions
// ------------------------------------------------------------------------------------------------

std::string CameraSprite::getFormattedScore()
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(cMaxScoreDigits_) << GameScore::Instance().currentScore();

    std::string score = ss.str();
    score = score.substr(score.size() - cMaxScoreDigits_);

    for (int i = score.size() - 3; i > 0; i -= 3) {
        score.insert(i, 1, cScoreThousandsSeparator_);
    }

    return score;
}