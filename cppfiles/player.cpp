#include "pch.h"
#include "../doth/player.h"

Player::Player(float xPos, float yPos, int hp, String name, float spriteWidht, float spriteHeight, Texture* playerTexture)
{
	this->createSprite(playerTexture);
	this->setPosition(xPos,yPos);
}

Player::~Player()
{
}

void Player::entityMovement(double deltaTime, float x, float y, float speed)
{
}

void Player::render(RenderTarget* objTarget)
{
	Entity::render(objTarget);
}

void Player::updateTimeInScreen(double deltaT)
{
}

/*void Player::setPosition(float xPos, float yPos)
{
	this->getEntitySprite()->setPosition(xPos, yPos);
}

Vector2f Player::getPosition() const
{
	return this->getEntitySprite()->getPosition();
}*/
