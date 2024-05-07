#include "pch.h"
#include "../doth/player.h"

Player::Player(Texture* playerTexture = nullptr, float speed = 0.f,
	unsigned int xTextureRectPos = 0, unsigned int yTextureRectPos = 0) : Entity(playerTexture,speed)
{
	 this->createSprite(*playerTexture);
	 /*textureRect.width = entityTexture->getSize().x / imageCount.x;
	 std::cout << "Texture rect width" << textureRect.width << std::endl;
	 textureRect.width = entityTexture->getSize().y / imageCount.y;
	 std::cout << "Texture rect height " << textureRect.width << std::endl;*/
	 this->entitySprite->setTextureRect(IntRect(xTextureRectPos, yTextureRectPos, spriteWidth, spriteHeight));
	 
}

Player::Player()
{

}
 
Player::~Player()
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
