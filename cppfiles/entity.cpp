#include "pch.h"
#include "../doth/entity.h"

Entity::Entity()
{
	this->entityTexture = NULL; this->entitySprite = NULL; this->speed = 100.f; this->hp = 0;
	this->name = ""; this->spriteHeight = 0; this->spriteWidht = 0; this->xPos = 0; this->yPos = 0;
}

Entity::~Entity()
{
	delete entitySprite;
}

void Entity::entityMovement(double deltaTime, float x, float y, float speed)
{
}

void Entity::render(RenderTarget* drawObj)
{
	try
	{
		if(!entitySprite != NULL)
		drawObj->draw(*this->entitySprite);
	}
	catch (const std::exception& p)
	{
		std::cout <<"The problem was: " << p.what() << std::endl;
	}
		
}

void Entity::updateTimeInScreen(double deltaT)
{
}

void Entity::setPosition(float xPos, float yPos)
{
	this->entitySprite->setPosition(xPos, yPos);
}

Vector2f Entity::getPosition() const
{
	return this->entitySprite->getPosition();
}


void Entity::createSprite(Texture* spriteTexture)
{
	try
	{
		this->entityTexture = spriteTexture;
		this->entitySprite = new Sprite(*entityTexture);
		this->entitySprite->setScale(spriteWidht, spriteHeight);
	}
	catch (const std::exception& p)
	{
		std::cout << "The problemas was : " << p.what();
	}
	
}



Texture* Entity::getEntityTexture() const
{
	return this->entityTexture;
}

void Entity::setEntityTexture(Texture* entityTexture)
{
	entityTexture = entityTexture;
}

Sprite* Entity::getEntitySprite() const
{
	return this->entitySprite;
}

void Entity::setEntitySprite(Sprite* entitySprite)
{
	this->entitySprite = entitySprite;
}

int Entity::getHp() const
{
	return this->hp;
}

void Entity::setHp(const int hp)
{
	this->hp = hp;
}

String Entity::getName() const
{
	return this->name;
}

void Entity::setName(const String name)
{
	this->name = name;
}

float Entity::getSpriteWidht() const
{
	return this->spriteWidht;
}

void Entity::setSpriteWidht(const float spriteWidht)
{
	this->spriteWidht = spriteWidht;
}

float Entity::getSpriteHeight() const
{
	return this->spriteHeight;
}

void Entity::setSpriteHeight(const float spriteHeight)
{
	this->spriteHeight = spriteHeight;
}

void Entity::setSpeed(const float speed)
{
	this->speed = speed;
}

float Entity::getSpeed() const
{
	return this->speed;
}

float Entity::getXpos() const
{
	return this->xPos;
}

void Entity::setXpos(const float xPos)
{
	this->xPos = xPos;
}

float Entity::getYpos() const
{
	return this->yPos;
}

void Entity::setYpos(const float yPos)
{
	this->yPos = yPos;
}

