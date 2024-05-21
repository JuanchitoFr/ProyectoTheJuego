#include "pch.h"
#include "Player.h"

Player::Player(Texture* playerTexture, float speed,
	unsigned int xTextureRectPos, unsigned int yTextureRectPos)
{
	 this->createSprite(playerTexture);

	 /*textureRect.width = entityTexture->getSize().x / imageCount.x;
	 std::cout << "Texture rect width" << textureRect.width << std::endl;
	 textureRect.width = entityTexture->getSize().y / imageCount.y;
	 std::cout << "Texture rect height " << textureRect.width << std::endl;*/
	 stats.x = 0; stats.y = 0; stats.hp = 0; stats.atkFisico = 0; stats.defFisica = 0; stats.atkMagico = 0; stats.defMagica = 0; stats.velocidad = 0;
	 
}

Player::~Player()
{
}

void Player::setTextureRect(unsigned int xCount, unsigned int yCount, unsigned int columns, unsigned int rows)
{
	

	this->coordinates.x = (float)xCount;
	this->coordinates.y = (float)yCount;
	this->spriteWidth = ((float)this->entityTexture->getSize().x) / (float)columns;
	this->spriteHeight = (float)this->entityTexture->getSize().y / (float)rows;
	cout << spriteWidth << "XDpe" << endl;
	cout << spriteHeight << "XDhe" << endl;
	this->entitySprite->setTextureRect(IntRect(xCount,yCount, static_cast<int>(spriteWidth),static_cast<int>(spriteHeight)));
}






/*void Player::setPosition(float xPos, float yPos)
{
	this->getEntitySprite()->setPosition(xPos, yPos);
}

Vector2f Player::getPosition() const
{
	return this->getEntitySprite()->getPosition();
}*/
