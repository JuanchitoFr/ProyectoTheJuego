#include "pch.h"
#include "Ogro.h"

Ogro::Ogro(Texture& texture, float xPos, float yPos)
{
	this->createSprite(&texture);
	this->asignarEstadisticas(this->stats, 27, 26, 16, 11, 10, 10);
	this->setPosition(xPos, yPos);
	this->createAnimationComponent(texture);
	this->animations->addAnimation("Idle", 0, 0, 14, 0, 18, 15, 0.15f);
	this->animations->addAnimation("Walk",0,1,11,1,18,15,0.15f);
	this->animations->addAnimation("Defend", 0, 2, 6, 2, 18, 15, 0.15f);
	this->animations->addAnimation("Attack", 0, 3, 12, 3, 18, 15, 0.15f);
	this->animations->addAnimation("Dead", 0, 6, 8, 6, 18, 15, 0.15f);
    this->animations->addAnimation("Hurt", 0, 4, 2, 4, 18, 15, 0.15f);
    this->animations->addAnimation("Hurt1", 0, 5, 4, 5, 18, 15, 0.15f);
	this->currenStateAnim = typeOfAnimation::Idle_Anim;
}

Ogro::~Ogro()
{
}

void Ogro::update(const float& deltaT)
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
                this->animations->play("Hurt1", deltaT);
                break;
            default:
                break;
        }
    
    }

    if (this->animations->getAnimations("Attack")->isFinished() ||
        this->animations->getAnimations("Defend")->isFinished() ||
        this->animations->getAnimations("Dead")->isFinished() ||
        this->animations->getAnimations("Hurt1")->isFinished() ||
        this->animations->getAnimations("Walk")->isFinished() || 
        this->animations->getAnimations("Hurt")->isFinished()) {
        // Volver al estado de inactividad
        currenStateAnim = typeOfAnimation::Idle_Anim;
        this->animationRequested = false;
    }

    // Si no hay animación solicitada, jugar la animación Idle
    if (!this->animationRequested) {
        this->animations->play("Idle", deltaT);
    }
}

void Ogro::setNextAnimation(typeOfAnimation xd)
{
	this->nextAnimation = xd;
}

void Ogro::setCurrentAnimation(typeOfAnimation xd)
{
	this->currenStateAnim = xd;
    this->animationRequested = true;
}

void Ogro::setTypeAnim(unsigned int typeAnim)
{
	this->typeAnim = typeAnim;
}

unsigned int Ogro::getTypeAnim()
{
	return this->typeAnim;
}
