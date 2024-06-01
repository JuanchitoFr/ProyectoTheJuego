#include "pch.h"
#include "Dragon.h"

Dragon::Dragon(Texture& texture, float xPos, float yPos)
{
	this->createSprite(&texture);
	this->asignarEstadisticas(this->stats, 27, 10, 16, 26, 10, 11);
	this->setPosition(xPos, yPos);
	this->createAnimationComponent(texture);
	this->animations->addAnimation("Idle", 0, 3, 2, 3, 4, 5, 0.25f);
	this->animations->addAnimation("Walk", 0, 1, 4, 1, 4, 5, 0.25f);
	this->animations->addAnimation("Defend", 0, 3, 2, 3, 4, 5, 0.25f);
	this->animations->addAnimation("Attack", 0, 2, 3, 2, 4, 5, 0.25f);
	this->animations->addAnimation("Dead", 0, 0, 4, 0, 4, 5, 0.25f);
	this->animations->addAnimation("Hurt", 0, 3, 2, 3, 4, 5, 0.25f);
	this->currenStateAnim = typeOfAnimation::Idle_Anim;
}

Dragon::~Dragon()
{
}

void Dragon::update(const float& deltaT)
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

void Dragon::setNextAnimation(typeOfAnimation xd)
{
}

void Dragon::setCurrentAnimation(typeOfAnimation xd)
{
    this->currenStateAnim = xd;
    this->animationRequested = true;

}

void Dragon::setTypeAnim(unsigned int typeAnim)
{
}

unsigned int Dragon::getTypeAnim()
{
	return 0;
}
