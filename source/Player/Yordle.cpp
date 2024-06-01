#include "pch.h"
#include "Yordle.h"

Yordle::Yordle(Texture& texture, float xPos, float yPos)
{
	this->createSprite(&texture);
	this->asignarEstadisticas(this->stats, 10, 10, 11, 26, 16, 27);
	this->setPosition(xPos, yPos);
	this->createAnimationComponent(texture);
	this->animations->addAnimation("Idle", 0, 7, 3, 7, 21, 13, 0.2f);
	this->animations->addAnimation("Walk", 0, 11, 8, 11, 21, 13, 0.2f);
	this->animations->addAnimation("Defend", 0, 15, 5, 15, 21, 13, 0.2f);
	this->animations->addAnimation("Attack", 0, 19, 12, 19, 21, 13, 0.2f);
	this->animations->addAnimation("Dead", 0, 20, 5, 20, 21, 13, 0.2f);
	this->animations->addAnimation("Hurt", 0, 3, 2, 3, 21, 13, 0.2f);
	this->currenStateAnim = typeOfAnimation::Idle_Anim;
}

Yordle::~Yordle()
{
}

void Yordle::update(const float& deltaT)
{
    if (this->animationRequested)
    {
        switch (currenStateAnim)
        {
        case typeOfAnimation::Idle_Anim:
            this->animations->play("Idle", deltaT);
            break;
        case typeOfAnimation::Walk_Anim:
            this->animations->play("Walk", deltaT);
            break;
        case typeOfAnimation::Defend_Anim:
            this->animations->play("Defend", deltaT);
            break;
        case typeOfAnimation::Attack_Anim:
            this->animations->play("Attack", deltaT);
            break;
        case typeOfAnimation::Dead_Anim:
            this->animations->play("Dead", deltaT);
            break;
        case typeOfAnimation::Hurt_Anim:
            this->animations->play("Hurt", deltaT);
            break;
        default:
            break;
        }

    }

    if (this->animations->getAnimations("Attack")->isFinished() ||
        this->animations->getAnimations("Defend")->isFinished() ||
        this->animations->getAnimations("Dead")->isFinished() ||
        this->animations->getAnimations("Hurt")->isFinished() || 
        this->animations->getAnimations("Walk")->isFinished()) {
        // Volver al estado de inactividad
        currenStateAnim = typeOfAnimation::Idle_Anim;
        this->animationRequested = false;
    }

    // Si no hay animación solicitada, jugar la animación Idle
    if (!this->animationRequested) {
        this->animations->play("Idle", deltaT);
    }
}

void Yordle::setNextAnimation(typeOfAnimation xd)
{
}

void Yordle::setCurrentAnimation(typeOfAnimation xd)
{
    this->currenStateAnim = xd;
    this->animationRequested = true;
}

void Yordle::setTypeAnim(unsigned int typeAnim)
{
}

unsigned int Yordle::getTypeAnim()
{
	return 0;
}
