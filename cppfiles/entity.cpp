#include "pch.h"
#include "../doth/entity.h"


Entity::Entity(int spriteWidth = 0, int spriteHeight = 0, Texture* entityTexture = NULL, Sprite* entitySprite = NULL, float speed = 0.f)
{
	this->velocity = Vector2f(0.f, 0.f); this->coordinates = Vector2i(0, 0); this->elapsedT = 0.f; this->isMoving = false;
}

Entity::~Entity()
{
	delete this->entitySprite;
}

void Entity::entityMovement(float deltaTime, float x, float y)
{
		this->velocity.x = this->speed * x;
		this->velocity.y = this->speed * y;
		this->entitySprite->move(getVelocity() * deltaTime);
	
}

void Entity::setEntityAnimation(float x, float y)
{
	this->velocity.x = x;
	this->velocity.y = y;
}

Vector2f Entity::getEntityMovement()
{
	return this->velocity;
}

void Entity::render(RenderTarget* objTarget)
{
	if (entitySprite != NULL) {
		objTarget->draw(*this->entitySprite);
	}
		
}

void Entity::updateSprite(float deltaT, float switchT)
{
	if (isMoving == true) 
	{
		elapsedT += deltaT;

		if (elapsedT >= switchT) {
			elapsedT -= switchT;
			coordinates.x++;

			if (coordinates.x * 64 >= this->getEntityTexture()->getSize().x) {
				coordinates.x = 0;
			}

		}
		this->entitySprite->setTextureRect(IntRect(coordinates.x * spriteWidth, coordinates.y * spriteHeight, spriteWidth, spriteHeight));
		std::cout << "deltaT: " << deltaT << std::endl;
	}
	else {
		this->entitySprite->setTextureRect(IntRect(coordinates.x * spriteWidth, coordinates.y * spriteHeight, spriteWidth, spriteHeight));
	}
	
		
		
}

void Entity::setPosition(float xPos, float yPos)
{
	
	this->entitySprite->setPosition(xPos, yPos);
}

Vector2f Entity::getPosition() 
{
	return this->entitySprite->getPosition();
}

void Entity::setSpeed(float speed)
{

	 this->speed = speed;
	 this->speed = speed;
}
float Entity::getSpeed() const {
	return this->speed;
}

Vector2f Entity::getVelocity()
{
	return velocity;
}


void Entity::createSprite(Texture* spriteTexture)
{
	std::cout << "Im the create sprite from entity " << std::endl;
	try
	{
		this->entityTexture = spriteTexture;
		this->entitySprite = new Sprite(*entityTexture);
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

int Entity::getSpriteWidth() const
{
	return this->spriteWidth;
}

void Entity::setSpriteWidth(int spriteWidth)
{
	this->spriteWidth = spriteWidth;
}

int Entity::getSpriteHeight() const
{
	return this->spriteHeight;
}

void Entity::setSpriteHeight(int spriteHeight)
{
	this->spriteHeight = spriteHeight;
}

int Entity::getCoordinatesX()
{
	return this->coordinates.x;
}

int Entity::getCoordinatesY()
{
	return this->coordinates.y;
}

void Entity::setCoordinatesX(int x)
{
	this->coordinates.x = x;
}

void Entity::setCoordinatesY(int y)
{
	this->coordinates.y = y;
}

bool Entity::getIsMoving()
{
	return this->isMoving;
}

void Entity::setIsMoving(bool isMoving)
{
	this->isMoving = isMoving;

}






