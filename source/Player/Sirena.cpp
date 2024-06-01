#include "pch.h"
#include "Sirena.h"

Sirena::Sirena(Texture& texture, float xPos, float yPos)
{
	this->createSprite(&texture);
	this->asignarEstadisticas(this->stats, 10, 16, 10, 11, 27, 26);
	this->setPosition(xPos, yPos);
	this->createAnimationComponent(texture);
	this->animations->addAnimation("Idle", 0, 3, 2, 8, 6, 9, 0.2f);
	this->animations->addAnimation("Walk", 0, 1, 4, 1, 4, 5, 0.2f);
	this->animations->addAnimation("Defend", 0, 3, 2, 3, 4, 5, 0.2f);
	this->animations->addAnimation("Attack", 0, 2, 3, 2, 4, 5, 0.2f);
	this->animations->addAnimation("Dead", 0, 0, 4, 0, 4, 5, 0.2f);
	this->animations->addAnimation("Hurt", 0, 3, 2, 3, 4, 5, 0.2f);
	this->currenStateAnim = typeOfAnimation::Idle_Anim;
}

Sirena::~Sirena()
{
}

void Sirena::update(const float& deltaT)
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

void Sirena::setNextAnimation(typeOfAnimation xd)
{
}

void Sirena::setCurrentAnimation(typeOfAnimation xd)
{
    this->currenStateAnim = xd;
    this->animationRequested = true;
}

void Sirena::setTypeAnim(unsigned int typeAnim)
{
}

unsigned int Sirena::getTypeAnim()
{
	return 0;
}
