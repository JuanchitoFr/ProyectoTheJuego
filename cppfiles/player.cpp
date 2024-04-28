#include "pch.h"
#include "../doth/player.h"

Player::Player(int spriteWidth, int spriteHeight, Texture* playerTexture, float speed,int xPos,int yPos, unsigned int row, unsigned int xRowPos) 
	: Entity(spriteWidth,spriteHeight,playerTexture,NULL,speed)
{
	 this->createSprite(playerTexture);
	 this->spriteHeight = 64;
	 this->spriteWidth = 64;
	 /*textureRect.width = entityTexture->getSize().x / imageCount.x;
	 std::cout << "Texture rect width" << textureRect.width << std::endl;
	 textureRect.width = entityTexture->getSize().y / imageCount.y;
	 std::cout << "Texture rect height " << textureRect.width << std::endl;*/
	 this->entitySprite->setTextureRect(IntRect(xRowPos, row, spriteWidth, spriteHeight));
	 this->setPosition(float(xPos), float(yPos));
	 
}
 
Player::~Player()
{
}

void Player::initAnimaions()
{
	//walk down
}


/*void Player::setPosition(float xPos, float yPos)
{
	this->getEntitySprite()->setPosition(xPos, yPos);
}

Vector2f Player::getPosition() const
{
	return this->getEntitySprite()->getPosition();
}*/
